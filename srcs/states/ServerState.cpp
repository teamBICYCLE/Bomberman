//
// ServerState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Tue May 22 17:59:10 2012 lois burg
// Last update Sun Jun  3 19:39:32 2012 lois burg
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GDL/Text.hpp>
#include <ctime>
#include "Vector3d.hh"
#include "Player.hh"
#include "ServerState.hh"
#include "Map.hh"
#include "Online.hh"
#include "Carrousel/Draw.hh"

using namespace	Bomberman;
using namespace	Online;

ServerState::ServerState(int mapWidth, int mapHeight, uint nbPlayers, TCPServerSocket*& serv, std::vector<TCPSocket*>& clients)
  : PlayState(), nbPlayers_(nbPlayers), serv_(serv), clients_(clients)
{
  mapW_ = mapWidth;
  mapH_ = mapHeight;
}

ServerState::~ServerState()
{
}

bool	ServerState::init()
{
  int	i = 1;
  bool	success = true;
  time_t seed = time(NULL);

  srand(seed);
  try {
    Map	map(mapW_, mapH_, nbPlayers_, 0, 0);

    characterToUpdate_ = 0;
    objs_.insert(objs_.end(), map.getTerrain().begin(), map.getTerrain().end());
    for (i = 1; i < nbPlayers_; ++i)
      {
	Player	*plyr = Online::getPlayerWithId(objs_, i);

	if (plyr)
	  plyr->setNetworkControlled(true);
      }
    i = 1;
    std::for_each(clients_.begin(), clients_.end(), [this, seed, i] (TCPSocket *s) mutable -> void {
	if (s)
	  try {
	    std::iostream& sockStream = s->getStream();

	    sockStream << seed << " " << i << " " << nbPlayers_ << std::endl;
	    sockStream.flush();
	    ++i;
	  } catch (SocketException& e) {
	    std::cerr << "Network error while sending seed: " << e.what() << std::endl;
	  }
      });
  } catch (Map::Failure& e) {
    success = false;
    std::cerr << e.what() << std::endl;
  }
  return (success);
}

void	ServerState::cleanUp()
{
  for (std::vector<TCPSocket*>::iterator it = clients_.begin(); it != clients_.end(); ++it)
    delete (*it);
  clients_.clear();
  delete serv_;
  serv_ = NULL;
  PlayState::cleanUp();
}

void	ServerState::update(StatesManager *mngr, double delta)
{
  Packet	packet;
  Packet	netPacket;
  Player	*plyr;
  std::vector<TCPSocket*>::iterator it;

  select_.reset();
  select_.setNonBlock();
  std::for_each(clients_.begin(), clients_.end(), [this] (TCPSocket *s) -> void {
      if (s)
	select_.addRead(s->getSockDesc());
    });
  select_.watch();
  for (it = clients_.begin(); it != clients_.end(); ++it)
    {
      bool	disconnected = false;
      Packet	p;

      if ((*it) && select_.canRead((*it)->getSockDesc()))
	{
	  p = recvPacket((*it)->getStream(), disconnected);
	  if (disconnected)
	    {
	      (*it)->close();
	      delete (*it);
	      (*it) = NULL;
	    }
	  else
	    {
	      Online::updatePlayerWithId(objs_, p.id, p, mngr->getGameClock(), mngr->getInput());
	      forwardPacket(clients_, (*it)->getSockDesc(), p);
	    }
	}
    }
  PlayState::update(mngr, delta);
  if ((plyr = getPlayerWithId(objs_, 0)))
    packet = plyr->pack(mngr->getInput());
  if (readyUp_ <= 0)
    std::for_each(clients_.begin(), clients_.end(), [&] (TCPSocket *s) -> void {
	if (s && plyr)
	  sendPacket(s->getStream(), packet);
      });
}

void	ServerState::checkEndGame(StatesManager *mngr, int nbPlayersAlive, int nbMonsters)
{
  int		i = 0;
  Player	*plyr = NULL;

  if (readyUp_ <= 0)
    {
      if (nbPlayersAlive == 1 && !nbMonsters)
	{
	  while (i < nbPlayers_ && !(plyr = Online::getPlayerWithId(objs_, i)))
	    i++;
	  if (plyr)
	    winnerId_ = i;
	  win(mngr);
	}
      else if (!nbPlayersAlive)
	{
	  CarrouselHandler  *cH = createInGameCH();

	  cH->pushPage(new APage(new Draw, "bg-defeat", "empty-arrows", "empty-arrows"));
	  cH->setArrowFocus(false);
	  cH->setEscapeFocus(false);
	  mngr->pushState(cH);
	}
    }
}

//
// ClientState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 25 17:11:55 2012 lois burg
// Last update Sun Jun  3 19:39:09 2012 lois burg
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
#include "ClientState.hh"
#include "ServerState.hh"
#include "Map.hh"
#include "Online.hh"
#include "Carrousel/Draw.hh"

using namespace	Bomberman;
using namespace	Online;

ClientState::ClientState(const std::string& host)
  : PlayState(), host_(host), disconnected_(false)
{
}

ClientState::~ClientState()
{
}

bool	ClientState::init()
{
  bool	success = true;
  time_t seed;

  try {
    if ((serv_ = new TCPSocket(host_.c_str(), ServPort)))
      {
	std::iostream& sockStream = serv_->getStream();

	sockStream >> seed;
	sockStream >> playerNbr_;
	sockStream >> nbPlayers_;
	characterToUpdate_ = playerNbr_;
	srand(seed);
	try {
	  Map	map(13, 13, nbPlayers_, 0, 0);
	  mapH_ = map.getHeight();
	  mapW_ = map.getWidth();
	  objs_.insert(objs_.end(), map.getTerrain().begin(), map.getTerrain().end());
	  for (int i = 0; i < nbPlayers_; ++i)
	    {
	      Player	*plyr = Online::getPlayerWithId(objs_, i);

	      if (plyr && i != playerNbr_)
		plyr->setNetworkControlled(true);
	    }
	} catch (Map::Failure& e) {
	  success = false;
	  std::cerr << e.what() << std::endl;
	}
      }
  } catch (SocketException& e) {
    std::cerr << "Network error: " << e.what() << std::endl;
    disconnected_ = true;
    serv_ = NULL;
    success = false;
  }
  return (success);
}

void	ClientState::cleanUp()
{
  delete serv_;
  PlayState::cleanUp();
}

void	ClientState::update(StatesManager *mngr, double delta)
{
  Packet	packet;
  Packet	netPacket;
  Player	*plyr;

  if (disconnected_)
    mngr->popState();
  else if (serv_)
    {
      select_.reset();
      select_.setNonBlock();
      select_.addRead(serv_->getSockDesc());
      select_.watch();
      if (select_.canRead(serv_->getSockDesc()))
	{
	  netPacket = Online::recvPacket(serv_->getStream(), disconnected_);
  	  Online::updatePlayerWithId(objs_, netPacket.id, netPacket, mngr->getGameClock(), mngr->getInput());
	}
      PlayState::update(mngr, delta);
      if ((plyr = getPlayerWithId(objs_, playerNbr_)))
	packet = plyr->pack(mngr->getInput());
      if (readyUp_ <= 0 && serv_ && !disconnected_)
	sendPacket(serv_->getStream(), packet);
    }
}

void	ClientState::checkEndGame(StatesManager *mngr, int nbPlayersAlive, int nbMonsters)
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

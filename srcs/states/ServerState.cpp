//
// ServerState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Tue May 22 17:59:10 2012 lois burg
// Last update Sun May 27 15:29:02 2012 lois burg
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

using namespace	Bomberman;
using namespace	Online;

ServerState::ServerState(uint nbPlayers)
  : PlayState(), nbPlayers_(nbPlayers), clients_(nbPlayers_ - 1)
{
}

ServerState::~ServerState()
{
}

bool	ServerState::init()
{
  uint	i = 1;
  bool	success = true;
  time_t seed = time(NULL);

  srand(seed);
  std::cout << "Seed : " << seed << std::endl;

  //TEMPORARY
  try {
    serv_ = new TCPServerSocket(ServPort, nbPlayers_ - 1);
    std::cout << "Server listening on : " << ServPort << std::endl;
    for (i = 1; i < nbPlayers_; ++i)
      {
	std::cout << "Waiting client #" << i << std::endl;
	clients_[i - 1] = serv_->accept();
	std::cout << nbPlayers_ - i << " clients left." << std::endl;
      }
  } catch (SocketException& e) {
    std::cerr << "Connection error: " << e.what() << std::endl;
    serv_ = NULL;
  }
  //END TEMPORARY

  try {
    Map	map(13, 13, nbPlayers_, 0, 0);

    characterToUpdate_ = 0;
    mapH_ = map.getHeight();
    mapW_ = map.getWidth();
    objs_.insert(objs_.end(), map.getTerrain().begin(), map.getTerrain().end());
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
  std::cout << "Cleanup server" << std::endl;
  clients_.clear();
  delete serv_;
  PlayState::cleanUp();
}

void	ServerState::update(StatesManager *mngr)
{
  Packet	prevPacket;
  Packet	updatedPacket;
  Packet	netPacket;
  Player	*plyr;
  std::vector<TCPSocket*>::iterator it;

  plyr = getPlayerWithId(objs_, 0);
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
	      delete (*it);
	      (*it) = NULL;
	    }
	  else
	    {
	      Online::updatePlayerWithId(objs_, p.id, p);
	      forwardPacket(clients_, (*it)->getSockDesc(), p);
	    }
	}
    }
  if (plyr)
    prevPacket = plyr->pack();
  PlayState::update(mngr);
  if (plyr)
    updatedPacket = plyr->pack();
  if (prevPacket != updatedPacket)
    std::for_each(clients_.begin(), clients_.end(), [&] (TCPSocket *s) -> void {
	if (s && plyr)
	  sendPacket(s->getStream(), updatedPacket);
      });
}

void	ServerState::win(StatesManager *mngr)
{
  (void)mngr;
}

void	ServerState::gameOver(StatesManager *mngr)
{
  (void)mngr;
}

void	ServerState::sendMap(void)
{
}

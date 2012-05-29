//
// ClientState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 25 17:11:55 2012 lois burg
// Last update Mon May 28 18:16:12 2012 lois burg
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

using namespace	Bomberman;
using namespace	Online;

ClientState::ClientState(const std::string& host)
  : PlayState(), host_(host), disconnected_(false)
{
  Online::init();
}

ClientState::~ClientState()
{
}

bool	ClientState::init()
{
  int	nbPlayers = 1;
  bool	success = true;
  time_t seed;

  //TEMPORARY
  try {
    serv_ = new TCPSocket(host_.c_str(), ServPort);
    std::cout << "Client connected to : " << host_ << std::endl;
  } catch (SocketException& e) {
    std::cerr << "Connection error: " << e.what() << std::endl;
    disconnected_ = true;
    serv_ = NULL;
  }
  //END TEMPORARY

  try {
    if (serv_)
      {
	std::iostream& sockStream = serv_->getStream();

	sockStream >> seed;
	sockStream >> playerNbr_;
	sockStream >> nbPlayers;
	std::cout << "The seed is: " << seed << ", I am the player #" << playerNbr_ << " out of " << nbPlayers << "players." << std::endl;
	characterToUpdate_ = playerNbr_;
	srand(seed);
	std::cout << "Seed : " << seed << std::endl;
	try {
	  Map	map(13, 13, nbPlayers, 0, 0);
	  mapH_ = map.getHeight();
	  mapW_ = map.getWidth();
	  objs_.insert(objs_.end(), map.getTerrain().begin(), map.getTerrain().end());
	  for (int i = 0; i < nbPlayers; ++i)
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
    serv_ = NULL;
    success = false;
  }
  return (success);
}

void	ClientState::cleanUp()
{
  std::cout << "Cleanup client" << std::endl;
  delete serv_;
  PlayState::cleanUp();
}

void	ClientState::update(StatesManager *mngr)
{
  Packet	packet;
  Packet	netPacket;
  Player	*plyr;

  if (disconnected_)
    mngr->popState();//faire plus smooth
  else if (serv_)
    {
      select_.reset();
      select_.setNonBlock();
      select_.addRead(serv_->getSockDesc());
      select_.watch();
      if (select_.canRead(serv_->getSockDesc()))
	{
	  netPacket = Online::recvPacket(serv_->getStream(), disconnected_);
	  std::cout << "NetPacket: " << std::endl << netPacket << std::endl;
	  Online::updatePlayerWithId(objs_, netPacket.id, netPacket, mngr->getGameClock(), mngr->getInput());
	}
      PlayState::update(mngr);
      if ((plyr = getPlayerWithId(objs_, playerNbr_)))
	packet = plyr->pack(mngr->getInput());
      if (serv_ && packet.isUseful())
	sendPacket(serv_->getStream(), packet);
    }
}

void	ClientState::win(StatesManager *mngr)
{
  (void)mngr;
}

void	ClientState::gameOver(StatesManager *mngr)
{
  (void)mngr;
}
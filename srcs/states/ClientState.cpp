//
// ClientState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 25 17:11:55 2012 lois burg
// Last update Sun May 27 12:41:42 2012 lois burg
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
  Packet	prevPacket;
  Packet	updatedPacket;
  Packet	netPacket;
  Player	*plyr;

  //update depuis le serveur
  if (disconnected_)
    mngr->popState();//faire plus smooth
  else if (serv_)
    {
      if ((plyr = getPlayerWithId(objs_, playerNbr_)))
	prevPacket = plyr->pack();
      select_.reset();
      select_.setNonBlock();
      select_.addRead(serv_->getSockDesc());
      select_.watch();
      if (select_.canRead(serv_->getSockDesc()))
	{
	  netPacket = Online::recvPacket(serv_->getStream(), disconnected_);
	  std::cout << "NetPacket: " << std::endl << netPacket << std::endl;
	  //check si c'est une bombe ou un joueur
	  Online::updatePlayerWithId(objs_, netPacket.id, netPacket);
	}
      PlayState::update(mngr);
      if (plyr)
	updatedPacket = plyr->pack();
      if (serv_ && updatedPacket != prevPacket)
	sendPacket(serv_->getStream(), updatedPacket);
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

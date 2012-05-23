//
// OnlineState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Tue May 22 17:59:10 2012 lois burg
// Last update Tue May 22 18:04:54 2012 lois burg
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vector3d.hh"
#include "Player.hh"
#include "OnlineState.hh"
#include "Map.hh"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GDL/Text.hpp>

using namespace	Bomberman;

OnlineState::OnlineState(uint nbPlayers, const std::string& host)
  : nbPlayers_(nbPlayers)
{
  if (host.empty())
    serv_ = new QTcpServer(NULL);
}

bool	OnlineState::init()
{
  bool	success = true;

  return (success);
}

void	OnlineState::cleanUp()
{
  PlayState::cleanUp();
}

void	OnlineState::win(StatesManager *mngr)
{
  (void)mngr;
}

void	OnlineState::gameOver(StatesManager *mngr)
{
  (void)mngr;
}

//
// AdventureState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:00:30 2012 lois burg
// Last update Sat May 19 16:52:50 2012 lois burg
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vector3d.hh"
#include "Player.hh"
#include "AdventureState.hh"
#include "Map.hh"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GDL/Text.hpp>

#include "SaveHandler.hh"

using namespace	Bomberman;

bool	AdventureState::init()
{
  bool			success = true;
  std::stringstream	ss;
  std::string		mapName = "./Ressources/Map/adventure";
  int			i = 1;
  Map			*map;

  try {
    for (; i <= 5; ++i)
      {
	ss.clear();
	ss.str("");
	ss << mapName << i;
	map = new Map(ss.str());
	adventureMaps_.push_back(map);
	Character::CharacterId = 0;
      }
    adventureLevel_ = adventureMaps_.begin();
    mapH_ = (*adventureLevel_)->getHeight();
    mapW_ = (*adventureLevel_)->getWidth();
    objs_.insert(objs_.end(), (*adventureLevel_)->getTerrain().begin(), (*adventureLevel_)->getTerrain().end());
  } catch (Map::Failure& e) {
    success = false;
    std::cerr << e.what() << std::endl;
  }
  return (true);
}

void	AdventureState::cleanUp()
{
  std::cout << "clean up Adventure" << std::endl;
}

void	AdventureState::win(StatesManager *mngr)
{
  (void)mngr;
  std::cout << "YOU WIN" << std::endl;
  ++adventureLevel_;
  if (adventureLevel_ == adventureMaps_.end())
    std::cout << "CONGRATS!" << std::endl;
  else
    {
      mapH_ = (*adventureLevel_)->getHeight();
      mapW_ = (*adventureLevel_)->getWidth();
      objs_.clear();
      objs_.insert(objs_.end(), (*adventureLevel_)->getTerrain().begin(), (*adventureLevel_)->getTerrain().end());
    }
}

void	AdventureState::gameOver(StatesManager *mngr)
{
  (void)mngr;
  std::cout << "YOU LOSE :(" << std::endl;
  adventureLevel_ = adventureMaps_.begin();
  mapH_ = (*adventureLevel_)->getHeight();
  mapW_ = (*adventureLevel_)->getWidth();
  objs_.insert(objs_.end(), (*adventureLevel_)->getTerrain().begin(), (*adventureLevel_)->getTerrain().end());
}

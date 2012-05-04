//
// PlayState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:00:30 2012 lois burg
// Last update Fri May  4 10:51:31 2012 lois burg
//

#include <iostream>
#include <algorithm>
#include "Vector3d.hh"
#include "Player.hh"
#include "PlayState.hh"

using namespace	Bomberman;

void  PlayState::init(gdl::GameClock *clock, gdl::Input *input)
{
  keys_ = input;
  clock_ = clock;
  objs_.push_back(new Player(Vector3d(), Vector3d(), Vector3d()));
}

void  PlayState::cleanUp()
{
  std::cout << "clean up Play" << std::endl;
}

void  PlayState::update(StatesManager * sMg)
{
  std::for_each(objs_.begin(), objs_.end(), [this](AObject *obj) -> void {
      obj->update(*clock_, *keys_);
    });
}

void  PlayState::draw(StatesManager * sMg)
{
  std::cout << "draw Play" << std::endl;
}

void  PlayState::pause()
{
  std::cout << "pause Play" << std::endl;
}

void  PlayState::resume()
{
  std::cout << "resume Play" << std::endl;
}

//
// PlayState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:00:30 2012 lois burg
// Last update Thu May  3 12:20:10 2012 lois burg
//

#include <iostream>
#include "PlayState.hh"

using namespace	Bomberman;

void  PlayState::init()
{

}

void  PlayState::cleanUp()
{
  std::cout << "clean up Play" << std::endl;
}

void  PlayState::update(StatesManager * sMg)
{
  std::cout << "update Play" << std::endl;
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

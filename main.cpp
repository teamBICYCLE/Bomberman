//
// main.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 16:49:18 2012 lois burg
// Last update Fri May  4 19:08:08 2012 romain sylvian
//

#include "StatesManager.hh"
#include "IntroState.hh"
#include "PlayState.hh"
#include <GDL/ModelException.hpp>

#include "Map.hh"

using namespace std;

int main(void)
{
  try {
    StatesManager   mg("Bomberman v0.1");


  mg.changeState(new Bomberman::PlayState());
  mg.run();
  }
  catch (gdl::ModelException * e)
  {
    std::cout << e->what() << std::endl;
  }

  return 0;
}

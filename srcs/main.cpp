//
// main.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 16:49:18 2012 lois burg
// Last update Sat May 19 15:42:55 2012 lois burg
//

#include "StatesManager.hh"
#include "Menu/MenuState.hh"
#include "AdventureState.hh"
#include <GDL/ModelException.hpp>

#include "Map.hh"

#include "Player.hh"

using namespace std;

int main(void)
{
  try {
    StatesManager   mg("Bomberman v0.01");

    mg.start(new Menu::MenuState());
  }
  catch (gdl::ModelException * e)
  {
    std::cout << e->what() << std::endl;
  }

  return 0;
}

//
// main.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 16:49:18 2012 lois burg
// Last update Sun May 20 14:26:01 2012 lois burg
//

#include <GDL/ModelException.hpp>
#include "StatesManager.hh"
#include "Menu/MenuState.hh"
#include "AdventureState.hh"
#include "Carrousel/CarrouselHandler.hh"
#include "Carrousel/ItemList.hh"

#include "Map.hh"

#include "Player.hh"

using namespace std;

void  loadModels()
{

}

int main(void)
{
  try {
    StatesManager   mg("Bomberman v0.01");
    CarrouselHandler *    carrouselHandler;

    carrouselHandler = new CarrouselHandler();

    ModelHandler::get().preload();
    carrouselHandler->pushPage(new APage(new ItemList(), "bg", "left", "right"));
    carrouselHandler->pushPage(new APage(new ItemList(), "bg", "right", "left"));
    mg.start(carrouselHandler);
  }
  catch (gdl::ModelException * e)
  {
    std::cout << e->what() << std::endl;
  }

  return 0;
}

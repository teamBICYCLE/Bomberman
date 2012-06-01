//
// main.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 16:49:18 2012 lois burg
// Last update Fri Jun  1 12:26:03 2012 lois burg
//

#include <GDL/ModelException.hpp>
#include "StatesManager.hh"
#include "Menu/MenuState.hh"
#include "AdventureState.hh"
#include "Carrousel/CarrouselHandler.hh"
#include "Carrousel/ItemList.hh"
#include "TwitterConnection.hh"
#include "Carrousel/LoadContent.hh"
#include "Carrousel/QuickGame.hh"
#include "Carrousel/CustomGame.hh"
#include "Carrousel/HostGame.hh"
#include "Carrousel/JoinGame.hh"
#include "Carrousel/AdventureGame.hh"
#include "Carrousel/LeaderBoards.hh"
#include "Carrousel/KeyBindSlide.hh"
#include "IntroState.hh"

using namespace std;

void  loadModels()
{

}

int main(int ac, char **av)
{
  try {
    StatesManager   mg("Bomberman v0.8");
    CarrouselHandler *carrouselHandler;
    TwitterConnection *ptr = TwitterConnection::getInstance(ac, av);


    ptr->requestAccess();
    ModelHandler::get().preload();
    carrouselHandler = new CarrouselHandler("mainbg");

    carrouselHandler->pushPage(new APage(new QuickGame(), "bg-quickgame", "left", "right"));
    carrouselHandler->pushPage(new APage(new CustomGame(), "bg-customgame", "left", "right"));
    carrouselHandler->pushPage(new APage(new AdventureGame(), "bg-adventure", "arrow-adventure-left", "arrow-adventure-right"));
    carrouselHandler->pushPage(new APage(new HostGame(), "bg-hostgame", "left", "right"));
    carrouselHandler->pushPage(new APage(new JoinGame(), "bg-joingame", "left", "right"));
    // carrouselHandler->pushPage(new APage(new ItemList(), "bg", "right", "left"));
    carrouselHandler->pushPage(new APage(new LoadContent(), "bg-load", "arrow-load-left", "arrow-load-right"));
    carrouselHandler->pushPage(new APage(new LeaderBoards(), "bg-leaderboards", "left", "right"));
    carrouselHandler->pushPage(new APage(new KeyBindSlide(), "bg-keybind", "arrow-keybind-left", "arrow-keybind-right"));

    mg.start(carrouselHandler);
  } catch (gdl::ModelException * e) {
    std::cout << e->what() << std::endl;
  }
  return 0;
}

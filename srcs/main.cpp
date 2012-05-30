//
// main.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 16:49:18 2012 lois burg
// Last update Wed May 30 17:28:30 2012 romain sylvian
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

using namespace std;

void  loadModels()
{

}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    try {
        StatesManager   mg("Bomberman v0.01");
        CarrouselHandler *carrouselHandler;

        carrouselHandler = new CarrouselHandler();

        ModelHandler::get().preload();
        carrouselHandler->pushPage(new APage(new QuickGame(), "bg-quickgame", "right", "left"));
        // carrouselHandler->pushPage(new APage(new ItemList(), "bg", "right", "left"));
        carrouselHandler->pushPage(new APage(new LoadContent(), "bg-load", "arrow-load-left", "arrow-load-right"));

        mg.start(carrouselHandler);
    }
    catch (gdl::ModelException * e)
    {
        std::cout << e->what() << std::endl;
    }

    return 0;
}

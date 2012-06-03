//
// main.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 16:49:18 2012 lois burg
// Last update Sat Jun  2 12:42:07 2012 lois burg
//

#include <GDL/ModelException.hpp>
#include "StatesManager.hh"
#include "Menu/MenuState.hh"
#include "AdventureState.hh"
#include "TwitterConnection.hh"
#include "IntroState.hh"
#include "Sounds.hh"
#include "IntroState.hh"

using namespace std;

void  loadModels()
{

}

int main(int ac, char **av)
{
    try {
        StatesManager   mg("Bomberman v0.8");
        TwitterConnection *ptr = TwitterConnection::getInstance(ac, av);

        ptr->requestAccess();
        ModelHandler::get().preload();
        Sounds::instance().preload();
        mg.start(new IntroState());
    }
    catch (std::exception * e)
    {
        std::cout << e->what() << std::endl;
    }

    return 0;

}

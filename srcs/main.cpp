//
// main.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 16:49:18 2012 lois burg
// Last update Mon May 28 14:54:04 2012 Thomas Duplomb
//

#include "StatesManager.hh"
#include "Menu/MenuState.hh"
#include "AdventureState.hh"
#include <GDL/ModelException.hpp>

#include "Player.hh"

#include "TwitterConnection.hh"



using namespace std;

void  loadModels()
{

}

int main(int ac, char **av)
{
  try {
        TwitterConnection *twitter = TwitterConnection::getInstance(ac, av);
        StatesManager   mg("Bomberman v0.01");

        twitter->requestAccess();
        twitter->sendTweet(2301);
        mg.start(new Menu::MenuState());
    }
    catch (gdl::ModelException * e)
    {
        std::cout << e->what() << std::endl;
    }
}

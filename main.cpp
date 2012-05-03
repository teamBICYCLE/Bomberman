//
// main.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 16:49:18 2012 lois burg
// Last update Thu May  3 16:50:12 2012 lois burg
//

#include "StatesManager.hh"
#include "IntroState.hh"
#include "PlayState.hh"

using namespace std;

int main(void)
{
  StatesManager   mg("Bomberman v0.1", new Bomberman::PlayState());

  mg.run();
  return 0;
}

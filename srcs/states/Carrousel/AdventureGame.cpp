//
// AdventureGame.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Thu May 31 10:51:25 2012 lois burg
//

#include "AdventureGame.hh"
#include "Map.hh"
#include "AdventureState.hh"

using namespace	Bomberman;

AdventureGame::AdventureGame()
  : returnHit_(false)
{
}

AdventureGame::~AdventureGame()
{
}

void	AdventureGame::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH)
{
  (void)cH;
  (void)gClock;
  if (input.isKeyDown(gdl::Keys::Return) && !returnHit_)
    sMg->pushState(new AdventureState);
  returnHit_ = input.isKeyDown(gdl::Keys::Return);
}

void	AdventureGame::draw(void)
{
}

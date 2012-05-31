//
// QuickGame.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Thu May 31 10:49:55 2012 lois burg
//

#include "QuickGame.hh"
#include "Map.hh"
#include "PlayState.hh"
#include "Character.hh"
#include "CarrouselHandler.hh"

using namespace	Bomberman;

QuickGame::QuickGame()
  : returnHit_(false)
{
}

QuickGame::~QuickGame()
{
}

void	QuickGame::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler *cH)
{
  static bool sHit;

  (void)gClock;
  if (input.isKeyDown(gdl::Keys::Comma) && !sHit)
    cH->setArrowFocus(!cH->getArrowFocusLeft());
  if (input.isKeyDown(gdl::Keys::Return) && !returnHit_)
    {
      try {
        Character::CharacterId = 0;
        Map	map(13, 13, 2, 0, 0);

        sMg->pushState(new PlayState(&map.getTerrain()), false);
      } catch (Map::Failure& e) {
        std::cerr << e.what() << std::endl;
      }
    }
  sHit = input.isKeyDown(gdl::Keys::Comma);
  returnHit_ = input.isKeyDown(gdl::Keys::Return);
}

void	QuickGame::draw(void)
{
}

//
// Win.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Sat Jun  2 18:01:49 2012 lois burg
//

#include "Win.hh"
#include "CarrouselHandler.hh"

using namespace	Bomberman;

Win::Win(int winnerId)
  : winnerId_(winnerId), returnHit_(false)
{
}

Win::~Win()
{
}

void	Win::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler *cH)
{
  (void)gClock;
  (void)cH;
  if (input.isKeyDown(gdl::Keys::Return) && !returnHit_)
    {
      sMg->popState();
      sMg->popState();
    }
  returnHit_ = input.isKeyDown(gdl::Keys::Return);
}

#include <sstream>
#include <GDL/Text.hpp>
void	Win::draw(void)
{
  gdl::Text	text;
  std::stringstream	ss;

  glPushMatrix();
  ss << "Player " << winnerId_ << " wins!";
  text.setFont("Ressources/Fonts/Dimbo.ttf");
  text.setSize(36);
  text.setText(ss.str());
  text.setPosition(0, 0);
  text.draw();
  glPopMatrix();
}

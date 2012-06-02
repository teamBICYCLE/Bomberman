//
// Loose.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Sat Jun  2 17:36:59 2012 lois burg
//

#include "Loose.hh"
#include "CarrouselHandler.hh"

using namespace	Bomberman;

Loose::Loose(int looserId)
  : looserId_(looserId), returnHit_(false)
{
}

Loose::~Loose()
{
}

void	Loose::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler *cH)
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
void	Loose::draw(void)
{
  gdl::Text	text;
  std::stringstream	ss;

  ss << "Player " << looserId_ << " looses!";
  text.setFont("Ressources/Fonts/Dimbo.ttf");
  text.setSize(36);
  text.setText(ss.str());
  text.setPosition(0, 0);
  text.draw();
}

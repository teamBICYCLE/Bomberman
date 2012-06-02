//
// Loose.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Sat Jun  2 19:11:45 2012 lois burg
//

#include <sstream>
#include "ModelHandler.hh"
#include "Loose.hh"
#include "CarrouselHandler.hh"

using namespace	Bomberman;

Loose::Loose(int looserId)
  : returnHit_(false), looseLabel_(ModelHandler::get().getModel("looses"))
{
  std::stringstream	ss;

  ss << "player" << looserId;
  playerLabel_ = new flatTexture(ModelHandler::get().getModel(ss.str()));
}

Loose::~Loose()
{
  delete playerLabel_;
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

void	Loose::draw(void)
{
  glPushMatrix();
  playerLabel_->draw();
  looseLabel_.draw();
  glPopMatrix();
}

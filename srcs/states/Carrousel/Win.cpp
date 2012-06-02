//
// Win.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Sat Jun  2 19:17:35 2012 lois burg
//

#include <sstream>
#include "ModelHandler.hh"
#include "Win.hh"
#include "CarrouselHandler.hh"

using namespace	Bomberman;

Win::Win(int winnerId)
  : returnHit_(false), winLabel_(ModelHandler::get().getModel("wins"))
{
  std::stringstream	ss;

  ss << "player" << winnerId;
  playerLabel_ = new flatTexture(ModelHandler::get().getModel(ss.str()));
}

Win::~Win()
{
  delete playerLabel_;
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

void	Win::draw(void)
{
  glPushMatrix();
  playerLabel_->draw();
  winLabel_.draw();
  glPopMatrix();
}

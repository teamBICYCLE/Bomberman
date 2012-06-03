//
// Win.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Sun Jun  3 12:53:50 2012 lois burg
//

#include <sstream>
#include "ModelHandler.hh"
#include "Win.hh"
#include "CarrouselHandler.hh"
#include "Sounds.hh"

using namespace	Bomberman;

Win::Win(int winnerId)
  : returnHit_(false), winLabel_(ModelHandler::get().getModel("wins"))
{
  std::stringstream	ss;

  ss << "player" << winnerId;
  playerLabel_ = new flatTexture(ModelHandler::get().getModel(ss.str()));
  Sounds::instance().playEffect("cheers");
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
  glTranslated(500, 350, 0);
  playerLabel_->draw();
  glPopMatrix();

  glPushMatrix();
  glTranslated(930, 382, 0);
  winLabel_.draw();
  glPopMatrix();
}

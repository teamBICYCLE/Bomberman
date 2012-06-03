//
// Draw.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Sun Jun  3 15:01:50 2012 lois burg
//

#include <sstream>
#include "ModelHandler.hh"
#include "Draw.hh"
#include "CarrouselHandler.hh"

using namespace	Bomberman;

Draw::Draw()
  : returnHit_(false), drawLabel_(ModelHandler::get().getModel("draw"))
{
}

Draw::~Draw()
{
}

void	Draw::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler *cH)
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

void	Draw::draw(void)
{
  glPushMatrix();
  glTranslated(600, 312, 0);
  drawLabel_.draw();
  glPopMatrix();
}

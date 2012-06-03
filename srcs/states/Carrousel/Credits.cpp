/**************************************************************************
** Credits.cpp: Created on 3 Jun 2012 by duplom_t
** for class : Credits
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "Credits.hh"
#include "ModelHandler.hh"
#include <GL/gl.h>

Credits::Credits()
  : bg_(Bomberman::ModelHandler::get().getModel("credits"))
{
}

Credits::~Credits()
{
}

void Credits::update(gdl::Input &input, gdl::GameClock &gClock, StatesManager *sMg, CarrouselHandler *cH)
{
  (void)input;
  (void)gClock;
  (void)sMg;
}

void Credits::draw()
{
  glPushMatrix();
  glTranslated(0, 15, 0);
  bg_.draw();
  glPopMatrix();
}

/**************************************************************************
** APage.cpp: Created on 25 May 2012 by duplom_t
** for class : APage
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "APage.hh"

#include <GL/gl.h>
#include <GL/glu.h>
#include "ModelHandler.hh"

APage::APage(AContent * content,
             const std::string & name,
             const std::string &leftImg,
             const std::string &rightImg)
  : content_(content),
    background_(Bomberman::ModelHandler::get().getModel(name)),
    leftImg_(Bomberman::ModelHandler::get().getModel(leftImg)),
    rightImg_(Bomberman::ModelHandler::get().getModel(rightImg))
{
}

APage::~APage()
{
}

void APage::update(gdl::Input & input, gdl::GameClock &gClock,
                   StatesManager * sMg)
{
  content_->update(input, gClock, sMg);
}

void APage::draw()
{
  glPushMatrix();
  glTranslated(200, 100, 0);
  background_.draw();
  glPopMatrix();
  content_->draw();
}

void APage::drawLeft()
{
  glPushMatrix();
  glTranslated(0, 350, 0);
  leftImg_.draw();
  glPopMatrix();
}

void APage::drawRight()
{
  glPushMatrix();
  glTranslated(1444, 350, 0);
  rightImg_.draw();
  glPopMatrix();
}

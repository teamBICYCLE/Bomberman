/**************************************************************************
** AButton.cpp: Created on 26 May 2012 by duplom_t
** for class : AButton
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "AButton.hh"

#include <GL/gl.h>
#include <GL/glu.h>
#include "ModelHandler.hh"

AButton::AButton(const std::string & normal, const std::string & highlight,
                 const Vector3d & pos)
  : normal_(Bomberman::ModelHandler::get().getModel(normal)),
    hightlight_(Bomberman::ModelHandler::get().getModel(highlight)),
    pos_(pos)
{
}


AButton::~AButton()
{
}

void AButton::update()
{
}

void AButton::draw()
{
  glPushMatrix();
  glTranslated(pos_.x, pos_.y, pos_.z);
  normal_.draw();
  glPopMatrix();
}

void AButton::drawHighlight()
{
  glPushMatrix();
  glTranslated(pos_.x, pos_.y, pos_.z);
  hightlight_.draw();
  glPopMatrix();
}

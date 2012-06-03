/**************************************************************************
** TexturedCube.cpp: Created on 21 May 2012 by duplom_t
** for class : TexturedCube
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "TexturedCube.hh"
#include <iostream>
#include "unavalaibleRessource.hh"

TexturedCube::TexturedCube(const std::string & imgpath)
  : list_(glGenLists(1)), coef_(0.0f), endAnimMax_(0.5f + ((rand() % 151) / 100.0f)),
    endAnim_(endAnimMax_), startAnim_((rand() % 51) / 100.0f), lastTime_(-1)
{
  if (!imgpath.empty())
    img_ = gdl::Image::load(imgpath);
  if (!img_.isValid() && !imgpath.empty())
    throw new unavalaibleRessource(imgpath);
}

TexturedCube::TexturedCube(const AModel &orig)
  : list_(dynamic_cast<const TexturedCube *>(&orig)->list_),
    img_(dynamic_cast<const TexturedCube *>(&orig)->img_),
    coef_(dynamic_cast<const TexturedCube *>(&orig)->coef_),
    endAnimMax_(0.5f + ((rand() % 151) / 100.0f)), endAnim_(endAnimMax_),
    startAnim_((rand() % 51) / 100.0f), lastTime_(-1)
{}

void TexturedCube::draw()
{
  if (coef_ == 0)
    return;
  if (coef_ != 1)
    {
      glScaled(1, 1, coef_);
      glTranslated(0, 0, -(1 - coef_));
    }
  if (img_.isValid())
    {
      glEnable(GL_TEXTURE_2D);
      img_.bind();
    }
  glBegin(GL_QUADS);
  glNormal3d(0, 0, 1);
  glTexCoord2d(0.0f, 0.0f); glVertex3f(1, 1, 1);
  glTexCoord2d(0.0f, 0.5f); glVertex3f(1, 1, 0);
  glTexCoord2d(0.34f, 0.5f); glVertex3f(0, 1, 0);
  glTexCoord2d(0.34f, 0.0f); glVertex3f(0, 1, 1);

  glNormal3d(0, 0, 1);
  glTexCoord2d(0.67f, 0.5f);  glVertex3f(0, 0, 1);
  glTexCoord2d(0.67f, 1.0f); glVertex3f(1, 0, 1);
  glTexCoord2d(1.0f, 1.0f);  glVertex3f(1, 1, 1);
  glTexCoord2d(1.0f, 0.5f); glVertex3f(0, 1, 1);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void TexturedCube::update(gdl::GameClock &clock)
{
  float		now = clock.getTotalGameTime();

  if (lastTime_ == -1)
    lastTime_ = now;
  if (startAnim_ > 0)
    startAnim_ -= (now - lastTime_);
  if (startAnim_ <= 0 && endAnim_ > 0)
    {
      coef_ = 1.0f - (endAnim_ / endAnimMax_);
      endAnim_ -= (now - lastTime_);
    }
  else if (endAnim_ <= 0)
    coef_ = 1.0f;
  lastTime_ = now;
}

AModel &TexturedCube::clone(void)
{
  return *this;
}

void TexturedCube::setBuild(void)
{
  coef_ = 1;
  endAnim_ = 0;
  startAnim_ = 0;
}

bool TexturedCube::getBuild(void) const
{
    if (coef_ == 1 && endAnim_ == 0)
        return true;
    return false;
}

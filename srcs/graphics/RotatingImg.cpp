/**************************************************************************
** RotatingImg.cpp: Created on 22 May 2012 by duplom_t
** for class : RotatingImg
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "RotatingImg.hh"

#include <GL/gl.h>
#include <GL/glut.h>

RotatingImg::RotatingImg(const std::string &imgpath)
  : angle_(0)
{
  if (!imgpath.empty())
    img_ = gdl::Image::load(imgpath);
}

RotatingImg::RotatingImg(const AModel &orig)
  : img_(dynamic_cast<const RotatingImg *>(&orig)->img_), angle_(0)
{
}

RotatingImg::~RotatingImg()
{
}

void RotatingImg::draw()
{
  glTranslated(0.5, 0.5, 0);
  glRotated(angle_, 0.0f, 0.0f, 1.0f);
  glTranslated(-0.5, -0.5, 0);
  if (img_.isValid())
    {
      glEnable(GL_TEXTURE_2D);
      img_.bind();
    }
  glBegin(GL_QUADS);
  glNormal3d(-1, 0, 0);
  glTexCoord2d(0.0f, 0.0f); glVertex3d(1.0f, 0.5f, 1.0f);
  glTexCoord2d(0.0f, 1.0f); glVertex3d(1.0f, 0.5f, 0.0f);
  glTexCoord2d(1.0f, 1.0f); glVertex3d(0.0f, 0.5f, 0.0f);
  glTexCoord2d(1.0f, 0.0f); glVertex3d(0.0f, 0.5f, 1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void RotatingImg::update(gdl::GameClock &clock)
{
  angle_ += 1;
}

AModel &RotatingImg::clone()
{
  return *this;
}


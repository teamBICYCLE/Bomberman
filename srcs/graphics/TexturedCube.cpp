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

TexturedCube::TexturedCube(const std::string & imgpath)
  : list_(glGenLists(1))
{
  if (!imgpath.empty())
    img_ = gdl::Image::load(imgpath);
}

TexturedCube::TexturedCube(const AModel &orig)
  : list_(dynamic_cast<const TexturedCube *>(&orig)->list_),
    img_(dynamic_cast<const TexturedCube *>(&orig)->img_)
{
}

void TexturedCube::draw()
{
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

//  glNormal3d(1, 0, 0);
//  glTexCoord2d(0.34f, 0.0f); glVertex3f(1, 0, 1);
//  glTexCoord2d(0.34f, 0.5f); glVertex3f(1, 0, 0);
//  glTexCoord2d(0.67f, 0.5f);  glVertex3f(1, 1, 0);
//  glTexCoord2d(0.67f, 0.0f); glVertex3f(1, 1, 1);

//  glNormal3d(0, -1, 0);
//  glTexCoord2d(0.67f, 0.0f); glVertex3f(0, 0, 1);
//  glTexCoord2d(0.67f, 0.5f);  glVertex3f(0, 0, 0);
//  glTexCoord2d(1.0f, 0.5f);  glVertex3f(1, 0, 0);
//  glTexCoord2d(1.0f, 0.0f);  glVertex3f(1, 0, 1);

//  glNormal3d(-1, 0, 0);
//  glTexCoord2d(0.0f, 0.5f);  glVertex3f(0, 1, 1);
//  glTexCoord2d(0.0f, 1.0f); glVertex3f(0, 1, 0);
//  glTexCoord2d(0.34f, 1.0f);  glVertex3f(0, 0, 0);
//  glTexCoord2d(0.34f, 0.5f); glVertex3f(0, 0, 1);

//  glNormal3d(0, 0, -1);
//  glTexCoord2d(0.34f, 0.5f); glVertex3f(0, 0, 0);
//  glTexCoord2d(0.34f, 1.0f);  glVertex3f(1, 0, 0);
//  glTexCoord2d(0.67f, 1.0f);  glVertex3f(1, 1, 0);
//  glTexCoord2d(0.67f, 0.5f);  glVertex3f(0, 1, 0);

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
  (void)clock;
}

AModel &TexturedCube::clone()
{
  return *this;
}

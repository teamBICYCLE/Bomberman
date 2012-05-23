/**************************************************************************
** ExplosionBlock.cpp: Created on 23 May 2012 by duplom_t
** for class : ExplosionBlock
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "ExplosionBlock.hh"

#include <GL/gl.h>
#include <GL/glut.h>

ExplosionBlock::ExplosionBlock(const std::string &imgpath)
{
  if (!imgpath.empty())
    img_ = gdl::Image::load(imgpath);
}

ExplosionBlock::ExplosionBlock(const AModel &orig)
  : img_(dynamic_cast<const ExplosionBlock *>(&orig)->img_)
{
}

ExplosionBlock::~ExplosionBlock()
{
}

void ExplosionBlock::draw()
{
  int     offset = iter_ / 16;

  if (img_.isValid())
    {
      glEnable(GL_TEXTURE_2D);
      img_.bind();
    }
  glBegin(GL_QUADS);
  glTexCoord2d(0.25f * (offset / 4), 0.25f * (offset % 4)); glVertex3d(1.0f, 0.5f, 1.0f);
  glTexCoord2d(0.25f * (offset / 4), 0.25f * (offset % 4) + 0.25f); glVertex3d(1.0f, 0.5f, 0.0f);
  glTexCoord2d(0.25f * (offset / 4) + 0.25f, 0.25f * (offset % 4) + 0.25f); glVertex3d(0.0f, 0.5f, 0.0f);
  glTexCoord2d(0.25f * (offset / 4) + 0.25f, 0.25f * (offset % 4)); glVertex3d(0.0f, 0.5f, 1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void ExplosionBlock::update(gdl::GameClock &clock)
{
  iter_++;
  iter_ %= 16 * 16;
}

AModel &ExplosionBlock::clone()
{
  return *this;
}


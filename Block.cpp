//
// Block.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Tue May  8 15:32:24 2012 geoffroy lafontaine
//

#include "Block.hh"

#include <GL/gl.h>

using namespace	Bomberman;

Block::Block(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz,"Block")
{
}

Block::~Block()
{
}

void		Block::update(gdl::GameClock& clock, gdl::Input& keys)
{
  (void)clock;
  (void)keys;
}

void		Block::draw(void)
{
  std::cout << "Drawing block of size: " << sz_ << std::endl;
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x, pos_.y, pos_.z);
  glBegin(GL_QUADS);
  glColor3ub(255, 255, 255);
  glVertex3d(0.0d, 0.0d, 0.0d);
  glVertex3d(0.0d, sz_.y, 0.0d);
  glVertex3d(sz_.x, sz_.y, 0.0d);
  glVertex3d(sz_.x, 0.0d, 0.0d);
  glEnd();
}

const std::string&	Block::type(void) const
{
  return (type_);
}

//
// RangePowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 15:33:03 2012 geoffroy lafontaine
// Last update Thu May 17 17:54:34 2012 lois burg
//

#include "RangePowerup.hh"

using namespace Bomberman;

RangePowerup::RangePowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : APowerup(pos, rot, sz, "RangePowerup")
{
}

RangePowerup::~RangePowerup(void)
{
}

RangePowerup::RangePowerup(const RangePowerup &other)
    : APowerup(other.getPos(), other.getRot(), other.getSize(), other.getType())
{
}

void	RangePowerup::activate(Player& p)
{
  std::cout << "Range up" << std::endl;
  p.setBombRange(p.getBombRange() + 1);
  APowerup::activate(p);
}

void	RangePowerup::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
}

void	RangePowerup::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  glBegin(GL_QUADS);
  glColor3ub(136, 77, 167);
  glVertex3f(1.0F, 1.0F, 1.0F);
  glVertex3f(1.0F, 1.0F, 0);
  glVertex3f(0, 1.0F, 0);
  glVertex3f(0, 1.0F, 1.0F);
  glVertex3f(1.0F, 0, 1.0F);
  glVertex3f(1.0F, 0, 0);
  glVertex3f(1.0F, 1.0F, 0);
  glVertex3f(1.0F, 1.0F, 1.0F);
  glVertex3f(0, 0, 1.0F);
  glVertex3f(0, 0, 0);
  glVertex3f(1.0F, 0, 0);
  glVertex3f(1.0F, 0, 1.0F);
  glVertex3f(0, 1.0F, 1.0F);
  glVertex3f(0, 1.0F, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 1.0F);
  glVertex3f(0, 0, 0);
  glVertex3f(1.0F, 0, 0);
  glVertex3f(1.0F, 1.0F, 0);
  glVertex3f(0, 1.0F, 0);
  glVertex3f(0, 0, 1.0F);
  glVertex3f(1.0F, 0, 1.0F);
  glVertex3f(1.0F, 1.0F, 1.0F);
  glVertex3f(0, 1.0F, 1.0F);
  glEnd();
}

RangePowerup    *RangePowerup::clone(void)
{
  return (new RangePowerup(*this));
}

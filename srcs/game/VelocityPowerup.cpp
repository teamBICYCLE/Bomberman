//
// VelocityPowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 15:35:37 2012 geoffroy lafontaine
// Last update Thu May 17 17:53:46 2012 lois burg
//

#include "VelocityPowerup.hh"

using namespace Bomberman;

VelocityPowerup::VelocityPowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : APowerup(pos, rot, sz, "VelocityPowerup")
{
}

VelocityPowerup::VelocityPowerup(const VelocityPowerup &other)
    : APowerup(other.getPos(), other.getRot(), other.getSize(), other.getType())
{
}

VelocityPowerup::~VelocityPowerup(void)
{
}

void VelocityPowerup::activate(Player& p)
{
  std::cout << "Speed up" << std::endl;
  p.setSpeed(p.getSpeed() + 0.01);
  APowerup::activate(p);
}

void	VelocityPowerup::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
}

void	VelocityPowerup::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  glBegin(GL_QUADS);
  glColor3ub(86, 130, 3);
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

VelocityPowerup *VelocityPowerup::clone(void)
{
    return (new VelocityPowerup(*this));
}

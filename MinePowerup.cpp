//
// MinePowerup.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 17 18:22:54 2012 lois burg
// Last update Thu May 17 18:33:57 2012 lois burg
//

#include "MinePowerup.hh"

using namespace Bomberman;

MinePowerup::MinePowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : APowerup(pos, rot, sz, "MinePowerup")
{
}

MinePowerup::MinePowerup(const MinePowerup &other)
    : APowerup(other.getPos(), other.getRot(), other.getSize(), "MinePowerup")
{
}

MinePowerup::~MinePowerup(void)
{
}

void MinePowerup::activate(Player& p)
{
  int	nbMines = p.getNbMines();

  std::cout << "Mine up" << std::endl;
  if (nbMines < 0)
    p.setNbMines(1);
  else
    p.setNbMines(nbMines + 1);
  APowerup::activate(p);
}

void	MinePowerup::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
}

void	MinePowerup::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  glBegin(GL_QUADS);
  glColor3ub(209, 182, 6);
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

MinePowerup *MinePowerup::clone(void)
{
    return (new MinePowerup(*this));
}

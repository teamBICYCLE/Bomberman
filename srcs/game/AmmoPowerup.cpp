//
// AmmoPowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 15:25:34 2012 geoffroy lafontaine
// Last update Sun May 20 16:15:51 2012 lois burg
//

#include "AmmoPowerup.hh"
#include "ModelHandler.hh"

using namespace Bomberman;

AmmoPowerup::AmmoPowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : APowerup(pos, rot, sz, "AmmoPowerup"), model_(ModelHandler::get().getModel("cube"))
{
}

AmmoPowerup::AmmoPowerup(const AmmoPowerup &other)
    : APowerup(other.getPos(), other.getRot(), other.getSize(), "AmmoPowerup"),
      model_(other.model_)
{
}

AmmoPowerup::~AmmoPowerup(void)
{
}

void AmmoPowerup::activate(Player& p)
{
  if (!toRemove())
    {
      std::cout << "Ammo up" << std::endl;
      p.setNbBombs(p.getNbBombs() + 1);
      APowerup::activate(p);
    }
}

void	AmmoPowerup::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
  model_.update(clock);
}

void	AmmoPowerup::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  model_.draw();
//  glBegin(GL_QUADS);
//  glColor3ub(0, 127, 255);
//  glVertex3f(1.0F, 1.0F, 1.0F);
//  glVertex3f(1.0F, 1.0F, 0);
//  glVertex3f(0, 1.0F, 0);
//  glVertex3f(0, 1.0F, 1.0F);
//  glVertex3f(1.0F, 0, 1.0F);
//  glVertex3f(1.0F, 0, 0);
//  glVertex3f(1.0F, 1.0F, 0);
//  glVertex3f(1.0F, 1.0F, 1.0F);
//  glVertex3f(0, 0, 1.0F);
//  glVertex3f(0, 0, 0);
//  glVertex3f(1.0F, 0, 0);
//  glVertex3f(1.0F, 0, 1.0F);
//  glVertex3f(0, 1.0F, 1.0F);
//  glVertex3f(0, 1.0F, 0);
//  glVertex3f(0, 0, 0);
//  glVertex3f(0, 0, 1.0F);
//  glVertex3f(0, 0, 0);
//  glVertex3f(1.0F, 0, 0);
//  glVertex3f(1.0F, 1.0F, 0);
//  glVertex3f(0, 1.0F, 0);
//  glVertex3f(0, 0, 1.0F);
//  glVertex3f(1.0F, 0, 1.0F);
//  glVertex3f(1.0F, 1.0F, 1.0F);
//  glVertex3f(0, 1.0F, 1.0F);
//  glEnd();
}

AmmoPowerup *AmmoPowerup::clone(void)
{
    return (new AmmoPowerup(*this));
}

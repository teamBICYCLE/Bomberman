//
// VelocityPowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 15:35:37 2012 geoffroy lafontaine
// Last update Sat Jun  2 14:18:57 2012 lois burg
//

#include "VelocityPowerup.hh"
#include "ModelHandler.hh"

using namespace Bomberman;

VelocityPowerup::VelocityPowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : APowerup(pos, rot, sz, "VelocityPowerup"), model_(ModelHandler::get().getModel("speedup"))
{
}

VelocityPowerup::VelocityPowerup(const VelocityPowerup &other)
    : APowerup(other.getPos(), other.getRot(), other.getSize(), other.getType()),
      model_(other.model_)
{
}

VelocityPowerup::~VelocityPowerup(void)
{
}

void VelocityPowerup::activate(Player& p)
{
  if (!toRemove())
    {
      p.setSpeed(p.getSpeed() + 0.01);
      APowerup::activate(p);
    }
}

void	VelocityPowerup::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
  model_.update(clock);
}

void	VelocityPowerup::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  model_.draw();
}

VelocityPowerup *VelocityPowerup::clone(void)
{
    return (new VelocityPowerup(*this));
}

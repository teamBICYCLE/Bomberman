//
// VelocityPowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 15:35:37 2012 geoffroy lafontaine
// Last update Mon May  7 18:31:23 2012 lois burg
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

void VelocityPowerup::activate(Player& p) const
{
  p.setSpeed(p.getSpeed() + 1);
}

void	VelocityPowerup::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
}

void	VelocityPowerup::draw(void)
{
}

const std::string&	VelocityPowerup::type(void) const
{
  return (type_);
}

VelocityPowerup *VelocityPowerup::clone(void)
{
    return (new VelocityPowerup(*this));
}

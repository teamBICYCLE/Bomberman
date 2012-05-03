//
// VelocityPowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Thu May  3 15:35:37 2012 geoffroy lafontaine
// Last update Thu May  3 16:12:48 2012 geoffroy lafontaine
//

#include "VelocityPowerup.hh"

VelocityPowerup::VelocityPowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz, "velocitypowerup")
{
}

VelocityPowerup::~VelocityPowerup(void)
{
}

void VelocityPowerup::activate(Player& p) const
{
  p.setSpeed(getSpeed() + 1);
}

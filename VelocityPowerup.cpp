//
// VelocityPowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Thu May  3 15:35:37 2012 geoffroy lafontaine
// Last update Thu May  3 15:42:04 2012 geoffroy lafontaine
//

#include "VelocityPowerup.hh"

VelocityPowerup::VelocityPowerup(void)
  : AObject("velocitypowerup")
{
}

VelocityPowerup::~VelocityPowerup(void)
{
}

void VelocityPowerup::activate(Player& p) const
{
  p.setSpeed(getSpeed() + 1);
}

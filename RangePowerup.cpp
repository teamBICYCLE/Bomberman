//
// RangePowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Thu May  3 15:33:03 2012 geoffroy lafontaine
// Last update Thu May  3 16:13:31 2012 geoffroy lafontaine
//

#include "RangePowerup.hh"

using namespace Bomberman;

RangePowerup::RangePowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz, "rangepowerup")
{
}

RangePowerup::~RangePowerup(void)
{
}

void RangePowerup::activate(Player& p) const
{
  p.setRange(p.getRange() + 1);
}

//
// AmmoPowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Thu May  3 15:25:34 2012 geoffroy lafontaine
// Last update Thu May  3 16:13:43 2012 geoffroy lafontaine
//

#include "AmmoPowerup.hh"

using namespace Bomberman;

AmmoPowerup::AmmoPowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz, "ammopowerup")
{
}

AmmoPowerup::~AmmoPowerup(void)
{
}

void AmmoPowerup::activate(Player& p) const
{
  p.setBombs(p.getBombs() + 1);
}

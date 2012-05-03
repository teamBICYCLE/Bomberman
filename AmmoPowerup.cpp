//
// AmmoPowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Thu May  3 15:25:34 2012 geoffroy lafontaine
// Last update Thu May  3 15:41:54 2012 geoffroy lafontaine
//

#include "AmmoPowerup.hh"

using namespace Bomberman;

AmmoPowerup::AmmoPowerup(void)
  : AObject("ammopowerup")
{
}

AmmoPowerup::~AmmoPowerup(void)
{
}

void AmmoPowerup::activate(Player& p) const
{
  p.setBombs(p.getBombs() + 1);
}

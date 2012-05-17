//
// APowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 14:37:08 2012 geoffroy lafontaine
// Last update Thu May 17 11:50:23 2012 lois burg
//

#include "APowerup.hh"

using namespace Bomberman;

APowerup::APowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& type)
  : AObject(pos, rot, sz, type)
{
}

APowerup::~APowerup(void)
{
}

void	APowerup::activate(Player &p)
{
  (void)p;
  destroy();
}

void	APowerup::interact(Character *ch)
{
  if (dynamic_cast<Player*>(ch))
    activate(*static_cast<Player*>(ch));
  else
    destroy();
}

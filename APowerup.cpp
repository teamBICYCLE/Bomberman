//
// APowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Thu May  3 14:37:08 2012 geoffroy lafontaine
// Last update Thu May  3 16:12:18 2012 geoffroy lafontaine
//

#include "APowerup.hh"

using namespace Bomberman;

APowerup::APowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz, "powerup")
{
}

APowerup::~APowerup(void)
{
}

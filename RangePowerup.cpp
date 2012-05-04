//
// RangePowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 15:33:03 2012 geoffroy lafontaine
// Last update Fri May  4 10:19:28 2012 lois burg
//

#include "RangePowerup.hh"

using namespace Bomberman;

RangePowerup::RangePowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : APowerup(pos, rot, sz, "RangePowerup")
{
}

RangePowerup::~RangePowerup(void)
{
}

void	RangePowerup::activate(Player& p) const
{
  p.setBombRange(p.getBombRange() + 1);
}

void	RangePowerup::update(gdl::GameClock& clock, gdl::Input& keys)
{
  (void)clock;
  (void)keys;
}

void	RangePowerup::draw(void)
{
}

const std::string&	RangePowerup::type(void) const
{
  return (type_);
}

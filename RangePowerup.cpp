//
// RangePowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 15:33:03 2012 geoffroy lafontaine
// Last update Wed May 16 16:24:57 2012 lois burg
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

RangePowerup::RangePowerup(const RangePowerup &other)
    : APowerup(other.getPos(), other.getRot(), other.getSize(), other.getType())
{
}

void	RangePowerup::activate(Player& p)
{
  std::cout << "Range up" << std::endl;
  p.setBombRange(p.getBombRange() + 1);
  APowerup::activate(p);
}

void	RangePowerup::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
}

void	RangePowerup::draw(void)
{
}

const std::string&	RangePowerup::type(void) const
{
  return (type_);
}

RangePowerup    *RangePowerup::clone(void)
{
  return (new RangePowerup(*this));
}

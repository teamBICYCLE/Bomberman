//
// AmmoPowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 15:25:34 2012 geoffroy lafontaine
// Last update Wed May 16 16:24:51 2012 lois burg
//

#include "AmmoPowerup.hh"

using namespace Bomberman;

AmmoPowerup::AmmoPowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : APowerup(pos, rot, sz, "AmmoPowerup")
{
}

AmmoPowerup::AmmoPowerup(const AmmoPowerup &other)
    : APowerup(other.getPos(), other.getRot(), other.getSize(), "AmmoPowerup")
{
}

AmmoPowerup::~AmmoPowerup(void)
{
}

void AmmoPowerup::activate(Player& p)
{
  std::cout << "Ammo up" << std::endl;
  p.setNbBombs(p.getNbBombs() + 1);
  APowerup::activate(p);
}

void	AmmoPowerup::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
}

void	AmmoPowerup::draw(void)
{
}

const std::string&	AmmoPowerup::type(void) const
{
  return (type_);
}

AmmoPowerup *AmmoPowerup::clone(void)
{
    return (new AmmoPowerup(*this));
}

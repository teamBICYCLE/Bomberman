//
// APowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 14:37:08 2012 geoffroy lafontaine
// Last update Sat May 26 17:48:37 2012 thibault carpentier
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

void	APowerup::interact(Character *ch, std::list<AObject*>& objs)
{
  (void)objs;
  if (dynamic_cast<Player*>(ch))
    activate(*static_cast<Player*>(ch));
  else
    destroy();
}

void	APowerup::interact(Explosion *e, std::list<AObject*>& objs)
{
  (void)e;
  (void)objs;
  destroy();
}


void  APowerup::setDanger(std::vector<std::vector<std::pair<int, int> > > &map, std::list<AObject*>objs,
			  int x, int y) const
{
  (void)x;
  (void)y;
  (void)objs;
  setDangerMap(getPos().x, getPos().y, DANGER_POWERUP, map);
}

//
// Bomb.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 11:50:36 2012 lois burg
// Last update Thu May 10 16:16:59 2012 lois burg
//

#include "Bomb.hh"

using namespace	Bomberman;

Bomb::Bomb(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, int range, int timeOut, Player& owner)
  : AObject(pos, rot, sz, "Bomb"), range_(range), timeOut_(timeOut), owner_(owner), speed_(Vector3d())
{
  model_ = gdl::Model::load("Ressources/assets/bomb.fbx");
}

Bomb::~Bomb()
{
}

void	Bomb::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
  --timeOut_;
  if (!timeOut_)
    {
      //explosion qui tue et ajout des loots de tier 7
      owner_.setNbBombs(owner_.getNbBombs() + 1);
      removeLater_ = true;
    }
  pos_ += speed_;
}

void	Bomb::draw(void)
{
}

const std::string&	Bomb::type(void) const
{
  return (type_);
}

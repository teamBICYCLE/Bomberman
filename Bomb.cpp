//
// Bomb.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 11:50:36 2012 lois burg
// Last update Fri May 11 18:12:43 2012 lois burg
//

#include <algorithm>
#include "Explosion.hh"
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
    destroy(objs);
  pos_ += speed_;
}

void	Bomb::explode(std::list<AObject*>& objs)
{
  Explosion	*e = new Explosion(pos_, sz_, 1);

  (void)objs;
  //explosion qui tue et ajout des loots de tier 7
  objs.push_back(e);
  for (int i = 1; i <= range_; ++i)
    {
    }
  std::for_each(objs.begin(), objs.end(), [](AObject *obj) -> void {
      //check si possibilite de mettre cette explosion ou non
      (void)obj;
    });
  owner_.setNbBombs(owner_.getNbBombs() + 1);
}

void	Bomb::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x, pos_.y, pos_.z);
  glScaled(0.0035, 0.0035,0.0035);
  glRotated(90, 1, 0, 0);
  model_.draw();
}

void	Bomb::adjustPos(void)
{
  pos_.x = (int)pos_.x;
  pos_.y = (int)pos_.y;
  pos_.z = (int)pos_.z;
}

const std::string&	Bomb::type(void) const
{
  return (type_);
}

void	Bomb::destroy(std::list<AObject*>& objs)
{
  explode(objs);
  AObject::destroy();
}

//
// Bomb.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 11:50:36 2012 lois burg
// Last update Sun May 13 16:11:05 2012 lois burg
//

#include <algorithm>
#include "Explosion.hh"
#include "Bomb.hh"
#include "Brick.hh"

using namespace	Bomberman;

Bomb::Bomb(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, int range, int timeOut, Player& owner)
  : AObject(pos, rot, sz, "Bomb"), range_(range), timeOut_(timeOut), owner_(owner), speed_(Vector3d()), timeCreation_(-1)
{
  model_ = gdl::Model::load("Ressources/assets/bomb.fbx");
}

Bomb::~Bomb()
{
}

void	Bomb::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)keys;
  (void)objs;
  if (timeCreation_ == -1)
    timeCreation_ = clock.getTotalGameTime();
  if (clock.getTotalGameTime() - timeCreation_ >= timeOut_)
    destroy(objs);
  pos_ += speed_;
}

void	Bomb::explode(std::list<AObject*>& objs)
{
  Explosion	*e = new Explosion(pos_, Vector3d(1, 1, 0), 1);
  bool		upInvalid = false;
  bool		downInvalid = false;
  bool		leftInvalid = false;
  bool		rightInvalid = false;

  (void)objs;
  (void)e;
  //explosion qui tue et ajout des loots de tier 7
  objs.push_back(new Explosion(*e));
  for (int i = 1; i <= range_; ++i)
    {
      // std::cout << std::boolalpha << "Up: " << upInvalid << ", Down: " << downInvalid << ", Left: " << leftInvalid << ", Right: " << rightInvalid << std::noboolalpha << std::endl;
      e->setPos(pos_ + Vector3d(0, -i, 0));
      checkPosition(e, upInvalid, objs);
      e->setPos(pos_ + Vector3d(0, i, 0));
      checkPosition(e, downInvalid, objs);
      e->setPos(pos_ + Vector3d(-i, 0, 0));
      checkPosition(e, leftInvalid, objs);
      e->setPos(pos_ + Vector3d(i, 0, 0));
      checkPosition(e, rightInvalid, objs);
      // std::cout << std::boolalpha << "Up: " << upInvalid << ", Down: " << downInvalid << ", Left: " << leftInvalid << ", Right: " << rightInvalid << std::noboolalpha << std::endl;
      // std::cout << "--------------------" << std::endl;
    }
  owner_.setNbBombs(owner_.getNbBombs() + 1);
}

void	Bomb::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x + 0.5, pos_.y + 0.5, pos_.z);
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

void	Bomb::checkPosition(Explosion *e, bool& isInvalid, std::list<AObject*>& objs)
{
  if (!isInvalid)
    std::for_each(objs.begin(), objs.end(), [&](AObject *obj) -> void {
	if (e->getBBox().collideWith(obj))
	  {
	    if (dynamic_cast<Character*>(obj))
	      obj->destroy();
	    else if (dynamic_cast<Bomb*>(obj))
	      dynamic_cast<Bomb*>(obj)->setTimeOut(0.0f);
	    else if (dynamic_cast<Brick*>(obj))
	      dynamic_cast<Brick*>(obj)->destroy(objs);
	    if (!dynamic_cast<Character*>(obj))
	      isInvalid = true;
	  }
      });
  if (!isInvalid)
    objs.push_back(new Explosion(*e));
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

void	Bomb::setTimeOut(const float timeOut)
{
  timeOut_ = timeOut;
}

float	Bomb::getTimeOut(void) const
{
  return (timeOut_);
}

/* Serialization */

void Bomb::serialize(QDataStream &out) const
{
    (void)out;
}

void Bomb::unserialize(QDataStream &in)
{
    (void)in;
}

void Bomb::sInit(void)
{

}

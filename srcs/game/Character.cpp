//
// Character.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 17:07:54 2012 lois burg
// Last update Sat Jun  2 15:23:48 2012 lois burg
//

#include "Character.hh"
#include "Explosion.hh"

using namespace	Bomberman;

int	Character::CharacterId = 0;

Character::Character(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& modelName, uint life, double speed)
  : AObject(pos, rot, sz, modelName), life_(life), speed_(speed),
    speedAdapter_(100), moved_(false), isInvincible_(false), id_(Character::CharacterId)
{
  ++Character::CharacterId;
}

Character::Character(const std::string &type)
    : AObject(Vector3d(), Vector3d(), Vector3d(), type),
      life_(0), speed_(0), speedAdapter_(100), moved_(false), isInvincible_(false), id_(Character::CharacterId)
{
  ++Character::CharacterId;
}

Character::~Character()
{
}

void	Character::turnLeft(void)
{
  pos_ -= Vector3d(getSpeed(), 0, 0);
  rot_.y = 270;
  moved_ = true;
}

void	Character::turnRight(void)
{
  pos_ += Vector3d(getSpeed(), 0, 0);
  rot_.y = 90;
  moved_ = true;
}

void	Character::turnUp(void)
{
  pos_ -= Vector3d(0, getSpeed(), 0);
  rot_.y = 0;
  moved_ = true;
}

void	Character::turnDown(void)
{
  pos_ += Vector3d(0, getSpeed(), 0);
  rot_.y = 180;
  moved_ = true;
 }

void	Character::takeDamage(uint damage)
{
  if (!isInvincible_)
    {
      if (life_ > 0)
	life_ -= damage;
      if (!life_)
	destroy();
    }
}

void	Character::bump(const Vector3d& bumpPos)
{
  (void)bumpPos;
  if (bBox_->isAbove() || bBox_->isBelow())
    pos_.y = save_.y;
  if (bBox_->isLeft() || bBox_->isRight())
    pos_.x = save_.x;
}

const BoundingBox	*Character::getBBox(void) const
{
  return (bBox_);
}

const Vector3d&		Character::getSavedPos(void) const
{
  return (save_);
}

double      Character::getSpeed(void) const
{
  return (speedAdapter_ * speed_) / 100;
}

uint		Character::getLife(void) const
{
  return (life_);
}

int	Character::getId(void) const
{
  return (id_);
}

bool	Character::isInvincible(void) const
{
  return (isInvincible_);
}

int	Character::getScoreValue(void) const
{
  return (10);
}

void	Character::setInvincible(bool b)
{
  isInvincible_ = b;
}

void		Character::setLife(const uint life)
{
  life_ = life;
}

void		Character::setSpeed(const double speed)
{
  speed_ = speed;
}

void	Character::destroy(void)
{
  if (!isInvincible_)
    AObject::destroy();
}

void	Character::interact(Explosion *e, std::list<AObject*>& objs)
{
  (void)objs;
  if (this != &e->getOwner() && !isInvincible())
    e->getOwner().addScore(getScoreValue());
  takeDamage(e->getDamage());
}

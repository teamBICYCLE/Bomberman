//
// Character.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 17:07:54 2012 lois burg
// Last update Sat May 12 15:10:51 2012 geoffroy lafontaine
//

#include "Character.hh"

using namespace	Bomberman;

Character::Character(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& modelName, uint life, double speed)
  : AObject(pos, rot, sz, modelName), life_(life), speed_(speed),
    speedAdapter_(100), moved_(false)
{
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
  if (life_ > 0)
    life_ -= damage;
}

double      Character::getSpeed(void) const
{
  return (speedAdapter_ * speed_) / 100;
}

uint		Character::getLife(void) const
{
  return (life_);
}

void		Character::setLife(const uint life)
{
  life_ = life;
}

void		Character::setSpeed(const double speed)
{
  speed_ = speed;
}


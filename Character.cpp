//
// Character.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 17:07:54 2012 lois burg
// Last update Thu May 10 17:32:05 2012 lois burg
//

#include "Character.hh"

using namespace	Bomberman;

Character::Character(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& modelName, uint life, double speed)
  : AObject(pos, rot, sz, modelName), life_(life), speed_(speed), speedAdapter_(100), bBox_(pos_, sz_)
{
}

Character::~Character()
{
}

void	Character::turnLeft(void)
{
  pos_ -= Vector3d(getSpeed(), 0, 0);
  rot_.y = 270;
}

void	Character::turnRight(void)
{
  pos_ += Vector3d(getSpeed(), 0, 0);
  rot_.y = 90;
}

void	Character::turnUp(void)
{
  pos_ -= Vector3d(0, getSpeed(), 0);
  rot_.y = 0;
}

void	Character::turnDown(void)
{
  pos_ += Vector3d(0, getSpeed(), 0);
  rot_.y = 180;
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

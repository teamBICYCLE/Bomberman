//
// BoundingBox.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 15:01:48 2012 lois burg
// Last update Sun May 13 16:55:27 2012 lois burg
//

#include "Player.hh"
#include "BoundingBox.hh"

using namespace Bomberman;

BoundingBox::BoundingBox(const Vector3d& pos, const Vector3d& sz, const AObject *owner)
  : pos_(pos), sz_(sz), owner_(owner), above_(false), below_(false), left_(false), right_(false)
{
}

BoundingBox::BoundingBox(const BoundingBox &other)
    : pos_(other.pos_), sz_(other.sz_), owner_(other.owner_),
      above_(other.above_), below_(other.below_),
      left_(other.left_), right_(other.right_)
{
}

BoundingBox::~BoundingBox()
{
}

bool	BoundingBox::isAbove(void) const
{
  return (above_);
}

bool	BoundingBox::isBelow(void) const
{
  return (below_);
}

bool	BoundingBox::isLeft(void) const
{
  return (left_);
}

bool	BoundingBox::isRight(void) const
{
  return (right_);
}

bool	BoundingBox::collideWith(const AObject *obj)
{
  if (owner_ == obj || pos_.distance(obj->getPos()) > 2)
    return (false);
  above_ = collideUp(obj);
  below_ = collideDown(obj);
  left_ = collideLeft(obj);
  right_ = collideRight(obj);

  // if (above_)
  //   std::cout << "Above!" << std::endl;
  // if (below_)
  //   std::cout << "Below!" << std::endl;
  // if (right_)
  //   std::cout << "Right!" << std::endl;
  // if (left_)
  //   std::cout << "Left!" << std::endl;
  // if (above_ || below_ || left_ || right_)
  //   std::cout << "Collingind with " << obj->getType() << std::endl;

  return (above_ || below_ || left_ || right_);
}

bool	BoundingBox::collideLeft(const AObject *obj)
{
  if (obj->getPos() == pos_)
    return (true);
  if (obj->getPos().x < pos_.x)
    if (((obj->getPos().y <= pos_.y && (obj->getPos().x + obj->getSize().x) > pos_.x && (obj->getPos().y + obj->getSize().y) > pos_.y) ||
	 (obj->getPos().y > pos_.y && (obj->getPos().x + obj->getSize().x) > pos_.x && obj->getPos().y < (pos_.y + sz_.y))))
      return (true);
  return (false);
}

bool	BoundingBox::collideRight(const AObject *obj)
{
  if (obj->getPos() == pos_)
    return (true);
  if (obj->getPos().x > pos_.x)
    if (((obj->getPos().y <= pos_.y && obj->getPos().x < (pos_.x + sz_.x) && (obj->getPos().y + obj->getSize().y) > pos_.y) ||
	 (obj->getPos().y > pos_.y && obj->getPos().x < (pos_.x + sz_.x) && obj->getPos().y < (pos_.y + sz_.y))))
      return (true);
  return (false);
}

bool	BoundingBox::collideUp(const AObject *obj)
{
  if (obj->getPos() == pos_)
    return (true);
  if (obj->getPos().y < pos_.y)
    if (((obj->getPos().x <= pos_.x && (obj->getPos().x + obj->getSize().x) > pos_.x && (obj->getPos().y + obj->getSize().y) > pos_.y) ||
	 (obj->getPos().x > pos_.x && obj->getPos().x < (pos_.x + sz_.x) && (obj->getPos().y + obj->getSize().y) > pos_.y)))
      return (true);
  return (false);
}

bool	BoundingBox::collideDown(const AObject *obj)
{
  if (obj->getPos() == pos_)
    return (true);
  if (obj->getPos().y > pos_.y)
    if (((obj->getPos().x <= pos_.x && (obj->getPos().x + obj->getSize().x) > pos_.x && obj->getPos().y < (pos_.y + sz_.y)) ||
	 (obj->getPos().x > pos_.x && obj->getPos().x < (pos_.x + sz_.x) && obj->getPos().y < (pos_.y + sz_.y))))
      return (true);
  return (false);
}

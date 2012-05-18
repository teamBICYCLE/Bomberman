//
// BoundingBox.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 15:01:48 2012 lois burg
// Last update Fri May 18 16:33:53 2012 lois burg
//

#include "Player.hh"
#include "BoundingBox.hh"

using namespace Bomberman;

BoundingBox::BoundingBox(const Vector3d& pos, const Vector3d& sz, const AObject *owner)
  : pos_(pos), sz_(sz), owner_(owner), above_(false), below_(false), left_(false), right_(false)
{
}

BoundingBox::BoundingBox(const BoundingBox &other, const AObject *owner)
    : pos_(other.pos_), sz_(other.sz_), owner_(owner),
      above_(other.above_), below_(other.below_),
      left_(other.left_), right_(other.right_)
{
}

BoundingBox::~BoundingBox()
{
}

void	BoundingBox::resetColliding(void)
{
  above_ = false;
  right_ = false;
  below_ = false;
  left_ = false;
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
  collideUp(obj);
  collideDown(obj);
  collideLeft(obj);
  collideRight(obj);

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
  left_ = false;
  if (obj->getPos() == pos_)
    left_ = true;
  if (!left_ && obj->getPos().x < pos_.x && (obj->getPos().x + obj->getSize().x) > pos_.x)
    if ((obj->getPos().y <= pos_.y && (obj->getPos().y + obj->getSize().y) > pos_.y) ||
	 (obj->getPos().y > pos_.y && obj->getPos().y < (pos_.y + sz_.y)))
      left_ = true;
  return (left_);
}

bool	BoundingBox::collideRight(const AObject *obj)
{
  right_ = false;
  if (obj->getPos() == pos_)
    right_ = true;
  if (!right_ && obj->getPos().x > pos_.x && obj->getPos().x < (pos_.x + sz_.x))
    if ((obj->getPos().y <= pos_.y && (obj->getPos().y + obj->getSize().y) > pos_.y) ||
	 (obj->getPos().y > pos_.y && obj->getPos().y < (pos_.y + sz_.y)))
      right_ = true;
  return (right_);
}

bool	BoundingBox::collideUp(const AObject *obj)
{
  above_ = false;
  if (obj->getPos() == pos_)
    above_ = true;
  if (!above_ && obj->getPos().y < pos_.y && (obj->getPos().y + obj->getSize().y) > pos_.y)
  if ((obj->getPos().x <= pos_.x && (obj->getPos().x + obj->getSize().x) > pos_.x) ||
       (obj->getPos().x > pos_.x && obj->getPos().x < (pos_.x + sz_.x)))
    above_ = true;
  return (above_);
}

bool	BoundingBox::collideDown(const AObject *obj)
{
  below_ = false;
  if (obj->getPos() == pos_)
    below_ = true;
  if (!below_ && obj->getPos().y > pos_.y && obj->getPos().y < (pos_.y + sz_.y))
    if ((obj->getPos().x <= pos_.x && (obj->getPos().x + obj->getSize().x) > pos_.x) ||
	 (obj->getPos().x > pos_.x && obj->getPos().x < (pos_.x + sz_.x)))
      below_ = true;
  return (below_);
}

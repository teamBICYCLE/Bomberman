//
// BoundingBox.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 15:01:48 2012 lois burg
// Last update Thu May 10 16:44:20 2012 lois burg
//

#include "BoundingBox.hh"

using namespace Bomberman;

BoundingBox::BoundingBox(const Vector3d& pos, const Vector3d& sz)
  : pos_(pos), sz_(sz), above_(false), below_(false), left_(false), right_(false)
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
  above_ = collideUp(obj);
  below_ = collideDown(obj);
  left_ = collideLeft(obj);
  right_ = collideRight(obj);
  return (above_ || below_ || left_ || right_);
}

bool	BoundingBox::collideLeft(const AObject *obj)
{
  if (!left_ && obj->getPos().x < pos_.x)
    if (((obj->getPos().y <= pos_.y && (obj->getPos().x + obj->getSize().x) > pos_.x && (obj->getPos().y + obj->getSize().y) > pos_.y) ||
	 (obj->getPos().y > pos_.y && (obj->getPos().x + obj->getSize().x) > pos_.x && obj->getPos().y < (pos_.y + sz_.y))))
      return (true);
  return (false);
}

bool	BoundingBox::collideRight(const AObject *obj)
{
  if (!right_ && obj->getPos().x > pos_.x)
    if (((obj->getPos().y <= pos_.y && obj->getPos().x < (pos_.x + sz_.x) && (obj->getPos().y + obj->getSize().y) > pos_.y) ||
	 (obj->getPos().y > pos_.y && obj->getPos().x < (pos_.x + sz_.x) && obj->getPos().y < (pos_.y + sz_.y))))
      return (true);
  return (false);
}

bool	BoundingBox::collideUp(const AObject *obj)
{
  if (!above_ && obj->getPos().y < pos_.y)
    if (((obj->getPos().x <= pos_.x && (obj->getPos().x + obj->getSize().x) > pos_.x && (obj->getPos().y + obj->getSize().y) > pos_.y) ||
	 (obj->getPos().x > pos_.x && obj->getPos().x < (pos_.x + sz_.x) && (obj->getPos().y + obj->getSize().y) > pos_.y)))
      return (true);
  return (false);
}

bool	BoundingBox::collideDown(const AObject *obj)
{
  if (!below_ && obj->getPos().y > pos_.y)
    if (((obj->getPos().x <= pos_.x && (obj->getPos().x + obj->getSize().x) > pos_.x && obj->getPos().y < (pos_.y + sz_.y)) ||
	 (obj->getPos().x > pos_.x && obj->getPos().x < (pos_.x + sz_.x) && obj->getPos().y < (pos_.y + sz_.y))))
      return (true);
  return (false);
}

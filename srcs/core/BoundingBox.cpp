//
// BoundingBox.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 15:01:48 2012 lois burg
// Last update Sun Jun  3 19:40:46 2012 lois burg
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

bool	 BoundingBox::collideWith(const Vector3d &pos, const Vector3d &sz)
{
  if (pos_.distance(pos) > 2)
    return (false);
  collideUp(pos, sz);
  collideDown(pos, sz);
  collideLeft(pos, sz);
  collideRight(pos, sz);
  return (above_ || below_ || left_ || right_);
}

bool	BoundingBox::collideWith(const AObject *obj)
{
  Vector3d sz;
  Vector3d pos;

  pos = obj->getPos();
  sz = obj->getSize();
  if (owner_ == obj || pos_.distance(obj->getPos()) > 2)
    return (false);
  collideUp(pos, sz);
  collideDown(pos, sz);
  collideLeft(pos, sz);
  collideRight(pos, sz);
  return (above_ || below_ || left_ || right_);
}

bool	BoundingBox::collideLeft(const Vector3d &pos, const Vector3d &sz)
{
  left_ = false;
  if (pos == pos_)
    left_ = true;
  if (!left_ && pos.x < pos_.x && (pos.x + sz.x) > pos_.x)
    if ((pos.y <= pos_.y && (pos.y + sz.y) > pos_.y) ||
	 (pos.y > pos_.y && pos.y < (pos_.y + sz_.y)))
      left_ = true;
  return (left_);
}

bool	BoundingBox::collideRight(const Vector3d &pos, const Vector3d &sz)
{
  right_ = false;
  if (pos == pos_)
    right_ = true;
  if (!right_ && pos.x > pos_.x && pos.x < (pos_.x + sz_.x))
    if ((pos.y <= pos_.y && (pos.y + sz.y) > pos_.y) ||
	 (pos.y > pos_.y && pos.y < (pos_.y + sz_.y)))
      right_ = true;
  return (right_);
}

bool	BoundingBox::collideUp(const Vector3d &pos, const Vector3d &sz)
{
  above_ = false;
  if (pos == pos_)
    above_ = true;
  if (!above_ && pos.y < pos_.y && (pos.y + sz.y) > pos_.y)
    if ((pos.x <= pos_.x && (pos.x + sz.x) > pos_.x) ||
	(pos.x > pos_.x && pos.x < (pos_.x + sz_.x)))
      above_ = true;
  return (above_);
}

bool	BoundingBox::collideDown(const Vector3d &pos, const Vector3d &sz)
{
  below_ = false;
  if (pos == pos_)
    below_ = true;
  if (!below_ && pos.y > pos_.y && pos.y < (pos_.y + sz_.y))
    if ((pos.x <= pos_.x && (pos.x + sz .x) > pos_.x) ||
	 (pos.x > pos_.x && pos.x < (pos_.x + sz_.x)))
      below_ = true;
  return (below_);
}

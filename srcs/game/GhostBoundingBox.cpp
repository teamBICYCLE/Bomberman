//
// GhostBoundingBox.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May 17 16:09:31 2012 geoffroy lafontaine
// Last update Sat Jun  2 16:27:52 2012 lois burg
//

#include "Brick.hh"
#include "Ghost.hh"
#include "GhostBoundingBox.hh"

using namespace Bomberman;

GhostBoundingBox::GhostBoundingBox(const Vector3d& pos, const Vector3d& sz, const AObject *owner)
  : BoundingBox(pos, sz, owner)
{
}

GhostBoundingBox::GhostBoundingBox(const GhostBoundingBox &other, const AObject *owner)
  : BoundingBox(other.pos_, other.sz_, owner)
{
}

GhostBoundingBox::~GhostBoundingBox()
{
}

bool	GhostBoundingBox::collideWith(const AObject *obj)
{
  if (obj->getType() == "Brick")
    return (false);
  if (owner_ == obj || pos_.distance(obj->getPos()) > 2)
    return (false);
  above_ = collideUp(obj->getPos(), obj->getSize());
  below_ = collideDown(obj->getPos(), obj->getSize());
  left_ = collideLeft(obj->getPos(), obj->getSize());
  right_ = collideRight(obj->getPos(), obj->getSize());
  return (above_ || below_ || left_ || right_);
}

bool	GhostBoundingBox::collideWith(const Vector3d &pos, const Vector3d &size)
{
  if (pos_.distance(pos) > 2)
    return (false);
  above_ = collideUp(pos, size);
  below_ = collideDown(pos, size);
  left_ = collideLeft(pos, size);
  right_ = collideRight(pos, size);
  return (above_ || below_ || left_ || right_);
}

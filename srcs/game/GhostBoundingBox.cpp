//
// GhostBoundingBox.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Thu May 17 16:09:31 2012 geoffroy lafontaine
// Last update Thu May 17 16:45:25 2012 geoffroy lafontaine
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
  if (dynamic_cast<const Brick*>(obj))
    return (false);
  if (owner_ == obj || pos_.distance(obj->getPos()) > 2)
    return (false);
  above_ = collideUp(obj);
  below_ = collideDown(obj);
  left_ = collideLeft(obj);
  right_ = collideRight(obj);
  return (above_ || below_ || left_ || right_);
}

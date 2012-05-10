//
// AObject.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:33:56 2012 lois burg
// Last update Thu May 10 14:31:13 2012 lois burg
//

#include "AObject.hh"

using namespace Bomberman;

AObject::AObject(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& modelName)
  : pos_(pos), rot_(rot), sz_(sz), // model_(getModelByName(modelName)),
    type_(modelName), removeLater_(false)
{
}

AObject::~AObject(void)
{
}

void AObject::setPos(const Vector3d &pos)
{
    pos_ = pos;
}

void AObject::setRot(const Vector3d &rot)
{
    rot_ = rot;
}

void AObject::setSize(const Vector3d &sz)
{
    sz_ = sz;
}

const Vector3d &AObject::getPos(void) const
{
    return pos_;
}

const Vector3d &AObject::getRot(void) const
{
    return rot_;
}

const Vector3d &AObject::getSize(void) const
{
    return sz_;
}

const std::string &AObject::getType(void) const
{
    return type_;
}

bool	AObject::toRemove(void) const
{
  return (removeLater_);
}

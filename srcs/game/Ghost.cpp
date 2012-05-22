//
// Ghost.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May 17 15:35:19 2012 geoffroy lafontaine
// Last update Fri May 18 17:47:04 2012 Jonathan Machado
//

#include <algorithm>
#include "Brick.hh"
#include "Bomb.hh"
#include "Ghost.hh"
#include "GhostBoundingBox.hh"

using namespace Bomberman;

Ghost::Ghost(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, Thinking::Brain *b, uint damage)
  : Monster(pos, rot, sz, b, damage)
{
  std::cout << "Ghost created." << std::endl;
  brainScript_->compileFile(GHOST_SCRIPT);
  bBox_ = new GhostBoundingBox(pos_, sz_, this);
  model_ = gdl::Model::load("Ressources/Assets/marvin.fbx");
  model_.cut_animation(model_, "Take 001", 0, 35, "start");
  model_.cut_animation(model_, "Take 001", 36, 54, "run");
  model_.cut_animation(model_, "Take 001", 55, 120, "stop");
  actionsMap_.insert(std::make_pair(Bomberman::LEFT, &Character::turnLeft));
  actionsMap_.insert(std::make_pair(Bomberman::RIGHT, &Character::turnRight));
  actionsMap_.insert(std::make_pair(Bomberman::UP, &Character::turnUp));
  actionsMap_.insert(std::make_pair(Bomberman::DOWN, &Character::turnDown));
}

Ghost::Ghost(const Ghost &other)
  : Monster(other.pos_, other.rot_, other.sz_, other.brainScript_, other.damage_)
{
    brainScript_->compileFile(GHOST_SCRIPT);
    bBox_ = new GhostBoundingBox(other.pos_, other.sz_, this);
    model_ = other.model_;
    actionsMap_ = other.actionsMap_;
}

Ghost::Ghost()
  : Monster()
{
  brainScript_->compileFile(GHOST_SCRIPT);
  bBox_ = new GhostBoundingBox(Vector3d(), Vector3d(), this);
  model_ = gdl::Model::load("Ressources/Assets/marvin.fbx");
  model_.cut_animation(model_, "Take 001", 0, 35, "start");
  model_.cut_animation(model_, "Take 001", 36, 54, "run");
  model_.cut_animation(model_, "Take 001", 55, 120, "stop");
  actionsMap_.insert(std::make_pair(Bomberman::LEFT, &Character::turnLeft));
  actionsMap_.insert(std::make_pair(Bomberman::RIGHT, &Character::turnRight));
  actionsMap_.insert(std::make_pair(Bomberman::UP, &Character::turnUp));
  actionsMap_.insert(std::make_pair(Bomberman::DOWN, &Character::turnDown));
}

Ghost::~Ghost()
{
}

/* Serialization */

void Ghost::serialize(QDataStream &out) const
{
    pos_.serialize(out);
    rot_.serialize(out);
    sz_.serialize(out);
    out << removeLater_;
    out << life_;
    out << speed_;
    out << speedAdapter_;
    out << moved_;
    out << id_;
}

void Ghost::unserialize(QDataStream &in)
{
    pos_.unserialize(in);
    rot_.unserialize(in);
    sz_.unserialize(in);
    in >> removeLater_;
    in >> life_;
    in >> speed_;
    in >> speedAdapter_;
    in >> moved_;
    in >> id_;
}

void Ghost::sInit(void)
{
    qRegisterMetaTypeStreamOperators<Ghost>("Ghost");
    qMetaTypeId<Ghost>();
}

QDataStream &operator<<(QDataStream &out, const Ghost &m)
{
    m.serialize(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Ghost &m)
{
    m.unserialize(in);
    return in;
}

void    Ghost::toQvariant(QSettings &w)
{
    w.setValue("Ghost", qVariantFromValue(*this));
}

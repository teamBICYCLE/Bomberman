//
// Ghost.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May 17 15:35:19 2012 geoffroy lafontaine
// Last update Sun Jun  3 12:18:33 2012 thibault carpentier
//

#include <algorithm>
#include "Brick.hh"
#include "Bomb.hh"
#include "Ghost.hh"
#include "GhostBoundingBox.hh"
#include "ModelHandler.hh"

using namespace Bomberman;

Ghost::Ghost(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, Thinking::Brain *b, uint damage)
  : Monster(pos, rot, sz, b, damage)
{
  std::cout << "Ghost created." << std::endl;
  //  brainScript_->compileFile(GHOST_SCRIPT);
  bBox_ = new GhostBoundingBox(pos_, sz_, this);
  actionsMap_.insert(std::make_pair(Bomberman::LEFT, &Character::turnLeft));
  actionsMap_.insert(std::make_pair(Bomberman::RIGHT, &Character::turnRight));
  actionsMap_.insert(std::make_pair(Bomberman::UP, &Character::turnUp));
  actionsMap_.insert(std::make_pair(Bomberman::DOWN, &Character::turnDown));
}

Ghost::Ghost(const Ghost &other)
  : Monster(other.pos_, other.rot_, other.sz_, other.brainScript_, other.damage_)
{
  //    brainScript_->compileFile(GHOST_SCRIPT);
    bBox_ = new GhostBoundingBox(other.pos_, other.sz_, this);
    actionsMap_ = other.actionsMap_;
}

Ghost::Ghost()
  : Monster()
{
  //  brainScript_->compileFile(GHOST_SCRIPT);
  bBox_ = new GhostBoundingBox(Vector3d(), Vector3d(), this);
  actionsMap_.insert(std::make_pair(Bomberman::LEFT, &Character::turnLeft));
  actionsMap_.insert(std::make_pair(Bomberman::RIGHT, &Character::turnRight));
  actionsMap_.insert(std::make_pair(Bomberman::UP, &Character::turnUp));
  actionsMap_.insert(std::make_pair(Bomberman::DOWN, &Character::turnDown));
}

Ghost::~Ghost()
{}

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

void    Ghost::toQvariant(QSettings &w) const
{
    w.setValue("Ghost", qVariantFromValue(*this));
}

void	Ghost::setVirtualPheromones(std::vector<std::vector<std::pair<int, int> > > &map,
				     std::list<AObject*>objs,
				     int x, int y) const
{
  (void)x;
  (void)y;
  (void)objs;
  if (map[(pos_.y + 0.001)][(pos_.x + 0.001)].second != PHEROMONE_PLAYER)
    map[(pos_.y + 0.001)][(pos_.x + 0.001)].second = PHEROMONE_MONSTER;
}

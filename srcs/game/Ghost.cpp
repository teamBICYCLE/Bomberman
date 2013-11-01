//
// Ghost.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May 17 15:35:19 2012 geoffroy lafontaine
// Last update Sun Jun  3 22:54:35 2012 Jonathan Machado
//

#include <algorithm>
#include "Brick.hh"
#include "Bomb.hh"
#include "Ghost.hh"
#include "GhostBoundingBox.hh"
#include "ModelHandler.hh"

using namespace Bomberman;

Ghost::Ghost(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, Thinking::Brain *b, uint damage)
  : Monster(pos, rot, sz, b, damage, "ghost")
{
  bBox_ = new GhostBoundingBox(pos_, sz_, this);
  actionsMap_.insert(std::make_pair(Bomberman::LEFT, &Character::turnLeft));
  actionsMap_.insert(std::make_pair(Bomberman::RIGHT, &Character::turnRight));
  actionsMap_.insert(std::make_pair(Bomberman::UP, &Character::turnUp));
  actionsMap_.insert(std::make_pair(Bomberman::DOWN, &Character::turnDown));
}

Ghost::Ghost(const Ghost &other)
  : Monster(other, "ghost")
{
    bBox_ = new GhostBoundingBox(other.pos_, other.sz_, this);
    actionsMap_ = other.actionsMap_;
}

Ghost::Ghost()
  : Monster()
{
  bBox_ = new GhostBoundingBox(Vector3d(), Vector3d(), this);
  actionsMap_.insert(std::make_pair(Bomberman::LEFT, &Character::turnLeft));
  actionsMap_.insert(std::make_pair(Bomberman::RIGHT, &Character::turnRight));
  actionsMap_.insert(std::make_pair(Bomberman::UP, &Character::turnUp));
  actionsMap_.insert(std::make_pair(Bomberman::DOWN, &Character::turnDown));
}

Ghost::~Ghost()
{}

void Ghost::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  brainScript_->selectFct("thinkingGhost");
  brainScript_->addParam(pos_.x);
  brainScript_->addParam(pos_.y);
  brainScript_->callFct(1);
  Monster::update(clock, brainScript_->getDecision(), objs);
  (void)keys;
}

void		Ghost::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x + 0.3, pos_.y + 0.3, pos_.z + 1.2 + h_);
  glScaled(0.3, 0.3, 0.43);
  glRotated(90, 1, 0, 0);
  glRotated(rot_.y, 0, 1, 0);
  this->model_.draw();
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
  out << brainScript_->getX();
  out << brainScript_->getY();
}

void Ghost::unserialize(QDataStream &in)
{
  int x, y;
  pos_.unserialize(in);
  rot_.unserialize(in);
  sz_.unserialize(in);
  in >> removeLater_;
  in >> life_;
  in >> speed_;
  in >> speedAdapter_;
  in >> moved_;
  in >> id_;
  in >> x;
  in >> y;
  brainScript_ = Thinking::Brain::getBrain(x, y);
  brainScript_->compileFile(MONSTER_SCRIPT);
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

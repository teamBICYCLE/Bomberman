//
// Monster.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Sat May 12 09:47:20 2012 geoffroy lafontaine
// Last update Sat Jun  2 16:27:45 2012 lois burg
//

#include <algorithm>
#include "Brick.hh"
#include "Bomb.hh"
#include "Monster.hh"
#include "ModelHandler.hh"

using namespace Bomberman;

Monster::Monster(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, Thinking::Brain *b, uint damage)
  : Character(pos, rot, sz, "Monster", 1, MONSTER_SPEED), moved_(false), damage_(damage), brainScript_(b),
    model_(ModelHandler::get().getModel("ghost"))
{
  //  isInvincible_ = true;
  brainScript_->compileFile(MONSTER_SCRIPT);
  bBox_ = new BoundingBox(pos_, sz_, this);
  actionsMap_.insert(std::make_pair(Bomberman::LEFT, &Character::turnLeft));
  actionsMap_.insert(std::make_pair(Bomberman::RIGHT, &Character::turnRight));
  actionsMap_.insert(std::make_pair(Bomberman::UP, &Character::turnUp));
  actionsMap_.insert(std::make_pair(Bomberman::DOWN, &Character::turnDown));
}

Monster::Monster(const Monster &other)
    : Character(other.pos_, other.rot_, other.sz_, "Monster", other.life_, other.speed_),
      moved_(other.moved_), damage_(other.getDamage()),
      brainScript_(new Thinking::Brain(other.brainScript_->getX(), other.brainScript_->getY())),
      model_(other.model_)
{
    isInvincible_ = other.isInvincible_;
    brainScript_->compileFile(MONSTER_SCRIPT);
    bBox_ = new BoundingBox(other.pos_, other.sz_, this);
    actionsMap_ = other.actionsMap_;
    damage_ = other.damage_;
}

Monster::Monster()
  : Character("Monster"), moved_(false), brainScript_(new Thinking::Brain()), model_(ModelHandler::get().getModel("bombman"))
{
    isInvincible_ = false;
    brainScript_->compileFile(MONSTER_SCRIPT);
    bBox_ = new BoundingBox(Vector3d(), Vector3d(), this);
    actionsMap_.insert(std::make_pair(Bomberman::LEFT, &Character::turnLeft));
    actionsMap_.insert(std::make_pair(Bomberman::RIGHT, &Character::turnRight));
    actionsMap_.insert(std::make_pair(Bomberman::UP, &Character::turnUp));
    actionsMap_.insert(std::make_pair(Bomberman::DOWN, &Character::turnDown));
    damage_ = 0;
}

Bomberman::Thinking::Brain *Monster::getBrain(void) const
{
  return (brainScript_);
}

Monster::~Monster()
{}

void		Monster::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  //  brainScript_->updateDangerMap(objs);
  brainScript_->selectFct("thinking");
  brainScript_->addParam(pos_.x);
  brainScript_->addParam(pos_.y);
  brainScript_->callFct(1);
  eDirection d = NODIR;
  d =  brainScript_->getDecision();
  if (keys.isKeyDown(gdl::Keys::Right))
    d = RIGHT;
  else if (keys.isKeyDown(gdl::Keys::Left))
    d = LEFT;
  else if (keys.isKeyDown(gdl::Keys::Up))
    d = UP;
  else if (keys.isKeyDown(gdl::Keys::Down))
    d = DOWN;
  update(clock, d, objs);
  model_.update(clock);
  (void)keys;
}

void		Monster::update(gdl::GameClock& clock, eDirection direction, std::list<AObject*>& objs)
{
  std::list<AObject*>::iterator objIt;

  save_ = pos_;
  if (actionsMap_[direction])
    (this->*(actionsMap_[direction]))();
  for (objIt = objs.begin(); objIt != objs.end() && save_ != pos_; ++objIt)
    if (bBox_->collideWith(*objIt))
      (*objIt)->interact(this, objs);
  this->moveAnimation();
  this->model_.update(clock);
}

void		Monster::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x + 0.3, pos_.y + 0.3, pos_.z + 1.2);
  glScaled(0.3, 0.3, 0.43);
  glRotated(90, 1, 0, 0);
  glRotated(rot_.y, 0, 1, 0);

  this->model_.draw();
}

void	Monster::interact(Character *ch, std::list<AObject*>& objs)
{
  (void)objs;
  if (ch->getType() == "Player")
    ch->takeDamage(damage_);
}

void			Monster::moveAnimation(void)
{
  static bool wasRunning = false;

  if (moved_)
  {
    if (!wasRunning && model_.getModel().anim_is_ended("stop"))
    {
      speedAdapter_ = 5;
      model_.getModel().stop_animation("stop");
      model_.getModel().play("start");
    }
    else if (model_.getModel().anim_is_ended("start"))
    {
      model_.getModel().stop_animation("stop");
      speedAdapter_ = 100;
      model_.getModel().play("run");
    }
    speedAdapter_ += speedAdapter_ < 100 ? 1 : 0;
    wasRunning = true;

  }
  else if (wasRunning == true)
  {
    model_.getModel().play("stop");
    wasRunning = false;
  }
  // reset de la propriete moved.
  moved_ = false;
}

uint	Monster::getDamage(void) const
{
  return (damage_);
}

void	Monster::setDamage(uint damage)
{
  damage_ = damage;
}

/* Serialization */

void Monster::serialize(QDataStream &out) const
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
    out << damage_;
    brainScript_->serialize(out);
}

void Monster::unserialize(QDataStream &in)
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
    in >> damage_;
    brainScript_->unserialize(in);
}

void Monster::sInit(void)
{
    qRegisterMetaTypeStreamOperators<Monster>("Monster");
    qMetaTypeId<Monster>();
}

QDataStream &operator<<(QDataStream &out, const Monster &m)
{
    m.serialize(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Monster &m)
{
    m.unserialize(in);
    return in;
}

void    Monster::toQvariant(QSettings &w) const
{
    w.setValue("Monster", qVariantFromValue(*this));
}

void	Monster::setVirtualPheromones(std::vector<std::vector<std::pair<int, int> > > &map,
				     std::list<AObject*>objs,
				     int x, int y) const
{
  (void)x;
  (void)y;
  (void)objs;
  if (map[(pos_.y + 0.001)][(pos_.x + 0.001)].second != PHEROMONE_PLAYER)
    map[(pos_.y + 0.001)][(pos_.x + 0.001)].second = PHEROMONE_MONSTER;
}

// void	Monster::setDanger(std::vector<std::vector<std::pair<int, int> > > &map,
// 			   std::list<AObject*>objs,
// 			   int x, int y) const
// {
//   (void)x;
//   (void)y;
//   (void)objs;
//   setDangerMap(getPos().x, getPos().y, DANGER_MONSTER, map);
// }

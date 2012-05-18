//
// Monster.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Sat May 12 09:47:20 2012 geoffroy lafontaine
// Last update Fri May 18 17:39:22 2012 Jonathan Machado
//

#include <algorithm>
#include "Brick.hh"
#include "Bomb.hh"
#include "Monster.hh"

using namespace Bomberman;

Monster::Monster(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, Thinking::Brain *b, uint damage)
  : Character(pos, rot, sz, "Monster", 1, 0.05), moved_(false), damage_(damage), brainScript_(b)
{
  brainScript_->compileFile (MONSTER_SCRIPT);
  bBox_ = new BoundingBox(pos_, sz_, this);
  model_ = gdl::Model::load("Ressources/assets/marvin.fbx");
  model_.cut_animation(model_, "Take 001", 0, 35, "start");
  model_.cut_animation(model_, "Take 001", 36, 54, "run");
  model_.cut_animation(model_, "Take 001", 55, 120, "stop");
  actionsMap_.insert(std::make_pair(Bomberman::LEFT, &Character::turnLeft));
  actionsMap_.insert(std::make_pair(Bomberman::RIGHT, &Character::turnRight));
  actionsMap_.insert(std::make_pair(Bomberman::UP, &Character::turnUp));
  actionsMap_.insert(std::make_pair(Bomberman::DOWN, &Character::turnDown));
}

Monster::Monster(const Monster &other)
    : Character(other.pos_, other.rot_, other.sz_, "Monster", other.life_, other.speed_),
      moved_(other.moved_), damage_(other.getDamage()), brainScript_(other.brainScript_)
{
    brainScript_->compileFile (MONSTER_SCRIPT);
    bBox_ = new BoundingBox(other.pos_, other.sz_, this);
    model_ = other.model_;
    actionsMap_ = other.actionsMap_;
}

Monster::Monster()
  : Character("Monster"), moved_(false), brainScript_()
{
  brainScript_->compileFile (MONSTER_SCRIPT);
  bBox_ = new BoundingBox(Vector3d(), Vector3d(), this);
  model_ = gdl::Model::load("Ressources/assets/marvin.fbx");
  model_.cut_animation(model_, "Take 001", 0, 35, "start");
  model_.cut_animation(model_, "Take 001", 36, 54, "run");
  model_.cut_animation(model_, "Take 001", 55, 120, "stop");
  actionsMap_.insert(std::make_pair(Bomberman::LEFT, &Character::turnLeft));
  actionsMap_.insert(std::make_pair(Bomberman::RIGHT, &Character::turnRight));
  actionsMap_.insert(std::make_pair(Bomberman::UP, &Character::turnUp));
  actionsMap_.insert(std::make_pair(Bomberman::DOWN, &Character::turnDown));
}

Monster::~Monster()
{}

void		Monster::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  brainScript_->selectFct("thinking");
  brainScript_->callFct(1);
  update(clock, brainScript_->getDecision(), objs);
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

#define ZIZIDEPOULE 0.5f

void		Monster::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x, pos_.y, pos_.z);
  // glScaled(0.002, 0.002, 0.002);
  // glRotated(90, 1, 0, 0);
  glColor3d(0.1f, 0.50f, 0.38f);


  glBegin(GL_LINE_LOOP);
  ////////////////////////////////////////////////////////////////////////////////
  /// Configuration de la couleur des vertices
  ///////////////////////////////////////////////////////////////////////////////
  glColor3f(0.23f, 0.50f, 0.62f);
  ////////////////////////////////////////////////////////////////////////////////
  /// Dessin des vertices
  ////////////////////////////////////////////////////////////////////////////////
  glNormal3d(0, 1, 0);
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, 0);
  /// Vertex inferieur droit
  glVertex3f(0, ZIZIDEPOULE, 0);
  /// Vertex superieur droit
  glVertex3f(0, ZIZIDEPOULE, ZIZIDEPOULE);

  glColor3f(0.32f, 0.05f, 0.26f);
  glNormal3d(1, 0, 0);
  /// Vertex superieur gauche
  glVertex3f(ZIZIDEPOULE, 0, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(ZIZIDEPOULE, 0, 0);
  /// Vertex inferieur droit
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, 0);
  /// Vertex superieur droit
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  glColor3f(0.33f, 0.21f, 0.12f);
  glNormal3d(0, -1, 0);
  /// Vertex superieur gauche
  glVertex3f(0, 0, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(0, 0, 0);
  /// Vertex inferieur droit
  glVertex3f(ZIZIDEPOULE, 0, 0);
  /// Vertex superieur droit
  glVertex3f(ZIZIDEPOULE, 0, ZIZIDEPOULE);
  glColor3f(0.88f, 0.57f, 0.10f);
  glNormal3d(-1, 0, 0);
  /// Vertex superieur gauche
  glVertex3f(0, ZIZIDEPOULE, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(0, ZIZIDEPOULE, 0);
  /// Vertex inferieur droit
  glVertex3f(0, 0, 0);
  /// Vertex superieur droit
  glVertex3f(0, 0, ZIZIDEPOULE);
  glColor3f(0.32f, 0.53f, 0.21f);
  glNormal3d(0, 0, -1);
  glVertex3f(0, 0, 0);
  glVertex3f(ZIZIDEPOULE, 0, 0);
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, 0);
  glVertex3f(0, ZIZIDEPOULE, 0);
  glColor3f(0.91f, 0.18f, 0.42f);
  glNormal3d(0, 0, 1);
  glVertex3f(0, 0, ZIZIDEPOULE);
  glVertex3f(ZIZIDEPOULE, 0, ZIZIDEPOULE);
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  glVertex3f(0, ZIZIDEPOULE, ZIZIDEPOULE);
 ////////////////////////////////////////////////////////////////////////////////
  /// Fermeture du contexte de rendu
  ////////////////////////////////////////////////////////////////////////////////
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x + (ZIZIDEPOULE / 2.0f) , pos_.y + (ZIZIDEPOULE / 2.0f), pos_.z);
  glColor3d(1.0f, 0.0f, 0.0f);
  glScaled(0.0035, 0.0035, 0.0023);
  glRotated(90, 1, 0, 0);
  glRotated(rot_.y, 0, 1, 0);

  this->model_.draw();
}

void	Monster::interact(Character *ch, std::list<AObject*>& objs)
{
  (void)objs;
  if (dynamic_cast<Player*>(ch))
    ch->takeDamage(damage_);
}

void			Monster::moveAnimation(void)
{
  static bool wasRunning = false;

  if (moved_)
  {
    if (!wasRunning && model_.anim_is_ended("stop"))
    {
      speedAdapter_ = 5;
      model_.stop_animation("stop");
      model_.play("start");
    }
    else if (model_.anim_is_ended("start"))
    {
      model_.stop_animation("stop");
      speedAdapter_ = 100;
      model_.play("run");
    }
    speedAdapter_ += speedAdapter_ < 100 ? 1 : 0;
    wasRunning = true;

  }
  else if (wasRunning == true)
  {
    model_.play("stop");
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

/* TMP */

void Monster::aff(void) const
{
    std::cout << "=== START MONSTER ===" << std::endl;
    std::cout << "moved : " << moved_ << std::endl;
    std::cout << "life : " << life_ << std::endl;
    std::cout << "speed : " << speed_ << std::endl;
    std::cout << "speed adapt : " << speedAdapter_ << std::endl;
    std::cout << "moved : " << moved_ << std::endl;
    std::cout << "pos : " << pos_ << std::endl;
    std::cout << "rot : " << rot_ << std::endl;
    std::cout << "size : " << sz_ << std::endl;
    std::cout << "type : " << type_ << std::endl;
    std::cout << "=== END MONSTER ===" << std::endl;
}


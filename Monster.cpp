//
// Monster.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Sat May 12 09:47:20 2012 geoffroy lafontaine
// Last update Sat May 12 15:16:31 2012 geoffroy lafontaine
//

#include <algorithm>
#include "Brick.hh"
#include "Bomb.hh"
#include "Monster.hh"

using namespace Bomberman;

Monster::Monster(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : Character(pos, rot, sz, "Monster", 1, 0.05), moved_(false)
{
  bBox_ = new BoundingBox(pos_, sz_);
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
{
}

void		Monster::update(gdl::GameClock& clock, eDirection direction, std::list<AObject*>& objs)
{
  Vector3d	verti(0, speed_, 0);
  Vector3d	hori(speed_, 0, 0);
  Vector3d	save(pos_);
  std::list<AObject*>::iterator objIt;

  if (actionsMap_[direction])
    (this->*(actionsMap_[direction]))();
  if (save != pos_)
    for (objIt = objs.begin(); objIt != objs.end() && save != pos_; ++objIt)
      {
	if (bBox_->collideWith(*objIt))
	  {
	    if (bBox_->isAbove() || bBox_->isBelow())
	      pos_.y = save.y;
	    if (bBox_->isLeft() || bBox_->isRight())
	      pos_.x = save.x;
	  }
      }
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

const std::string&	Monster::type(void) const
{
  return (type_);
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

/* Serialization */

void Monster::serialize(QDataStream &out) const
{
    (void)out;
}

void Monster::unserialize(QDataStream &in)
{
    (void)in;
}

void Monster::sInit(void)
{
//    qRegisterMetaTypeStreamOperators<Monster>("Monster");
//    qMetaTypeId<Monster>();
}

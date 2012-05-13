//
// Explosion.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 11 11:45:40 2012 lois burg
// Last update Sun May 13 14:23:48 2012 lois burg
//

#include "Explosion.hh"

using namespace	Bomberman;

Explosion::Explosion(const Vector3d& pos, const Vector3d& sz, uint damage)
  : AObject(pos, Vector3d(), sz, "Explosion"), damage_(damage), bBox_(pos_, sz_, this), timeOnScreen_(1.0f), timeOfCreation_(-1)
{
  model_ = gdl::Model::load("Ressources/assets/bomb.fbx");
}

Explosion::Explosion(const Explosion& other)
  : AObject(other.getPos(), other.getRot(), other.getSize(), other.type()), damage_(other.getDamage()), bBox_(pos_, sz_, this), timeOnScreen_(1.0f), timeOfCreation_(-1)
{
}

Explosion::~Explosion()
{
}

void		Explosion::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)keys;
  (void)objs;
  if (timeOfCreation_ == -1)
    timeOfCreation_ = clock.getTotalGameTime();
  if (clock.getTotalGameTime() - timeOfCreation_ >= timeOnScreen_)
    destroy();
}

void		Explosion::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  glBegin(GL_QUADS);
  glColor3ub(198, 12, 0);
  glVertex3f(1.0F, 1.0F, 1.0F);
  glVertex3f(1.0F, 1.0F, 0);
  glVertex3f(0, 1.0F, 0);
  glVertex3f(0, 1.0F, 1.0F);
  glVertex3f(1.0F, 0, 1.0F);
  glVertex3f(1.0F, 0, 0);
  glVertex3f(1.0F, 1.0F, 0);
  glVertex3f(1.0F, 1.0F, 1.0F);
  glVertex3f(0, 0, 1.0F);
  glVertex3f(0, 0, 0);
  glVertex3f(1.0F, 0, 0);
  glVertex3f(1.0F, 0, 1.0F);
  glVertex3f(0, 1.0F, 1.0F);
  glVertex3f(0, 1.0F, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 1.0F);
  glVertex3f(0, 0, 0);
  glVertex3f(1.0F, 0, 0);
  glVertex3f(1.0F, 1.0F, 0);
  glVertex3f(0, 1.0F, 0);
  glVertex3f(0, 0, 1.0F);
  glVertex3f(1.0F, 0, 1.0F);
  glVertex3f(1.0F, 1.0F, 1.0F);
  glVertex3f(0, 1.0F, 1.0F);
  glEnd();
}

const std::string&	Explosion::type(void) const
{
  return (type_);
}

uint	Explosion::getDamage(void) const
{
  return (damage_);
}

/* Serialization */

BoundingBox&	Explosion::getBBox(void)
{
  return (bBox_);
}

void Explosion::serialize(QDataStream &out) const
{
    (void)out;
}

void Explosion::unserialize(QDataStream &in)
{
    (void)in;
}

void Explosion::sInit(void)
{
//    qRegisterMetaTypeStreamOperators<Explosion>("Explosion");
//    qMetaTypeId<Explosion>();
}

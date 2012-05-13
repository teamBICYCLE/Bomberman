//
// Explosion.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 11 11:45:40 2012 lois burg
// Last update Fri May 11 15:27:42 2012 lois burg
//

#include "Explosion.hh"

using namespace	Bomberman;

Explosion::Explosion(const Vector3d& pos, const Vector3d& sz, uint damage)
  : AObject(pos, Vector3d(), sz, "Explosion"), damage_(damage), bBox_(pos_, sz_)
{
  model_ = gdl::Model::load("Ressources/assets/bomb.fbx");
}

Explosion::~Explosion()
{
}

void		Explosion::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
}

void		Explosion::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glColor3ub(198, 8, 0);
  glTranslated(pos_.x, pos_.y, pos_.z);
  glScaled(0.0035, 0.0035,0.0035);
  glRotated(90, 1, 0, 0);
  model_.draw();
}

const std::string&	Explosion::type(void) const
{
  return (type_);
}

/* Serialization */

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

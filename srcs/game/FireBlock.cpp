//
// FireBlock.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Sat May 19 19:11:48 2012 lois burg
//

#include "FireBlock.hh"

#include <GL/gl.h>
#include <GDL/Image.hpp>

using namespace	Bomberman;

FireBlock::FireBlock(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : Block(pos, rot, sz), range_(2), lastTime_(-1), timer_(3.0f)
{
  type_ = "FireBlock";
}

FireBlock::FireBlock(const FireBlock &other)
  : Block(other.pos_, other.rot_, other.sz_), dir_(other.dir_), range_(other.range_)
{
  type_ = "FireBlock";
}

FireBlock::FireBlock()
  : Block(Vector3d(), Vector3d(), Vector3d()), dir_(Vector3d()), range_(2)
{
  type_ = "FireBlock";
}

FireBlock::~FireBlock()
{
}

void		FireBlock::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  float		now = clock.getTotalGameTime();

  (void)keys;
  (void)objs;
  if (lastTime_ == -1)
    lastTime_ = now;
  if (now - lastTime_ >= timer_)
    {
      randDir();
      //spitFire();
      lastTime_ = now;
    }
}

#define ZIZIDEPOULE 1.0f

void		FireBlock::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  glBegin(GL_QUADS);
  glColor3ub(175, 175, 175);
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

void	FireBlock::destroy(void)
{
  //indestructible block
}

void	FireBlock::randDir(void)
{
  int	r = rand() % 2;

  if (r)
    dir_ = Vector3d(1, 0, 0);
  else
    dir_ = Vector3d(0, 1, 0);
  r = rand() % 2;
  if (r)
    dir_ *= -1;
}

/* Serialization */

void FireBlock::serialize(QDataStream &out) const
{
  Block::serialize(out);
  dir_.serialize(out);
  out << range_;
  out << lastTime_;
  out << timer_;
}

void FireBlock::unserialize(QDataStream &in)
{
  Block::unserialize(in);
  dir_.unserialize(in);
  in >> range_;
  in >> lastTime_;
  in >> timer_;
}

void FireBlock::sInit(void)
{
    qRegisterMetaTypeStreamOperators<FireBlock>("FireBlock");
    qMetaTypeId<FireBlock>();
}

QDataStream &operator<<(QDataStream &out, const FireBlock &v)
{
    v.serialize(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, FireBlock &v)
{
    v.unserialize(in);
    return in;
}

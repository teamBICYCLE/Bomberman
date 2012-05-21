//
// FireBlock.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Sun May 20 17:08:01 2012 lois burg
//

#include <algorithm>
#include "Character.hh"
#include "APowerup.hh"
#include "Mine.hh"
#include "Bomb.hh"
#include "Brick.hh"
#include "FireBlock.hh"

#include <GL/gl.h>
#include <GDL/Image.hpp>

using namespace	Bomberman;

FireBlock::FireBlock(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : Block(pos, rot, sz), range_(2), lastTime_(-1), timer_(3.0f)
{
  randDir();
  type_ = "FireBlock";
}

FireBlock::FireBlock(const FireBlock &other)
  : Block(other.pos_, other.rot_, other.sz_), dir_(other.dir_), range_(other.range_)
{
  randDir();
  type_ = "FireBlock";
}

FireBlock::FireBlock()
  : Block(Vector3d(), Vector3d(), Vector3d()), dir_(Vector3d()), range_(2)
{
  randDir();
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
      spitFire(objs);
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

void	FireBlock::spitFire(std::list<AObject*>& objs)
{
  Explosion	*e = new Explosion(pos_, Vector3d(1, 1, 0), 1, *(new Player()));
  bool		isInvalid = false;

  for (int i = 1; !isInvalid && i <= range_; ++i)
    {
      e->setPos(pos_ + (dir_ * i));
      if (!isInvalid)
	std::for_each(objs.begin(), objs.end(), [&](AObject *obj) -> void {
	    if (!isInvalid && e->getBBox().collideWith(obj))
	      {
		if (dynamic_cast<Character*>(obj))
		  static_cast<Character*>(obj)->takeDamage(e->getDamage());
		else if (dynamic_cast<APowerup*>(obj))
		  obj->destroy();
		else if (dynamic_cast<Mine*>(obj))
		  static_cast<Mine*>(obj)->setChainReaction(true);
		else if (dynamic_cast<Bomb*>(obj))
		  static_cast<Bomb*>(obj)->setTimeOut(0.0f);
		else if (dynamic_cast<Brick*>(obj))
		  static_cast<Brick*>(obj)->destroy(objs);
		if (!dynamic_cast<Character*>(obj) && !dynamic_cast<APowerup*>(obj) &&
		    !dynamic_cast<Mine*>(obj))
		  isInvalid = true;
	      }
	  });
      if (!isInvalid)
	objs.push_back(new Explosion(*e));

    }
  delete e;
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

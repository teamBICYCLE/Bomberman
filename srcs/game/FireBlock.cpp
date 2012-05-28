//
// FireBlock.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Mon May 28 16:18:32 2012 lois burg
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
#include "ModelHandler.hh"

using namespace	Bomberman;


FireBlock::FireBlock(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const Vector3d& dir)
  : Block(pos, rot, sz), dir_(dir), range_(2), lastTime_(-1), timer_(3.0f),
    model_(ModelHandler::get().getModel("cube"))
{
  type_ = "FireBlock";
}

FireBlock::FireBlock(const FireBlock &other)
  : Block(other.pos_, other.rot_, other.sz_), dir_(other.dir_),
    range_(other.range_), lastTime_(other.lastTime_), timer_(other.timer_),
    model_(other.model_)
{
  type_ = "FireBlock";
}

FireBlock::FireBlock()
  : Block(Vector3d(), Vector3d(), Vector3d()), dir_(Vector3d()), range_(2),
    model_(ModelHandler::get().getModel("cube"))
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
    {
      last_ = timer_;
      lastTime_ = now;
    }
  if (now - lastTime_ >= timer_)
    {
      spitFire(objs);
      lastTime_ = now;
      last_ = timer_;
    }
  else
    last_ -= now;
  model_.update(clock);
}

float	FireBlock::getTimeout() const
{
  return last_;
}

#define ZIZIDEPOULE 1.0f

void		FireBlock::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  model_.draw();
}

void	FireBlock::destroy(void)
{
  //indestructible block
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
		obj->interact(e, objs);
                // if (dynamic_cast<Character*>(obj))
                //   static_cast<Character*>(obj)->takeDamage(e->getDamage());
                // else if (dynamic_cast<APowerup*>(obj))
                //   obj->destroy();
                // else if (dynamic_cast<Mine*>(obj))
                //   static_cast<Mine*>(obj)->setChainReaction(true);
                // else if (dynamic_cast<Bomb*>(obj))
                //   static_cast<Bomb*>(obj)->setTimeOut(0.0f);
                // else if (dynamic_cast<Brick*>(obj))
                //   static_cast<Brick*>(obj)->destroy(objs);
                if (!dynamic_cast<Character*>(obj) && !dynamic_cast<APowerup*>(obj) &&
                    !dynamic_cast<Mine*>(obj) && !dynamic_cast<Explosion*>(obj))
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
    pos_.serialize(out);
    rot_.serialize(out);
    sz_.serialize(out);
    dir_.serialize(out);
    out << lastTime_;
    out << range_;
    out << timer_;
}

void FireBlock::unserialize(QDataStream &in)
{
    pos_.unserialize(in);
    rot_.unserialize(in);
    sz_.unserialize(in);
    dir_.unserialize(in);
    in >> lastTime_;
    in >> range_;
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

void    FireBlock::toQvariant(QSettings &w) const
{
    w.setValue("FireBlock", qVariantFromValue(*this));
}

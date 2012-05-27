//
// Explosion.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 11 11:45:40 2012 lois burg
// Last update Sat May 26 17:49:37 2012 thibault carpentier
//

#include "Explosion.hh"
#include "ModelHandler.hh"

using namespace	Bomberman;

Explosion::Explosion(const Vector3d& pos, const Vector3d& sz, uint damage, Player& owner)
  : AObject(pos, Vector3d(), sz, "Explosion"), damage_(damage), bBox_(pos_, sz_, this), timeOnScreen_(1.0f), lastTime_(-1), owner_(owner),
    model_(ModelHandler::get().getModel("explosion"))
{
}

Explosion::Explosion(const Explosion& other)
  : AObject(other.getPos(), other.getRot(), other.getSize(), other.getType()), damage_(other.getDamage()), bBox_(pos_, sz_, this), timeOnScreen_(1.0f), lastTime_(-1), owner_(other.owner_),
    model_(other.model_)
{
}

Explosion::Explosion()
    : AObject(Vector3d(), Vector3d(), Vector3d(), "Explosion"), damage_(0),
      bBox_(Vector3d(), Vector3d(), this), timeOnScreen_(1.0f), lastTime_(-1), owner_(*(new Player())),
      model_(ModelHandler::get().getModel("explosion"))
{
}

Explosion::~Explosion()
{
}

void		Explosion::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  float		now = clock.getTotalGameTime();

  (void)keys;
  (void)objs;
  if (lastTime_ == -1)
    lastTime_ = now;
  if (timeOnScreen_ <= 0)
    destroy();
  else
    {
      timeOnScreen_ -= now - lastTime_;
      lastTime_ = now;
    }
  model_.update(clock);
}

void		Explosion::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  model_.draw();
}

uint	Explosion::getDamage(void) const
{
  return (damage_);
}

void	Explosion::interact(Character *ch, std::list<AObject*>& objs)
{
  (void)objs;
  ch->takeDamage(damage_);
  if (ch != &owner_ && !ch->getLife() && !ch->isInvincible())
    owner_.addScore(ch->getScoreValue());
}

BoundingBox&	Explosion::getBBox(void)
{
  return (bBox_);
}

Player&		Explosion::getOwner(void)
{
  return (owner_);
}

/* Serialization */

void Explosion::serialize(QDataStream &out) const
{
    pos_.serialize(out);
    rot_.serialize(out);
    sz_.serialize(out);
    out << removeLater_;
    out << damage_;
    out << timeOnScreen_;
    out << lastTime_;
}

void Explosion::unserialize(QDataStream &in)
{
    pos_.unserialize(in);
    rot_.unserialize(in);
    sz_.unserialize(in);
    in >> removeLater_;
    in >> damage_;
    in >> timeOnScreen_;
    in >> lastTime_;
}

void Explosion::sInit(void)
{
    qRegisterMetaTypeStreamOperators<Explosion>("Explosion");
    qMetaTypeId<Explosion>();
}

QDataStream &operator<<(QDataStream &out, const Explosion &v)
{
    v.serialize(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Explosion &v)
{
    v.unserialize(in);
    return in;
}

void    Explosion::toQvariant(QSettings &w) const
{
    w.setValue("Explosion", qVariantFromValue(*this));
}

void  Explosion::setDanger(std::vector<std::vector<std::pair<int, int> > > &map, std::list<AObject*>objs,
			   int x, int y) const
{
  (void)x;
  (void)y;
  (void)objs;
  setDangerMap(getPos().x, getPos().y, DANGER_EXPLOSION, map);
}



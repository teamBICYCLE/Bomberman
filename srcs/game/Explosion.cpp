//
// Explosion.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 11 11:45:40 2012 lois burg
// Last update Mon May 21 10:32:27 2012 lois burg
//

#include "Explosion.hh"
#include "ModelHandler.hh"

using namespace	Bomberman;

Explosion::Explosion(const Vector3d& pos, const Vector3d& sz, uint damage, Player& owner)
  : AObject(pos, Vector3d(), sz, "Explosion"), damage_(damage), bBox_(pos_, sz_, this), timeOnScreen_(1.0f), lastTime_(-1), owner_(owner),
    model_(ModelHandler::get().getModel("cube"))
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
      model_(ModelHandler::get().getModel("cube"))
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
  glColor3ub(198, 12, 0);
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

/* TMP */

void Explosion::aff(void) const
{
    std::cout << "=== START Explosion ===" << std::endl;
    std::cout << "Pos : " << pos_.x << " " << pos_.y << " " << pos_.z << std::endl;
    std::cout << "Rot : " << rot_.x << " " << rot_.y << " " << rot_.z << std::endl;
    std::cout << "Size : " << sz_.x << " " << sz_.y << " " << sz_.z << std::endl;
    std::cout << "Damage : " << damage_ << std::endl;
    std::cout << "timeonscreen : " << timeOnScreen_ << std::endl;
    std::cout << "timeofcreation : " << lastTime_ << std::endl;
    std::cout << "=== END Explosion ===" << std::endl;
}

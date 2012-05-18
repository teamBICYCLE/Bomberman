//
// Bomb.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 11:50:36 2012 lois burg
// Last update Thu May 17 18:54:34 2012 lois burg
//

#include <algorithm>
#include "Explosion.hh"
#include "Bomb.hh"
#include "Mine.hh"
#include "Brick.hh"

using namespace	Bomberman;

Bomb::Bomb(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, int range, int timeOut, Player& owner)
  : AObject(pos, rot, sz, "Bomb"), range_(range), timeOut_(timeOut), owner_(owner), speed_(Vector3d()), timeCreation_(-1), ownerCollide_(false)
{
  model_ = gdl::Model::load("Ressources/assets/bomb.fbx");
}

Bomb::Bomb(const Bomb &other)
    : AObject(other.pos_, other.rot_, other.sz_, "Bomb"),
      range_(other.range_), timeOut_(other.timeOut_),
      owner_(other.owner_), speed_(other.speed_),
      timeCreation_(other.timeCreation_),
      ownerCollide_(other.getOwnerCollide())
{
    model_ = other.getModel();
}

Bomb::Bomb()
  : AObject(Vector3d(), Vector3d(), Vector3d(), "Bomb"),
    range_(0), timeOut_(0), owner_(*(new Player())),
    speed_(Vector3d()), timeCreation_(0)
{
    model_ = gdl::Model::load("Ressources/assets/bomb.fbx");
}

Bomb::~Bomb()
{
}

void	Bomb::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)keys;
  (void)objs;
  if (timeCreation_ == -1)
    timeCreation_ = clock.getTotalGameTime();
  if (clock.getTotalGameTime() - timeCreation_ >= timeOut_)
    destroy(objs);
  pos_ += speed_;
}

void	Bomb::explode(std::list<AObject*>& objs)
{
  Explosion	*e = new Explosion(pos_, Vector3d(1, 1, 0), 1);
  bool		upInvalid = false;
  bool		downInvalid = false;
  bool		leftInvalid = false;
  bool		rightInvalid = false;

  (void)objs;
  (void)e;
  //explosion qui tue et ajout des loots de tier 7
  objs.push_back(new Explosion(*e));
  for (int i = 1; i <= range_; ++i)
    {
      // std::cout << std::boolalpha << "Up: " << upInvalid << ", Down: " << downInvalid << ", Left: " << leftInvalid << ", Right: " << rightInvalid << std::noboolalpha << std::endl;
      e->setPos(pos_ + Vector3d(0, -i, 0));
      checkPosition(e, upInvalid, objs);
      e->setPos(pos_ + Vector3d(0, i, 0));
      checkPosition(e, downInvalid, objs);
      e->setPos(pos_ + Vector3d(-i, 0, 0));
      checkPosition(e, leftInvalid, objs);
      e->setPos(pos_ + Vector3d(i, 0, 0));
      checkPosition(e, rightInvalid, objs);
      // std::cout << std::boolalpha << "Up: " << upInvalid << ", Down: " << downInvalid << ", Left: " << leftInvalid << ", Right: " << rightInvalid << std::noboolalpha << std::endl;
      // std::cout << "--------------------" << std::endl;
    }
}

void	Bomb::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x + 0.5, pos_.y + 0.5, pos_.z);
  glScaled(0.0035, 0.0035,0.0035);
  glRotated(90, 1, 0, 0);
  model_.draw();
}

void	Bomb::adjustPos(void)
{
  pos_.x = (int)pos_.x;
  pos_.y = (int)pos_.y;
  pos_.z = (int)pos_.z;
}

void	Bomb::checkPosition(Explosion *e, bool& isInvalid, std::list<AObject*>& objs)
{
  if (!isInvalid)
    std::for_each(objs.begin(), objs.end(), [&](AObject *obj) -> void {
	if (!isInvalid && e->getBBox().collideWith(obj))
	  {
	    if (dynamic_cast<Character*>(obj))
	      {
		if (obj != &owner_ && !static_cast<Character*>(obj)->isInvincible())
		  owner_.addScore(static_cast<Character*>(obj)->getScoreValue());
		static_cast<Character*>(obj)->takeDamage(e->getDamage());
	      }
	    else if (dynamic_cast<APowerup*>(obj))
	      obj->destroy();
	    else if (dynamic_cast<Mine*>(obj))
	      static_cast<Mine*>(obj)->setChainReaction(true);
	    else if (dynamic_cast<Bomb*>(obj))
	      static_cast<Bomb*>(obj)->setTimeOut(0.0f);
	    else if (dynamic_cast<Brick*>(obj))
	      static_cast<Brick*>(obj)->destroy(objs);
	    if (!dynamic_cast<Character*>(obj) && !dynamic_cast<APowerup*>(obj))
	      isInvalid = true;
	  }
      });
  if (!isInvalid)
    objs.push_back(new Explosion(*e));
}

void	Bomb::interact(Character *ch, std::list<AObject*>& objs)
{
  (void)objs;
  if ((&owner_ == ch && ownerCollide_) ||
      &owner_ != ch)
    ch->bump(pos_);
}

void	Bomb::destroy(std::list<AObject*>& objs)
{
  explode(objs);
  owner_.setNbBombs(owner_.getNbBombs() + 1);
  if (!ownerCollide_)
    owner_.setBombCollide(true);
  AObject::destroy();
}

void	Bomb::setTimeOut(const float timeOut)
{
  timeOut_ = timeOut;
}

float	Bomb::getTimeOut(void) const
{
  return (timeOut_);
}

void    Bomb::setSpeed(const Vector3d &v)
{
    speed_ = v;
}

const Player&	Bomb::getOwner(void) const
{
  return (owner_);
}

bool	Bomb::getOwnerCollide(void) const
{
  return (ownerCollide_);
}

void	Bomb::setOwnerCollide(bool b)
{
  ownerCollide_ = b;
}

/* Serialization */

void Bomb::serialize(QDataStream &out) const
{
    pos_.serialize(out);
    rot_.serialize(out);
    sz_.serialize(out);
    out << removeLater_;
    out << range_;
    out << timeOut_;
    owner_.serialize(out);
}

void Bomb::unserialize(QDataStream &in)
{
    pos_.unserialize(in);
    rot_.unserialize(in);
    sz_.unserialize(in);
    in >> removeLater_;
    in >> range_;
    in >> timeOut_;
    owner_.unserialize(in);
}

void Bomb::sInit(void)
{
    qRegisterMetaTypeStreamOperators<Bomb>("Bomb");
    qMetaTypeId<Bomb>();
}

QDataStream &operator<<(QDataStream &out, const Bomb &v)
{
    v.serialize(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Bomb &v)
{
    v.unserialize(in);
    return in;
}

/* TMP */
void Bomb::aff(void) const
{
    std::cout << "=== START BOMB ===" << std::endl;
    std::cout << "Pos : " << pos_.x << " " << pos_.y << " " << pos_.z << std::endl;
    std::cout << "Rot : " << rot_.x << " " << rot_.y << " " << rot_.z << std::endl;
    std::cout << "Size : " << sz_.x << " " << sz_.y << " " << sz_.z << std::endl;
    std::cout << "type : " << type_ << std::endl;
    std::cout << "Range : " << range_ << std::endl;
    std::cout << "timeout : " << timeOut_ << std::endl;
    std::cout << "speed : " << speed_ << std::endl;
    std::cout << "timeCreation : " << timeCreation_ << std::endl;
    owner_.aff();
    std::cout << "=== END BOMB ===" << std::endl;
}

//
// Bomb.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 11:50:36 2012 lois burg
// Last update Mon May 21 10:39:21 2012 lois burg
//

#include <algorithm>
#include "Explosion.hh"
#include "Bomb.hh"
#include "Mine.hh"
#include "Brick.hh"

using namespace	Bomberman;

Bomb::Bomb(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, int range, int timeOut, Player& owner)
  : AObject(pos, rot, sz, "Bomb"), range_(range), timeOut_(timeOut), owner_(owner), speed_(Vector3d()), lastTime_(-1), ownerCollide_(false), bBox_(pos_, sz_, this)
{
  model_ = gdl::Model::load("Ressources/Assets/bomb.fbx");
}

Bomb::Bomb(const Bomb &other)
    : AObject(other.pos_, other.rot_, other.sz_, "Bomb"),
      range_(other.range_), timeOut_(other.timeOut_),
      owner_(other.owner_), speed_(other.speed_),
      lastTime_(other.lastTime_),
      ownerCollide_(other.getOwnerCollide()),
      bBox_(other.bBox_)
{
    model_ = other.getModel();
}

Bomb::Bomb()
  : AObject(Vector3d(), Vector3d(), Vector3d(), "Bomb"),
    range_(0), timeOut_(0), owner_(*(new Player())),
    speed_(Vector3d()), lastTime_(0), bBox_(pos_, sz_, this)
{
    model_ = gdl::Model::load("Ressources/Assets/bomb.fbx");
}

Bomb::~Bomb()
{
}

void	Bomb::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  std::list<AObject*>::iterator	objIt = objs.begin();
  Vector3d	save(pos_);
  Vector3d	nullSpeed;
  float		now = clock.getTotalGameTime();

  (void)keys;
  if (lastTime_ == -1)
    lastTime_ = clock.getTotalGameTime();
  if (timeOut_ <= 0)
    destroy(objs);
  else
    {
      timeOut_ -= now - lastTime_;
      lastTime_ = now;
    }
  pos_ += speed_;
  for (; speed_ != nullSpeed && objIt != objs.end(); ++objIt)
    if (*objIt != &owner_ && bBox_.collideWith(*objIt))
      {
	pos_ = save + sz_ / 2;
	adjustPos();
	speed_ = nullSpeed;
	if (dynamic_cast<Explosion*>(*objIt) || dynamic_cast<Mine*>(*objIt))
	  destroy(objs);
      }
}

void	Bomb::explode(std::list<AObject*>& objs)
{
  Explosion	*e = new Explosion(pos_, Vector3d(1, 1, 0), 1, owner_);
  bool		upInvalid = false;
  bool		downInvalid = false;
  bool		leftInvalid = false;
  bool		rightInvalid = false;

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
  delete e;
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
  pos_.x = static_cast<int>(pos_.x);
  pos_.y = static_cast<int>(pos_.y);
  pos_.z = static_cast<int>(pos_.z);
}

void	Bomb::checkPosition(Explosion *e, bool& isInvalid, std::list<AObject*>& objs)
{
  if (!isInvalid)
    std::for_each(objs.begin(), objs.end(), [&](AObject *obj) -> void {
	if (!isInvalid && e->getBBox().collideWith(obj))
	  {
	    obj->interact(e, objs);
	    // if (dynamic_cast<Character*>(obj))
	    //   {
	    // 	if (obj != &owner_ && !static_cast<Character*>(obj)->isInvincible())
	    // 	  owner_.addScore(static_cast<Character*>(obj)->getScoreValue());
	    // 	static_cast<Character*>(obj)->takeDamage(e->getDamage());
	    //   }
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

void	Bomb::interact(Character *ch, std::list<AObject*>& objs)
{
  Player	*p;
  const BoundingBox	*b;

  (void)objs;
  if ((&owner_ == ch && ownerCollide_) ||
      &owner_ != ch)
    {
      ch->bump(pos_);
      if (dynamic_cast<Player*>(ch) && static_cast<Player*>(ch)->getKickAbility())
	{
	  p = static_cast<Player*>(ch);
	  b = p->getBBox();
	  if (b->isAbove() || b->isBelow())
	    speed_ = Vector3d(0, p->getSpeed(), 0);
	  else if (b->isLeft() || b->isRight())
	    speed_ = Vector3d(p->getSpeed(), 0, 0);
	  if (b->isAbove() || b->isLeft())
	    speed_ *= (-1);
	}
    }
}

void	Bomb::interact(Explosion *e, std::list<AObject*>& objs)
{
  (void)e;
  (void)objs;
  setTimeOut(0.0f);
}

void	Bomb::destroy(std::list<AObject*>& objs)
{
  if (!toRemove())
    {
      explode(objs);
      owner_.setNbBombs(owner_.getNbBombs() + 1);
      if (!ownerCollide_)
	owner_.setBombCollide(true);
      AObject::destroy();
    }
}

void	Bomb::setTimeOut(const float timeOut)
{
  timeOut_ = timeOut;
}

float	Bomb::getTimeOut(void) const
{
  return (timeOut_);
}

float	Bomb::getLastTime(void) const
{
  return (lastTime_);
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

int     Bomb::getRange(void) const
{
    return range_;
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
    std::cout << "timeCreation : " << lastTime_ << std::endl;
    owner_.aff();
    std::cout << "=== END BOMB ===" << std::endl;
}

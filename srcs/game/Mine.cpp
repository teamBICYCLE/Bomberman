//
// Mine.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 17 16:56:22 2012 lois burg
// Last update Tue May 22 15:08:09 2012 thibault carpentier
//

#include "Mine.hh"
#include "ModelHandler.hh"

using namespace	Bomberman;

Mine::Mine(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, int range, int timeOut, Player& owner)
  : Bomb(pos, rot, sz, range, timeOut, owner), chainReaction_(false)
{
  type_ = "Mine";
}

Mine::Mine(const Mine& other)
  : Bomb(other), chainReaction_(other.chainReaction_)
{
  type_ = "Mine";
}

Mine::Mine()
  : Bomb(), chainReaction_(false)
{
  type_ = "Mine";
}

Mine::~Mine()
{
}

void	Mine::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)keys;
  (void)objs;
  (void)clock;
  if (chainReaction_)
    destroy(objs);
  model_.update(clock);
}

void	Mine::interact(Character *ch, std::list<AObject*>& objs)
{
  (void)ch;
  if (ownerCollide_)
    destroy(objs);
}

void	Mine::interact(Explosion *e, std::list<AObject*>& objs)
{
  (void)e;
  (void)objs;
  setChainReaction(true);
}

void	Mine::destroy(std::list<AObject*>& objs)
{
    std::cout << "* POUF *" << std::endl;
  explode(objs);
  if (!ownerCollide_)
    owner_.setBombCollide(true);
  AObject::destroy();
}

void	Mine::explode(std::list<AObject*>& objs)
{
  Explosion	*e = new Explosion(pos_, Vector3d(1, 1, 0), 1, owner_);

  objs.push_back(new Explosion(*e));
}

void	Mine::setChainReaction(bool b)
{
  chainReaction_ = b;
}

/* Serialization */

void Mine::serialize(QDataStream &out) const
{
  pos_.serialize(out);
  rot_.serialize(out);
  sz_.serialize(out);
  out << removeLater_;
  out << range_;
  out << timeOut_;
  owner_.serialize(out);
  out << chainReaction_;
}

void Mine::unserialize(QDataStream &in)
{
  pos_.unserialize(in);
  rot_.unserialize(in);
  sz_.unserialize(in);
  in >> removeLater_;
  in >> range_;
  in >> timeOut_;
  owner_.unserialize(in);
  in >> chainReaction_;
}

void Mine::sInit(void)
{
    qRegisterMetaTypeStreamOperators<Mine>("Mine");
    qMetaTypeId<Mine>();
}

QDataStream &operator<<(QDataStream &out, const Mine &v)
{
    v.serialize(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Mine &v)
{
    v.unserialize(in);
    return in;
}

void    Mine::toQvariant(QSettings &w) const
{
    w.setValue("Mine", qVariantFromValue(*this));
}

void Mine::aff2(void) const
{
    std::cout << "=== START MINE ===" << std::endl;
    std::cout << "Pos : " << pos_.x << " " << pos_.y << " " << pos_.z << std::endl;
    std::cout << "Rot : " << rot_.x << " " << rot_.y << " " << rot_.z << std::endl;
    std::cout << "Size : " << sz_.x << " " << sz_.y << " " << sz_.z << std::endl;
    std::cout << "type : " << type_ << std::endl;
    std::cout << "Range : " << range_ << std::endl;
    std::cout << "timeout : " << timeOut_ << std::endl;
    std::cout << "speed : " << speed_ << std::endl;
    std::cout << "timeCreation : " << lastTime_ << std::endl;
    //owner_.aff();
    std::cout << "chainReaction : " << chainReaction_ << std::endl;
    std::cout << "=== END MINE ===" << std::endl;
}

//
// Mine.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 17 16:56:22 2012 lois burg
// Last update Thu May 17 18:54:25 2012 lois burg
//

#include "Mine.hh"

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
}

void	Mine::interact(Character *ch, std::list<AObject*>& objs)
{
  (void)ch;
  if (ownerCollide_)
    destroy(objs);
}

void	Mine::destroy(std::list<AObject*>& objs)
{
  explode(objs);
  owner_.setNbMines(owner_.getNbMines() + 1);
  if (!ownerCollide_)
    owner_.setBombCollide(true);
  AObject::destroy();
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
  out << chainReaction_;
  owner_.serialize(out);
}

void Mine::unserialize(QDataStream &in)
{
  pos_.unserialize(in);
  rot_.unserialize(in);
  sz_.unserialize(in);
  in >> removeLater_;
  in >> range_;
  in >> timeOut_;
  in >> chainReaction_;
  owner_.unserialize(in);
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

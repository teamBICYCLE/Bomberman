//
// Mine.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 17 16:56:22 2012 lois burg
// Last update Sun Jun  3 21:44:09 2012 romain sylvian
//

#include "Mine.hh"
#include "ModelHandler.hh"

using namespace	Bomberman;

Mine::Mine(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, Player& owner)
  : Bomb(pos, rot, sz, 0, 0.0f, owner, "mine"), chainReaction_(false)
{
  type_ = "Mine";
}

Mine::Mine(const Mine& other)
  : Bomb(other.pos_, other.rot_, other.sz_, 0, 0.0f, other.owner_, "mine"), chainReaction_(other.chainReaction_)
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

void    Mine::draw()
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x + 0.5, pos_.y + 0.5, pos_.z + 0.20);
  glScaled(0.38, 0.38,0.07);
  glRotated(90, 1, 0, 0);
  model_.draw();
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

void  Mine::setDanger(std::vector<std::vector<std::pair<int, int> > > &map, std::list<AObject*>objs,
                      int x, int y) const
{
  (void)objs;
  (void)x;
  (void)y;
  setDangerMap(getPos().x, getPos().y, DANGER_MINE, map);
}


//
// Block.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Sat Jun  2 20:13:03 2012 lois burg
//

#include <GL/gl.h>
#include <GDL/Image.hpp>
#include "ModelHandler.hh"
#include "Block.hh"

using namespace	Bomberman;

Block::Block(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz, "Brick"), model_(ModelHandler::get().getModel("block"))
{
    build_ = false;
}

Block::Block(const Block &other)
  : AObject(other.pos_, other.rot_, other.sz_, "cube"), model_(other.model_)
{
    build_ = other.build_;
    if (build_)
        model_.setBuild();
}

Block::Block()
  : AObject(Vector3d(), Vector3d(), Vector3d(), "cube"),
    model_(ModelHandler::get().getModel("block"))
{
    build_ = true;
}

Block::~Block()
{
}

void		Block::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
  model_.update(clock);
  if (!build_)
      build_ = model_.getBuild();
}

void		Block::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  model_.draw();
}

void	Block::destroy(void)
{
  //indestructible block
}

/* Serialization */

void Block::serialize(QDataStream &out) const
{
    pos_.serialize(out);
    rot_.serialize(out);
    sz_.serialize(out);
    out << removeLater_;
    out << build_;
}

void Block::unserialize(QDataStream &in)
{
    pos_.unserialize(in);
    rot_.unserialize(in);
    sz_.unserialize(in);
    in >> removeLater_;
    in >> build_;
}

void Block::sInit(void)
{
    qRegisterMetaTypeStreamOperators<Block>("Block");
    qMetaTypeId<Block>();
}

QDataStream &operator<<(QDataStream &out, const Block &v)
{
    v.serialize(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Block &v)
{
    v.unserialize(in);
    return in;
}

void    Block::toQvariant(QSettings &w) const
{
    w.setValue("Block", qVariantFromValue(*this));
}


void	Block::setDanger(std::vector<std::vector<std::pair<int, int> > > &map,
			  std::list<AObject*>objs,
			  int x, int y) const
{
  (void)x;
  (void)y;
  (void)objs;
  setDangerMap(getPos().x, getPos().y, DANGER_BLOCK, map);
}

TexturedCube &Block::getCube()
{
  return model_;
}

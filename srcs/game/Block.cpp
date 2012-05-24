//
// Block.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Thu May 17 11:49:59 2012 lois burg
//

#include "Block.hh"

#include <GL/gl.h>
#include <GDL/Image.hpp>
#include "ModelHandler.hh"

using namespace	Bomberman;

Block::Block(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz, "cube"), model_(ModelHandler::get().getModel("block"))
{
}

Block::Block(const Block &other)
  : AObject(other.pos_, other.rot_, other.sz_, "cube"), model_(other.model_)
{
}

Block::Block()
  : AObject(Vector3d(), Vector3d(), Vector3d(), "cube"),
    model_(ModelHandler::get().getModel("block"))
{
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
}

void Block::unserialize(QDataStream &in)
{
    pos_.unserialize(in);
    rot_.unserialize(in);
    sz_.unserialize(in);
    in >> removeLater_;
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

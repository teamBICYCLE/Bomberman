//
// Block.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Thu May  3 15:31:53 2012 lois burg
//

#include "Block.hh"

using namespace	Bomberman;

Block::Block(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz,"Block")
{
}

Block::~Block()
{
}

void		Block::update(const gdl::GameClock& clock, const gdl::Input& keys)
{
  (void)clock;
  (void)keys;
}

void		Block::draw(void)
{
}

const std::string&	Block::type(void) const
{
  return (type_);
}

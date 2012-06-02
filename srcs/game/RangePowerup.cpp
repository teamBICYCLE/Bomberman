//
// RangePowerup.cpp for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 15:33:03 2012 geoffroy lafontaine
// Last update Sat Jun  2 14:19:04 2012 lois burg
//

#include "RangePowerup.hh"
#include "ModelHandler.hh"

using namespace Bomberman;

RangePowerup::RangePowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : APowerup(pos, rot, sz, "RangePowerup"), model_(ModelHandler::get().getModel("powerup"))
{
}

RangePowerup::~RangePowerup(void)
{
}

RangePowerup::RangePowerup(const RangePowerup &other)
    : APowerup(other.getPos(), other.getRot(), other.getSize(), other.getType()),
      model_(other.model_)
{
}

void	RangePowerup::activate(Player& p)
{
  if (!toRemove())
    {
      p.setBombRange(p.getBombRange() + 1);
      APowerup::activate(p);
    }
}

void	RangePowerup::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
  model_.update(clock);
}

void	RangePowerup::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  model_.draw();
}

RangePowerup    *RangePowerup::clone(void)
{
  return (new RangePowerup(*this));
}

//
// MinePowerup.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 17 18:22:54 2012 lois burg
// Last update Sun May 20 16:16:05 2012 lois burg
//

#include "MinePowerup.hh"
#include "ModelHandler.hh"

using namespace Bomberman;

MinePowerup::MinePowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : APowerup(pos, rot, sz, "MinePowerup"), model_(ModelHandler::get().getModel("powerup"))
{
}

MinePowerup::MinePowerup(const MinePowerup &other)
  : APowerup(other.getPos(), other.getRot(), other.getSize(), "MinePowerup"),
    model_(other.model_)
{
}

MinePowerup::~MinePowerup(void)
{
}

void MinePowerup::activate(Player& p)
{
  if (!toRemove())
    {
      std::cout << "Mine up" << std::endl;
      p.setNbMines(p.getNbMines() + 1);
      APowerup::activate(p);
    }
}

void	MinePowerup::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
  model_.update(clock);
}

void	MinePowerup::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  model_.draw();
}

MinePowerup *MinePowerup::clone(void)
{
    return (new MinePowerup(*this));
}

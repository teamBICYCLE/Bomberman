//
// KickPowerup.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 18 14:57:26 2012 lois burg
// Last update Sun Jun  3 10:12:17 2012 lois burg
//

#include "KickPowerup.hh"
#include "ModelHandler.hh"

using namespace Bomberman;

KickPowerup::KickPowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : APowerup(pos, rot, sz, "KickPowerup"), model_(ModelHandler::get().getModel("kickup"))
{
}

KickPowerup::KickPowerup(const KickPowerup &other)
    : APowerup(other.getPos(), other.getRot(), other.getSize(), "KickPowerup"),
      model_(other.model_)
{
}

KickPowerup::~KickPowerup(void)
{
}

void KickPowerup::activate(Player& p)
{
  if (!toRemove())
    {
      p.setKickAbility(true);
      APowerup::activate(p);
    }
}

void	KickPowerup::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
  model_.update(clock);
}

void	KickPowerup::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  model_.draw();
}

KickPowerup *KickPowerup::clone(void)
{
    return (new KickPowerup(*this));
}

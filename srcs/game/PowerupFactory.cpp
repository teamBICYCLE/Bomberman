/*
** BEER-WARE LICENSE :
** PowerupFactory.cpp for PowerupFactory class (5/3/2012)
** <sylvia_r@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#include <cstdlib>
#include "PowerupFactory.hh"

using namespace Bomberman;

PowerupFactory *PowerupFactory::instance_ = NULL;

PowerupFactory::PowerupFactory()
{
    ref_.push_back(std::make_pair(25, new VelocityPowerup(Vector3d(), Vector3d(), Vector3d())));
    ref_.push_back(std::make_pair(50, new RangePowerup(Vector3d(), Vector3d(), Vector3d())));
    ref_.push_back(std::make_pair(80, new AmmoPowerup(Vector3d(), Vector3d(), Vector3d())));
    ref_.push_back(std::make_pair(90, new MinePowerup(Vector3d(), Vector3d(), Vector3d())));
    ref_.push_back(std::make_pair(100, new KickPowerup(Vector3d(), Vector3d(), Vector3d())));
}

PowerupFactory::~PowerupFactory()
{
  std::vector< std::pair<uint, APowerup *> >::iterator it;

  for (it = ref_.begin(); it != ref_.end(); it++)
    delete (it->second);
}

APowerup *PowerupFactory::percentDrop(void) const
{
   uint nb = (random() % 100) + 1;
   std::vector< std::pair<uint, APowerup *> >::const_iterator it;
   uint borne = 0;

   for (it = ref_.begin(); it != ref_.end(); it++)
   {
       if (nb <= it->first && nb >= borne)
           return it->second->clone();
       borne = it->first;
   }
   return NULL;
}

APowerup *PowerupFactory::create(void) const
{
    uint nb = (random() % PERCENT_FACTORY) + 1;

    if (nb == 1)
        return PowerupFactory::percentDrop();
    return NULL;
}

PowerupFactory *PowerupFactory::getInstance(void)
{
    if (!instance_)
        instance_ = new PowerupFactory;
    return instance_;
}

void PowerupFactory::deleteInstance(void)
{
    delete instance_;
    instance_ = NULL;
}

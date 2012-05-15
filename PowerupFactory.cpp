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
    ref_.push_back(new VelocityPowerup(Vector3d(), Vector3d(), Vector3d()));
    ref_.push_back(new RangePowerup(Vector3d(), Vector3d(), Vector3d()));
    ref_.push_back(new AmmoPowerup(Vector3d(), Vector3d(), Vector3d()));
}

PowerupFactory::~PowerupFactory()
{
  std::vector<APowerup*>::iterator it;

  for (it = ref_.begin(); it != ref_.end(); it++)
    delete (*it);
}

APowerup *PowerupFactory::create(void) const
{
    uint nb = (rand() % (Bomberman::NONE * 3));

    // std::cout << nb << std::endl;
    if (nb >= ref_.size())
        return NULL;
    return (ref_.at(nb)->clone());
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

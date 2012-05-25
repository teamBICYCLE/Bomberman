/*
** BEER-WARE LICENSE :
** PowerupFactory.hpp for PowerupFactory class (5/3/2012)
** <sylvia_r@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#ifndef     POWERUPFACTORY_HPP
# define    POWERUPFACTORY_HPP

# include <vector>
# include "APowerup.hh"
# include "MinePowerup.hh"
# include "AmmoPowerup.hh"
# include "KickPowerup.hh"
# include "VelocityPowerup.hh"
# include "RangePowerup.hh"
# include "Vector3d.hh"

# define PERCENT_FACTORY    3

namespace Bomberman
{
    class PowerupFactory
    {

    public:
        static PowerupFactory *getInstance(void);
        static void deleteInstance(void);
        APowerup *percentDrop(void) const;

    public:
        APowerup *create(void) const;

    private:
        PowerupFactory();
        ~PowerupFactory();

    private:
        std::vector< std::pair<uint, APowerup *> > ref_;
        static PowerupFactory *instance_;
    };
}

#endif // POWERUPFACTORY_HPP

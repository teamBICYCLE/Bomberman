//
// VelocityPowerup.hh for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Thu May  3 14:49:39 2012 geoffroy lafontaine
// Last update Thu May  3 16:11:14 2012 geoffroy lafontaine
//

#ifndef		__VELOCITYPOWERUP_HH__
# define	__VELOCITYPOWERUP_HH__

# include "APowerup.hh"
# include "Player.hh"

namespace	Bomberman
{
  class VelocityPowerup : public APowerup
  {
  public:
    VelocityPowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    virtual ~VelocityPowerup(void);

  public:
    void activate(Player&) const;

  private:
    VelocityPowerup(const VelocityPowerup& other);
    VelocityPowerup& operator=(const VelocityPowerup& other);
  };
}

#endif		/* !__VELOCITYPOWERUP_HH__ */

//
// VelocityPowerup.hh for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 14:49:39 2012 geoffroy lafontaine
// Last update Sat May 26 15:53:12 2012 thibault carpentier
//

#ifndef		__VELOCITYPOWERUP_HH__
# define	__VELOCITYPOWERUP_HH__

# include "APowerup.hh"
# include "Player.hh"
# include "RotatingImg.hh"

namespace	Bomberman
{
  class VelocityPowerup : public APowerup
  {
  public:
    VelocityPowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    virtual ~VelocityPowerup(void);

  public:
    virtual void		activate(Player&);
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual VelocityPowerup *clone(void);

  private:
    VelocityPowerup(const VelocityPowerup& other);
    VelocityPowerup& operator=(const VelocityPowerup& other);
    RotatingImg   model_;
  };
}

#endif		/* !__VELOCITYPOWERUP_HH__ */

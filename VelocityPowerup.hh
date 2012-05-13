//
// VelocityPowerup.hh for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 14:49:39 2012 geoffroy lafontaine
// Last update Sun May 13 15:21:11 2012 lois burg
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
    virtual void		activate(Player&);
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual const std::string&	type(void) const;
    virtual VelocityPowerup *clone(void);

  private:
    VelocityPowerup(const VelocityPowerup& other);
    VelocityPowerup& operator=(const VelocityPowerup& other);
  };
}

#endif		/* !__VELOCITYPOWERUP_HH__ */

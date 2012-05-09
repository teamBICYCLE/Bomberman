//
// APowerup.hh for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 14:33:03 2012 geoffroy lafontaine
// Last update Wed May  9 17:46:17 2012 Jonathan Machado
//

#ifndef		__APOWERUP_HH__
# define	__APOWERUP_HH__

# include "Player.hh"

namespace	Bomberman
{
  enum	ePowerupType { VELOCITY = 0, RANGE, AMMO, NONE };

  class	APowerup : public AObject
  {
  public:
    APowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& type);
    virtual ~APowerup(void);

  public:
    virtual void		activate(Player&) const;
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs) = 0;
    virtual void		draw(void) = 0;
    virtual const std::string&	type(void) const = 0;
    virtual APowerup		*clone(void) = 0;

  private:
    APowerup(const APowerup& other);
    APowerup& operator=(const APowerup& other);
  };
}

#endif		/* !__APOWERUP_HH__ */

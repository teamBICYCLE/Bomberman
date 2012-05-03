//
// APowerup.hh for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Thu May  3 14:33:03 2012 geoffroy lafontaine
// Last update Thu May  3 16:10:05 2012 geoffroy lafontaine
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
    APowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    virtual ~APowerup(void);

  public:
    virtual void activate(Player&) const;

  private:
    APowerup(const APowerup& other);
    APowerup& operator=(const APowerup& other);
  };
}

#endid		/* !__APOWERUP_HH__ */

//
// RangePowerup.hh for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 15:11:59 2012 geoffroy lafontaine
// Last update Fri May  4 10:21:09 2012 lois burg
//

#ifndef		__RANGEPOWERUP_HH__
# define	__RANGEPOWERUP_HH__

# include "APowerup.hh"
# include "Player.hh"

namespace	Bomberman
{
  class RangePowerup : public APowerup
  {
  public:
    RangePowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    virtual ~RangePowerup(void);

  public:
    virtual void		activate(Player&) const;
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys);
    virtual void		draw(void);
    virtual const std::string&	type(void) const;

  private:
    RangePowerup(const RangePowerup& other);
    RangePowerup& operator=(const RangePowerup& other);
  };
}

#endif		/* !__RANGEPOWERUP_HH__ */

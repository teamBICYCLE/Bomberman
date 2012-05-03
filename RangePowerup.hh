//
// RangePowerup.hh for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Thu May  3 15:11:59 2012 geoffroy lafontaine
// Last update Thu May  3 15:18:05 2012 geoffroy lafontaine
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
    RangePowerup(void);
    virtual ~RangePowerup(void);
    
  public:
    void activate(Player&) const;

  private:
    RangePowerup(const RangePowerup& other);
    RangePowerup& operator=(const RangePowerup& other);
  };
}

#endif		/* !__RANGEPOWERUP_HH__ */

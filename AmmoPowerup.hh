//
// AmmoPowerup.hh for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Thu May  3 15:18:35 2012 geoffroy lafontaine
// Last update Thu May  3 15:21:30 2012 geoffroy lafontaine
//

#ifndef		__AMMOPOWERUP_HH__
# define	__AMMOPOWERUP_HH__

# include "APowerup.hh"
# include "Player.hh"

namespace	Bomberman
{
  class	AmmoPowerup : public APowerup
  {
  public:
    AmmoPowerup(void);
    virtual ~AmmoPowerup(void);

  public:
    void activate(Player&) const;

  private:
    AmmoPowerup(const AmmoPowerup& other);
    AmmoPowerup& operator=(const AmmoPowerup& other);
  };
}

#endif		/* !__AMMOPOWERUP_HH__ */

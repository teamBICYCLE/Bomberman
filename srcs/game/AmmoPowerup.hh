//
// AmmoPowerup.hh for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 15:18:35 2012 geoffroy lafontaine
// Last update Thu May 17 11:49:16 2012 lois burg
//

#ifndef		__AMMOPOWERUP_HH__
# define	__AMMOPOWERUP_HH__

# include "APowerup.hh"
# include "Player.hh"
# include "TexturedCube.hh"

namespace	Bomberman
{
  class	AmmoPowerup : public APowerup
  {
  public:
    AmmoPowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    virtual ~AmmoPowerup(void);

  public:
    virtual void		activate(Player&);
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual AmmoPowerup *clone(void);

  private:
    AmmoPowerup(const AmmoPowerup& other);
    AmmoPowerup& operator=(const AmmoPowerup& other);
    TexturedCube  model_;
  };
}

#endif		/* !__AMMOPOWERUP_HH__ */

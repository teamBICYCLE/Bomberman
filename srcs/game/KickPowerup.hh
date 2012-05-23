//
// KickPowerup.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 18 14:56:53 2012 lois burg
// Last update Fri May 18 14:56:54 2012 lois burg
//

#ifndef		__KICKPOWERUP_HH__
# define	__KICKPOWERUP_HH__

# include "APowerup.hh"
# include "Player.hh"
# include "TexturedCube.hh"

namespace	Bomberman
{
  class	KickPowerup : public APowerup
  {
  public:
    KickPowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    virtual ~KickPowerup(void);

  public:
    virtual void		activate(Player&);
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual KickPowerup *clone(void);

  private:
    KickPowerup(const KickPowerup& other);
    KickPowerup& operator=(const KickPowerup& other);
    TexturedCube  model_;
  };
}

#endif		/* !__KICKPOWERUP_HH__ */

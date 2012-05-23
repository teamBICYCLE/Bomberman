//
// MinePowerup.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 17 18:17:41 2012 lois burg
// Last update Thu May 17 18:22:41 2012 lois burg
//

#ifndef		__MINEPOWERUP_HH__
# define	__MINEPOWERUP_HH_

# include "APowerup.hh"
# include "Player.hh"
# include "TexturedCube.hh"
# include "RotatingImg.hh"

namespace	Bomberman
{
  class	MinePowerup : public APowerup
  {
  public:
    MinePowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    virtual ~MinePowerup(void);

  public:
    virtual void	activate(Player&);
    virtual void	update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void	draw(void);
    virtual MinePowerup *clone(void);

  private:
    MinePowerup(const MinePowerup& other);
    MinePowerup& operator=(const MinePowerup& other);
    RotatingImg  model_;
  };
}

#endif /* !__MINEPOWERUP_HH__*/

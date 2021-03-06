//
// APowerup.hh for bomberman in /home/lafont_g//tek2/bomberman/PowerUp
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May  3 14:33:03 2012 geoffroy lafontaine
// Last update Sat May 26 17:48:24 2012 thibault carpentier
//

#ifndef		__APOWERUP_HH__
# define	__APOWERUP_HH__

# include "Player.hh"
# include "Explosion.hh"
# include "Danger.hh"

namespace	Bomberman
{
  enum	ePowerupType { VELOCITY = 0, RANGE, AMMO, MINE, KICK, NONE };

  class	APowerup : public AObject
  {
  public:
    APowerup(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& type);
    virtual ~APowerup(void);

  public:
    virtual void		activate(Player&);
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs) = 0;
    virtual void		draw(void) = 0;
    virtual void		interact(Character *ch, std::list<AObject*>& objs);
    virtual void		interact(Explosion *e, std::list<AObject*>& objs);
    virtual APowerup    *clone(void) = 0;
    virtual void        serialize(QDataStream &out) const {(void)out;}
    virtual void        unserialize(QDataStream &in) {(void)in;}
    virtual void        sInit(void){}

  public:
    virtual void                setDanger(std::vector<std::vector<std::pair<int, int> > > &map,
					 std::list<AObject*>objs,
					  int x, int y) const;

  private:
    APowerup(const APowerup& other);
    APowerup& operator=(const APowerup& other);
  };
}

#endif		/* !__APOWERUP_HH__ */

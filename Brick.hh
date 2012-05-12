//
// Brick.hh for Brick in /home/sylvia_r//Desktop/projet/tek2/Bomberman
//
// Made by romain sylvian
// Login   <sylvia_r@epitech.net>
//
// Started on  Thu May  3 15:18:05 2012 romain sylvian
// Last update Fri May 11 11:35:27 2012 lois burg
//
//

#ifndef		__BRICK_HH__
# define	__BRICK_HH__

# include   <vector>
# include	"AObject.hh"
# include   "APowerup.hh"
# include   "PowerupFactory.hh"

namespace	Bomberman
{
  class	Brick : public AObject
  {
  public:
    Brick(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz = Vector3d(40, 40, 0));
    virtual ~Brick();

  public:
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual const std::string&	type(void) const;
    virtual void		loot(std::list<AObject *> &);

  private:
    APowerup	*loot_;
  };
}
#endif /* !__BRICK_HH__*/

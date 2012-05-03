//
// Brick.hh for Brick in /home/sylvia_r//Desktop/projet/tek2/Bomberman
//
// Made by romain sylvian
// Login   <sylvia_r@epitech.net>
//
// Started on  Thu May  3 15:18:05 2012 romain sylvian
// Last update Thu May  3 15:26:43 2012 romain sylvian
//
//

#ifndef		__BRICK_HH__
# define	__BRICK_HH__

# include	"AObject.hh"
# include   "APowerup.hh"
# include   "PowerupFactory.hh"

namespace	Bomberman
{
  class	Brick : public AObject
  {
  public:
    Brick(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    virtual ~Brick();

  public:
    virtual void		update(const gdl::GameClock& clock,
				       const gdl::Input& keys);
    virtual void		draw(void);
    virtual const std::string&	type(void) const;

  private:
    APowerup	*loot_;
  };
}
#endif /* !__BRICK_HH__*/

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
      Brick(const Vector3d& pos = Vector3d(), const Vector3d& rot = Vector3d(), const Vector3d& sz = Vector3d(40, 40, 0));
      Brick(const Brick &);
    virtual ~Brick();

  public:
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual const std::string&	type(void) const;
    virtual void		loot(std::list<AObject *> &);

    /* Serialization */
    virtual void serialize(QDataStream &out) const;
    virtual void unserialize(QDataStream &in);
    static void sInit(void);

  private:s
    APowerup	*loot_;
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Brick);
QDataStream &operator << (QDataStream &out, const Bomberman::Brick &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Brick &v);

#endif /* !__BRICK_HH__*/

//
// Brick.hh for Brick in /home/sylvia_r//Desktop/projet/tek2/Bomberman
//
// Made by romain sylvian
// Login   <sylvia_r@epitech.net>
//
// Started on  Thu May  3 15:18:05 2012 romain sylvian
// Last update Sat May 26 17:50:53 2012 thibault carpentier
//
//

#ifndef		__BRICK_HH__
# define	__BRICK_HH__

# include   <vector>
# include   "AObject.hh"
# include   "APowerup.hh"
# include   "PowerupFactory.hh"
# include	"Explosion.hh"
# include   "TexturedCube.hh"

namespace	Bomberman
{
  class	Brick : public AObject
  {
  public:
      Brick(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz = Vector3d(40, 40, 0));
      Brick(const Brick &);
      Brick();
      virtual ~Brick();

  public:
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual void		loot(std::list<AObject *> &);
    virtual void		destroy(std::list<AObject*>& objs);
    virtual void		interact(Explosion *e, std::list<AObject*>& objs);
    virtual void		setDanger(std::vector<std::vector<std::pair<int, int> > > &map,
					  std::list<AObject*>objs,
					  int x, int y) const;
    /* Serialization */
    virtual void serialize(QDataStream &out) const;
    virtual void unserialize(QDataStream &in);
    static void sInit(void);
    virtual void toQvariant(QSettings &w) const;

  private:
    APowerup	*loot_;
    TexturedCube  model_;
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Brick);
QDataStream &operator << (QDataStream &out, const Bomberman::Brick &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Brick &v);

#endif /* !__BRICK_HH__*/

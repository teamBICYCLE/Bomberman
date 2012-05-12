//
// Explosion.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 11 11:45:47 2012 lois burg
// Last update Fri May 11 15:14:38 2012 lois burg
//

#ifndef		__EXPLOSION_HH__
# define	__EXPLOSION_HH__

# include	"AObject.hh"
# include	"BoundingBox.hh"

namespace	Bomberman
{
  class	Explosion : public AObject
  {
  public:  public:
    Explosion(const Vector3d& pos, const Vector3d& sz, uint damage);
    virtual ~Explosion();

  public:
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual const std::string&	type(void) const;

    /* Serialization */
    virtual void serialize(QDataStream &out) const;
    virtual void unserialize(QDataStream &in);
    static void sInit(void);

  private:
    uint	damage_;
    BoundingBox	bBox_;
  };
}

#endif /* !__EXPLOSION_HH__*/

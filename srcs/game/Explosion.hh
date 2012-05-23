//
// Explosion.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 11 11:45:47 2012 lois burg
// Last update Mon May 21 10:31:36 2012 lois burg
//

#ifndef		__EXPLOSION_HH__
# define	__EXPLOSION_HH__

# include	"AObject.hh"
# include	"Character.hh"
# include	"BoundingBox.hh"
# include	"Player.hh"
# include       "ExplosionBlock.hh"

namespace	Bomberman
{
  class	Explosion : public AObject
  {
  public:
    Explosion(const Vector3d& pos, const Vector3d& sz, uint damage, Player& owner);
    Explosion(const Explosion& other);
    Explosion();
    virtual ~Explosion();

  public:
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual void		interact(Character *ch, std::list<AObject*>& objs);

    /* Serialization */
    virtual void serialize(QDataStream &out) const;
    virtual void unserialize(QDataStream &in);
    static void sInit(void);
    virtual void toQvariant(QSettings &w);

    /* tmp */
    void aff(void) const;

  public:
    uint		getDamage(void) const;
    BoundingBox&	getBBox(void);
    Player&		getOwner(void);

  private:
    uint	damage_;
    BoundingBox	bBox_;
    float	timeOnScreen_;
    float	lastTime_;
    Player&	owner_;
    ExplosionBlock  model_;
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Explosion);
QDataStream &operator << (QDataStream &out, const Bomberman::Explosion &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Explosion &v);


#endif /* !__EXPLOSION_HH__*/

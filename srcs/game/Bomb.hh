//
// Bomb.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 11:50:46 2012 lois burg
// Last update Mon May 21 10:39:13 2012 lois burg
//

#ifndef		__BOMB_HH__
# define	__BOMB_HH__

# include	"AObject.hh"
# include	"Explosion.hh"
# include	"Player.hh" //a remplacer par la classe qui emglobera joueurs et monstres

namespace	Bomberman
{
  class	Bomb : public AObject
  {
  public:
      Bomb(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, int range, int timeOut, Player& owner);
      Bomb(const Bomb &);
      Bomb();
      virtual ~Bomb();

  public:
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual void		interact(Character *ch, std::list<AObject*>& objs);
    virtual void		interact(Explosion *e, std::list<AObject*>& objs);
    virtual void		destroy(std::list<AObject*>& objs);

    /* Serialization */
    virtual void serialize(QDataStream &out) const;
    virtual void unserialize(QDataStream &in);
    static void sInit(void);
    virtual void toQvariant(QSettings &w) const;

    /* Tmp */
    void aff(void) const;

  public:
    void	adjustPos(void);
    void	explode(std::list<AObject*>& objs);

  public:
    float	getTimeOut(void) const;
    float	getLastTime(void) const;
    const Player&	getOwner(void) const;
    bool	getOwnerCollide(void) const;
    int     getRange(void) const;

  public:
    void	setTimeOut(const float timeOut);
    void	setSpeed(const Vector3d &s);
    void	setOwnerCollide(bool b);

  private:
    void	checkPosition(Explosion *e, bool& isInvalid, std::list<AObject*>& objs);

  protected:
    int         range_;
    float       timeOut_;
    Player&     owner_;
    Vector3d	speed_;
    float       lastTime_;
    bool	ownerCollide_;
    BoundingBox	bBox_;
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Bomb);
QDataStream &operator << (QDataStream &out, const Bomberman::Bomb &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Bomb &v);

#endif /* !__BOMB_HH__*/

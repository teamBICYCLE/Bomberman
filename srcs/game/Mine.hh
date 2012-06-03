//
// Mine.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 17 16:56:25 2012 lois burg
// Last update Sun Jun  3 19:41:27 2012 lois burg
//

#ifndef		__MINE_HH__
# define	__MINE_HH__

# include	"Bomb.hh"
# include	"Explosion.hh"
# include	"gdlModel.hh"
# include	"Danger.hh"

namespace	Bomberman
{
  class	Mine : public Bomb
  {
  public:
    Mine(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, Player& owner);
    Mine(const Mine&);
    Mine();
    virtual ~Mine();

  public:
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void                draw();
    virtual void		interact(Character *ch, std::list<AObject*>& objs);
    virtual void		interact(Explosion *e, std::list<AObject*>& objs);
    virtual void		destroy(std::list<AObject*>& objs);

    virtual void                setDanger(std::vector<std::vector<std::pair<int, int> > > &map,
                                          std::list<AObject*>objs,
                                          int x, int y) const;

    /* Serialization */
    virtual void	serialize(QDataStream &out) const;
    virtual void	unserialize(QDataStream &in);
    static void		sInit(void);
    void            toQvariant(QSettings &w) const;

  public:
    void	setChainReaction(bool b);

  public:
    void	explode(std::list<AObject*>& objs);

  private:
    bool	chainReaction_;
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Mine);
QDataStream &operator << (QDataStream &out, const Bomberman::Mine &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Mine &v);

#endif /* !__MINE_HH__*/

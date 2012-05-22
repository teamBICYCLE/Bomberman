//
// FireBlock.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Sat May 19 18:34:59 2012 lois burg
// Last update Mon May 21 11:54:56 2012 lois burg
//

#ifndef		__FIREBLOCK_HH__
# define	__FIREBLOCK_HH__

# include	"Block.hh"

namespace	Bomberman
{
  class	FireBlock : public Block
  {
  public:
      FireBlock(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const Vector3d& dir);
      FireBlock(const FireBlock &other);
      FireBlock();
      virtual ~FireBlock();

  public:
    virtual void	update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void	draw(void);
    virtual void	destroy(void);

    /* Serialization */
    virtual void	serialize(QDataStream &out) const;
    virtual void	unserialize(QDataStream &in);
    static void		sInit(void);
    virtual void    toQvariant(QSettings &w);

  private:
    void	spitFire(std::list<AObject*>& objs);

  private:
    Vector3d	dir_;
    int		range_;
    float	lastTime_;
    float	timer_;
    TexturedCube  model_;
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::FireBlock);
QDataStream &operator << (QDataStream &out, const Bomberman::FireBlock &v);
QDataStream &operator >> (QDataStream &in, Bomberman::FireBlock &v);

#endif /* !__FIREBLOCK_HH__*/

//
// Block.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:02:52 2012 lois burg
// Last update Wed May 30 15:31:21 2012 thibault carpentier
//

#ifndef		__BLOCK_HH__
# define	__BLOCK_HH__

# include	"AObject.hh"
# include       "TexturedCube.hh"
# include       "RotatingImg.hh"
# include	"Danger.hh"

namespace	Bomberman
{
  class	Block : public AObject
  {
  public:
      Block(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
      Block(const Block &other);
      Block();
      virtual ~Block();

  public:
      virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
      virtual void		draw(void);
      virtual void		destroy(void);
      virtual void		setDanger(std::vector<std::vector<std::pair<int, int> > > &map,
                                          std::list<AObject*>objs,
                                          int x, int y) const;
      TexturedCube &getCube();

    /* Serialization */
    virtual void serialize(QDataStream &out) const;
    virtual void unserialize(QDataStream &in);
    static void sInit(void);
    virtual void toQvariant(QSettings &w) const;

  private:
    TexturedCube  model_;
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Block);
QDataStream &operator << (QDataStream &out, const Bomberman::Block &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Block &v);

#endif /* !__BLOCK_HH__*/

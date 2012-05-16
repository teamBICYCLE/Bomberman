//
// Block.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:02:52 2012 lois burg
// Last update Fri May 11 11:30:49 2012 lois burg
//

#ifndef		__BLOCK_HH__
# define	__BLOCK_HH__

# include	"AObject.hh"

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
    virtual const std::string&	type(void) const;
    virtual void		destroy(void);

    /* Serialization */
    virtual void serialize(QDataStream &out) const;
    virtual void unserialize(QDataStream &in);
    static void sInit(void);

    /* TMP */
    void aff(void) const;
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Block);
QDataStream &operator << (QDataStream &out, const Bomberman::Block &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Block &v);

#endif /* !__BLOCK_HH__*/

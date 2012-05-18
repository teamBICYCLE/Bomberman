//
// Ghost.hh for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May 17 15:28:13 2012 geoffroy lafontaine
// Last update Fri May 18 12:29:16 2012 thibault carpentier
//

#ifndef		__GHOST_HH__
# define	__GHOST_HH__

# include	<sys/types.h>
# include	"Monster.hh"

namespace	Bomberman
{

# define GHOST_SCRIPT "./Ressources/lua/Ghost.lua"

  class Ghost : public Monster
  {
  public:
    Ghost(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, uint damage = 1);
    Ghost(const Ghost &);
    Ghost();
    virtual ~Ghost();

  public:
    /* Serialization */
    virtual void serialize(QDataStream &out) const;
    virtual void unserialize(QDataStream &in);
    static void sInit(void);
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Ghost);
QDataStream &operator << (QDataStream &out, const Bomberman::Ghost &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Ghost &v);

#endif /* !__GHOST_HH__ */

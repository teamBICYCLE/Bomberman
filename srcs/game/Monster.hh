//
// Monster.hh for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Sat May 12 09:08:54 2012 geoffroy lafontaine
// Last update Fri May 18 17:39:01 2012 Jonathan Machado
//

#ifndef		__MONSTER_HH__
# define	__MONSTER_HH__

# include	<sys/types.h>
# include	"Character.hh"
# include	"BoundingBox.hh"
# include	"Brain.hh"

namespace	Bomberman
{
# define MONSTER_SCRIPT "./Ressources/lua/Monster.lua"

  class Monster : public Character
  {

  public:
    typedef void (Character::*t_monsterActionFun)(void);

  public:
    Monster(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, Thinking::Brain *, uint damage = 1);
    Monster(const Monster &);
    Monster();
    virtual ~Monster();

  public:
    virtual void	update(gdl::GameClock& clock, eDirection direction, std::list<AObject*>& objs);
    virtual void        update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void	draw(void);
    virtual void	interact(Character *ch, std::list<AObject*>& objs);

  public:
    /* Serialization */
    virtual void serialize(QDataStream &out) const;
    virtual void unserialize(QDataStream &in);
    static void sInit(void);

    /* tmp */
    void aff(void) const;

  public:
    uint	getDamage(void) const;

  public:
    void	setDamage(uint damage);

  protected:
    void	turnLeft(void);
    void	turnRight(void);
    void	turnUp(void);
    void	turnDown(void);

  protected:
    void	moveAnimation(void);

  protected:
    std::map<eDirection, void (Character::*)(void)> actionsMap_;
    bool	moved_;
    uint	damage_;
    Bomberman::Thinking::Brain *brainScript_;
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Monster);
QDataStream &operator << (QDataStream &out, const Bomberman::Monster &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Monster &v);

#endif /* !__MONSTER_HH__ */
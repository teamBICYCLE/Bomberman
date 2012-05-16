//
// Monster.hh for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Sat May 12 09:08:54 2012 geoffroy lafontaine
// Last update Tue May 15 17:33:25 2012 lois burg
//

#ifndef		__MONSTER_HH__
# define	__MONSTER_HH__

# include	<sys/types.h>
# include	"Character.hh"
# include	"BoundingBox.hh"

namespace	Bomberman
{
  class Monster : public Character
  {
  public:
    typedef void (Character::*t_monsterActionFun)(void);

  public:
    Monster(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, uint damage = 1);
    Monster(const Monster &);
    Monster();
    virtual ~Monster();

  public:
    virtual void	update(gdl::GameClock& clock, eDirection direction, std::list<AObject*>& objs);
    virtual void        update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void	draw(void);
    virtual const std::string&	type(void) const;
    virtual void	interact(Character *ch);

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

  private:
    void	turnLeft(void);
    void	turnRight(void);
    void	turnUp(void);
    void	turnDown(void);

  private:
    void	moveAnimation(void);

  private:
    std::map<eDirection, void (Character::*)(void)> actionsMap_;
    bool	moved_;
    uint	damage_;
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Monster);
QDataStream &operator << (QDataStream &out, const Bomberman::Monster &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Monster &v);

#endif /* !__MONSTER_HH__ */

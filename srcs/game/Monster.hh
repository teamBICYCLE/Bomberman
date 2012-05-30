//
// Monster.hh for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Sat May 12 09:08:54 2012 geoffroy lafontaine
// Last update Wed May 30 17:04:03 2012 thibault carpentier
//

#ifndef		__MONSTER_HH__
# define	__MONSTER_HH__

# include	<sys/types.h>
# include	"Character.hh"
# include	"BoundingBox.hh"
# include	"Brain.hh"
# include       "gdlModel.hh"

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
    virtual void	update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void	draw(void);
    virtual void	interact(Character *ch, std::list<AObject*>& objs);
    virtual void	setVirtualPheromones(std::vector<std::vector<std::pair<int, int> > > &map,
					     std::list<AObject*>objs,
					     int x, int y) const;

  public:
    /* Serialization */
    virtual void serialize(QDataStream &out) const;
    virtual void unserialize(QDataStream &in);
    static void sInit(void);
    virtual void toQvariant(QSettings &w) const;

  public:
    uint	getDamage(void) const;

  public:
    void	setDamage(uint damage);
    Bomberman::Thinking::Brain	*getBrain(void) const;

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
    gdlModel    model_;
  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Monster);
QDataStream &operator << (QDataStream &out, const Bomberman::Monster &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Monster &v);

#endif /* !__MONSTER_HH__ */

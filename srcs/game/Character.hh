//
// Character.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 17:08:02 2012 lois burg
// Last update Mon May 21 15:22:39 2012 lois burg
//

#ifndef		__CHARACTER_HH__
# define	__CHARACTER_HH__

# include	"AObject.hh"
# include	"BoundingBox.hh"

namespace	Bomberman
{
  class	Explosion;
  enum eDirection { UP, RIGHT, DOWN, LEFT, NODIR};

  class	Character : public AObject
  {
  public:
    Character(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& modelName, uint life, double speed);
    Character(const std::string &);
    virtual ~Character();

  public:
    void	turnLeft(void);
    void	turnRight(void);
    void	turnUp(void);
    void	turnDown(void);

  public:
    void	takeDamage(uint damage);
    void	bump(const Vector3d& bumpPos);

  public:
    uint	getLife(void) const;
    double      getSpeed(void) const;
    bool	isInvincible(void) const;
    int		getId(void) const;
    const Vector3d&	getSavedPos(void) const;
    virtual int	getScoreValue(void) const;
    const BoundingBox	*getBBox(void) const;

  public:
    void	setLife(const uint life);
    void	setSpeed(const double speed);
    void	setInvincible(bool b);

  public:
    virtual void	destroy(void);
    virtual void	interact(Explosion *b, std::list<AObject*>& objs);

  public:
    /* Serialization */
    virtual void serialize(QDataStream &out) const = 0;
    virtual void unserialize(QDataStream &in) = 0;

  public:
    static int	CharacterId;

  protected:
    uint        life_;
    double      speed_;
    double      speedAdapter_;
    BoundingBox	*bBox_;
    bool	moved_;
    bool	isInvincible_;
    Vector3d	save_;
    int		id_;
  };
}

#endif /* !__CHARACTER_HH__*/

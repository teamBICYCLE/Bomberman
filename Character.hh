//
// Character.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 17:08:02 2012 lois burg
// Last update Sat May 12 10:51:58 2012 geoffroy lafontaine
//

#ifndef		__CHARACTER_HH__
# define	__CHARACTER_HH__

# include	"AObject.hh"
# include	"BoundingBox.hh"

namespace	Bomberman
{
  enum eDirection { UP, RIGHT, DOWN, LEFT };

  class	Character : public AObject
  {
  public:
    Character(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& modelName, uint life, double speed);
    virtual ~Character();

  public:
    void	turnLeft(void);
    void	turnRight(void);
    void	turnUp(void);
    void	turnDown(void);

  public:
    void	takeDamage(uint damage);
    
  public:
    uint	getLife(void) const;
    double      getSpeed(void) const;

  public:
    void	setLife(const uint life);
    void	setSpeed(const double speed);

  public:
    /* Serialization */
    virtual void serialize(QDataStream &out) const = 0;
    virtual void unserialize(QDataStream &in) = 0;

  protected:
    uint        life_;
    double      speed_;
    double      speedAdapter_;
    BoundingBox	bBox_;
    bool	moved_;
  };
}

#endif /* !__CHARACTER_HH__*/

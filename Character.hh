//
// Character.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 17:08:02 2012 lois burg
// Last update Tue May 15 17:28:33 2012 lois burg
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
    Character(const std::string &);
    virtual ~Character();

  public:
    void	turnLeft(void);
    void	turnRight(void);
    void	turnUp(void);
    void	turnDown(void);

  public:
    void	takeDamage(uint damage);
    void	bump(void);

  public:
    uint	getLife(void) const;
    double      getSpeed(void) const;
    bool	isInvincible(void) const;

  public:
    void	setLife(const uint life);
    void	setSpeed(const double speed);
    void	setInvincible(bool b);

  public:
    virtual void	destroy(void);

  protected:
    uint        life_;
    double      speed_;
    double      speedAdapter_;
    BoundingBox	*bBox_;
    bool	moved_;
    bool	isInvincible_;
    Vector3d	save_;
  };
}

#endif /* !__CHARACTER_HH__*/

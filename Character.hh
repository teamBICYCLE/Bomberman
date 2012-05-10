//
// Character.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 17:08:02 2012 lois burg
// Last update Thu May 10 17:26:14 2012 lois burg
//

#ifndef		__CHARACTER_HH__
# define	__CHARACTER_HH__

# include	"AObject.hh"
# include	"BoundingBox.hh"

namespace	Bomberman
{
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

  protected:
    uint	life_;
    double	speed_;
    BoundingBox	bBox_;
  };
}

#endif /* !__CHARACTER_HH__*/

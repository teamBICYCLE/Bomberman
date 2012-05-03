//
// Player.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 13:46:49 2012 lois burg
// Last update Thu May  3 16:47:56 2012 lois burg
//

#ifndef		__PLAYER_HH__
# define	__PLAYER_HH__

# include	"AObject.hh"

namespace	Bomberman
{
  class	Player : public AObject
  {
  public:
    Player(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    virtual ~Player();

  public:
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys);
    virtual void		draw(void);
    virtual const std::string&	type(void) const;

  public:
    uint	getLife(void) const;
    uint	getNbBombs(void) const;
    int		getSpeed(void) const;
    uint	getBombRange(void) const;

  public:
    void	setLife(const uint life);
    void	setNbBombs(const uint nbBombs);
    void	setSpeed(const int speed);
    void	setBombRange(const uint range);

  private:
    uint	life_;
    uint	nbBombs_;
    int		speed_;
    uint	bombRange_;
  };
}

#endif /* !__PLAYER_HH__*/

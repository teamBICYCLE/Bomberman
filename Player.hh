//
// Player.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 13:46:49 2012 lois burg
// Last update Thu May 10 17:27:01 2012 lois burg
//

#ifndef		__PLAYER_HH__
# define	__PLAYER_HH__

# include	<sys/types.h>
# include	"Character.hh"
# include	"BoundingBox.hh"

namespace	Bomberman
{
  class	Player : public Character
  {
  public:
    Player(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    virtual ~Player();

  public:
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual const std::string&	type(void) const;

  public:
    uint	getLife(void) const;
    uint	getNbBombs(void) const;
    double	getSpeed(void) const;
    uint	getBombRange(void) const;

  public:
    void	setLife(const uint life);
    void	setNbBombs(const uint nbBombs);
    void	setSpeed(const double speed);
    void	setBombRange(const uint range);

  private:
    void	turnLeft(std::list<AObject*>& objs);
    void	turnRight(std::list<AObject*>& objs);
    void	turnUp(std::list<AObject*>& objs);
    void	turnDown(std::list<AObject*>& objs);
    void	putBomb(std::list<AObject*>& objs);

  private:
    void	checkLeft(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap);
    void	checkRight(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap);
    void	checkUp(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap);
    void	checkDown(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap);

  private:
    void        moveAnimation(void);
    
  private:
    uint	nbBombs_;
    uint	bombRange_;
    std::map<gdl::Keys::Key, void (Player::*)(std::list<AObject*>&)> actionsMap_;
    bool        moved_;
  };
}

#endif /* !__PLAYER_HH__*/

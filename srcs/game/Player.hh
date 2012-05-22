//
// Player.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 13:46:49 2012 lois burg
// Last update Fri May 18 16:54:11 2012 lois burg
//

#ifndef		__PLAYER_HH__
# define	__PLAYER_HH__

# include	<map>
# include	<sys/types.h>
# include	"Character.hh"
# include	"BoundingBox.hh"
# include       "gdlModel.hh"

namespace	Bomberman
{
  class	Player : public Character
  {
  public:
    typedef void (Player::*t_playerActionFun)(std::list<AObject*>&);
    typedef bool (BoundingBox::*t_collideFun)(const AObject*);

  public:
    Player(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    Player(const Player &other);
    Player();
    virtual ~Player();

  public:
    virtual void	update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void	draw(void);
    virtual void	interact(Character *ch, std::list<AObject*>& objs);

  public:
    uint	getNbBombs(void) const;
    int		getNbMines(void) const;
    uint	getBombRange(void) const;
    float	getBombTime(void) const;
    virtual int	getScoreValue(void) const;
    int		getScore(void) const;
    bool	getKickAbility(void) const;

  public:
    void	setNbBombs(const uint nb);
    void	setNbMines(const int nb);
    void	setBombRange(const uint range);
    void	setBombTime(const float time);
    void	setBombCollide(bool b);
    void	addScore(int val);
    void	setKickAbility(bool b);

  public:
    /* Serialization */
    virtual void serialize(QDataStream &out) const;
    virtual void unserialize(QDataStream &in);
    static void sInit(void);

    /* tmp */
    void aff(void) const;

  private:
    void	turnLeft(std::list<AObject*>& objs);
    void	turnRight(std::list<AObject*>& objs);
    void	turnUp(std::list<AObject*>& objs);
    void	turnDown(std::list<AObject*>& objs);
    void	putBomb(std::list<AObject*>& objs);
    void	putMine(std::list<AObject*>& objs);

  private:
    void        moveAnimation(void);

  private:
    uint	nbBombs_;
    int		nbMines_;
    uint	bombRange_;
    uint	mineRange_;
    float	bombTime_;
    std::map<gdl::Keys::Key, t_collideFun>	collideMap_;
    std::map<gdl::Keys::Key, t_playerActionFun> actionsMap_;
    bool        moved_;
    bool	bombCollide_;
    bool	wasRunning_;
    int		score_;
    bool	kickAbility_;
    gdlModel    model_;

  };
}

/* Serialization */
Q_DECLARE_METATYPE(Bomberman::Player);
QDataStream &operator << (QDataStream &out, const Bomberman::Player &v);
QDataStream &operator >> (QDataStream &in, Bomberman::Player &v);
#endif /* !__PLAYER_HH__*/

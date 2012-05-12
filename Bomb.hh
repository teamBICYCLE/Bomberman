//
// Bomb.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 11:50:46 2012 lois burg
// Last update Fri May 11 11:39:52 2012 lois burg
//

#ifndef		__BOMB_HH__
# define	__BOMB_HH__

# include	"AObject.hh"
# include	"Player.hh" //a remplacer par la classe qui emglobera joueurs et monstres

namespace	Bomberman
{
  class	Bomb : public AObject
  {
  public:
    Bomb(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, int range, int timeOut, Player& owner);
    virtual ~Bomb();

  public:
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs);
    virtual void		draw(void);
    virtual const std::string&	type(void) const;
    virtual void		destroy(std::list<AObject*>& objs);

  public:
    void	adjustPos(void);
    void	explode(std::list<AObject*>& objs);

  private:
    int		range_;
    int		timeOut_;
    Player&	owner_;
    Vector3d	speed_;
  };
}

#endif /* !__BOMB_HH__*/

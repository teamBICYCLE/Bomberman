//
// AdventureState.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Sat May 19 11:29:40 2012 lois burg
// Last update Wed May 30 10:42:25 2012 lois burg
//

#ifndef		__ADVENTURESTATE_HH__
# define	__ADVENTURESTATE_HH__

# include	"AObject.hh"
# include	"Map.hh"
# include	"PlayState.hh"

namespace	Bomberman
{
  class	AdventureState : public PlayState
  {
  public:
    AdventureState();
    virtual ~AdventureState();

  public:
    virtual bool init();
    virtual void cleanUp();

    virtual void win(StatesManager *mngr);
    virtual void gameOver(StatesManager *mngr);

  private:
    Map		*curMap_;
    int		curMapId_;
    const std::string	mapBaseName_;
    const int	nbMaps_;
  };
}
#endif /* !__ADVENTURESTATE_HH__*/

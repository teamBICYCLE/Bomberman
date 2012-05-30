//
// PlayState.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 17:54:59 2012 lois burg
// Last update Wed May 30 10:45:17 2012 lois burg
//

#ifndef		__PLAYSTATE_HH__
# define	__PLAYSTATE_HH__

# include       <GDL/Image.hpp>
# include	"AObject.hh"
# include	"AGameState.hh"
# include       "Camera.hh"
# include       "ModelHandler.hh"

namespace	Bomberman
{
  class	PlayState : public AGameState
  {
  public:
    PlayState(void);
    PlayState(std::list<AObject*> *);
    virtual ~PlayState(void);

  public:
    virtual bool init();
    virtual void cleanUp();

    virtual void update(StatesManager *mngr);
    virtual void draw(StatesManager *mngr);
    virtual void pause();
    virtual void resume();

    virtual void win(StatesManager *mngr);
    virtual void gameOver(StatesManager *mngr);
    virtual void checkEndGame(StatesManager *mngr, int nbPlayers, int nbMonsters);

  protected:
    void	saveScore(void) const;
    void	clearObjs(void);

  protected:
    size_t              mapW_;
    size_t              mapH_;
    std::list<AObject*>	objs_;
    Camera              camera_;
    int                 bestScore_;
    int                 winnerId_;
    int                 characterToUpdate_;
    gdl::Image          img_;
  };
}
#endif /* !__PLAYSTATE_HH__*/

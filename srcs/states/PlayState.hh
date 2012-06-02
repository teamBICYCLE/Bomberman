//
// PlayState.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 17:54:59 2012 lois burg
// Last update Sat Jun  2 18:58:06 2012 Jonathan Machado
//

#ifndef		__PLAYSTATE_HH__
# define	__PLAYSTATE_HH__

# include       <GDL/Image.hpp>
# include	"AObject.hh"
# include	"AGameState.hh"
# include       "Camera.hh"
# include       "ModelHandler.hh"
# include       "flatTexture.hh"
# include       "Player.hh"
# include	"Brain.hh"
# include	"Carrousel/CarrouselHandler.hh"

namespace	Bomberman
{
  class	PlayState : public AGameState
  {
  public:
    PlayState(void);
    PlayState(const std::list<AObject*> *);
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

    virtual void updateReadyUpOverlay(float now);
    virtual void drawReadyUpOverlay(float now);

  protected:
    //void	saveScore(void) const;
    void	clearObjs(void);
    uint    getHeight(const std::list<AObject*> *list) const;
    uint    getWidth(const std::list<AObject*> *list) const;
    CarrouselHandler	*createInGameCH(void) const;

  protected:
    size_t              mapW_;
    size_t              mapH_;
    std::list<AObject*>	objs_;
    Camera              camera_;
    int                 bestScore_;
    int                 winnerId_;
    int                 characterToUpdate_;
    gdl::Image          img_;
    gdl::Image          bg_;
    bool                escapeDisable_;
    float               readyUp_;
    float               lastTime_;
    float                     readySize_;
    int                       readyCurrent_;
    std::vector<flatTexture>  readyImg_;
    int                sndPlayed_;
    std::string         music_;
    std::list<Player *> players_;
    DangerMap		*danger;
  };
}
#endif /* !__PLAYSTATE_HH__*/

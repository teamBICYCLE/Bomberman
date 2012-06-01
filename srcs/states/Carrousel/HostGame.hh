//
// HostGame.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 15:57:15 2012 lois burg
// Last update Fri Jun  1 14:15:18 2012 lois burg
//

#ifndef		__HOSTGAME_HH__
# define	__HOSTGAME_HH__

# include	<map>
# include	<GDL/Text.hpp>
# include	"AContent.hh"
# include	"PracticalSocket.h"
# include	"Select.hh"

namespace	Bomberman
{
  class	HostGame : public AContent
  {
  private:
    typedef void (HostGame::*t_paramFunc)(StatesManager *);
    typedef void (HostGame::*t_modifyParam)(int);
    enum ParamIdx
      {
	MapWidth = 0,
	MapHeight,
	NbPlayers
      };
    static const int	NbParams = 3;

  public:
    HostGame();
    virtual ~HostGame();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    void		drawIntAt(int val, int x, int y);
    void		drawArrow(void) const;
    void		drawButton(void) const;

  private:
    void		upArrow(StatesManager *sMg);
    void		downArrow(StatesManager *sMg);
    void		leftArrow(StatesManager *sMg);
    void		rightArrow(StatesManager *sMg);
    void		returnArrow(StatesManager *sMg);

  private:
    void		modifyMapWidth(int val);
    void		modifyMapHeight(int val);
    void		modifyNbPlayers(int val);

  private:
    void		resetSelect(void);
    void		createServSock(void);

  private:
    std::map<gdl::Keys::Key, t_paramFunc> paramMap_;
    std::map<ParamIdx, t_modifyParam>	  modifyMap_;
    bool			returnHit_;
    bool			upHit_;
    bool			downHit_;
    bool			leftHit_;
    bool			rightHit_;
    int				mapWidth_;
    int				mapHeight_;
    int				nbPlayers_;
    int				currentSelection_;
    bool			editing_;
    bool			waitingClients_;
    int				curClient_;
    TCPServerSocket		*serv_;
    std::vector<TCPSocket*>	clients_;
    Select			select_;
    gdl::Text			*text_;
    float			dotTimer_;
    float			lastTime_;
    int				nbDots_;
  };
}

#endif /* !__HOSTGAME_HH__*/

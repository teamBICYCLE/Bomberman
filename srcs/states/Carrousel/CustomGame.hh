//
// CustomGame.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 15:57:15 2012 lois burg
// Last update Thu May 31 15:30:19 2012 lois burg
//

#ifndef		__CUSTOMGAME_HH__
# define	__CUSTOMGAME_HH__

# include	<map>
# include	<GDL/Text.hpp>
# include	"AContent.hh"

namespace	Bomberman
{
  class	CustomGame : public AContent
  {
  private:
    typedef void (CustomGame::*t_paramFunc)(StatesManager *);
    typedef void (CustomGame::*t_modifyParam)(int);
    enum ParamIdx
      {
	MapWidth = 0,
	MapHeight,
	NbPlayers,
	NbMonsters,
	NbGhosts
      };
    static const int	NbParams = 5;

  public:
    CustomGame();
    virtual ~CustomGame();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    void		drawIntAt(int val, int x, int y);
    void		drawArrow(void) const;

  private:
    void		upArrow(StatesManager *sMg);
    void		downArrow(StatesManager *sMg);
    void		returnArrow(StatesManager *sMg);

  private:
    void		modifyMapWidth(int val);
    void		modifyMapHeight(int val);
    void		modifyNbPlayers(int val);
    void		modifyNbMonsters(int val);
    void		modifyNbGhosts(int val);

  private:
    std::map<gdl::Keys::Key, t_paramFunc> paramMap_;
    std::map<ParamIdx, t_modifyParam>	  modifyMap_;
    bool	returnHit_;
    bool        upHit_;
    bool        downHit_;
    int		mapWidth_;
    int		mapHeight_;
    int		nbPlayers_;
    int		nbMonsters_;
    int		nbGhosts_;
    int		currentSelection_;
    bool	editing_;
    gdl::Text	*text_;
  };
}

#endif /* !__CUSTOMGAME_HH__*/

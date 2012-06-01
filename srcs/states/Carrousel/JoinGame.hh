//
// JoinGame.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 15:57:15 2012 lois burg
// Last update Fri Jun  1 12:33:59 2012 lois burg
//

#ifndef		__JOINGAME_HH__
# define	__JOINGAME_HH__

# include	<map>
# include	<GDL/Text.hpp>
# include	"AContent.hh"
# include	"Keyboard.hh"

namespace	Bomberman
{
  class	JoinGame : public AContent
  {
  private:
    typedef void (JoinGame::*t_paramFunc)(StatesManager *);
    static const int	NbParams = 1;

  public:
    JoinGame();
    virtual ~JoinGame();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    void		drawArrow(void) const;

  private:
    void		upArrow(StatesManager *sMg);
    void		downArrow(StatesManager *sMg);
    void		returnArrow(StatesManager *sMg);

  private:
    std::map<gdl::Keys::Key, t_paramFunc> paramMap_;
    bool	returnHit_;
    bool        upHit_;
    bool        downHit_;
    int		currentSelection_;
    bool	editing_;
    Keyboard	editText_;
  };
}

#endif /* !__JOINGAME_HH__*/

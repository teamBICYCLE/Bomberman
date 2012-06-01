//
// QuickGame.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 15:57:15 2012 lois burg
// Last update Fri Jun  1 17:05:44 2012 lois burg
//

#ifndef		__QUICKGAME_HH__
# define	__QUICKGAME_HH__

# include	"FadingTexture.hh"
# include	"AContent.hh"

namespace	Bomberman
{
  class	QuickGame : public AContent
  {
  public:
    QuickGame();
    virtual ~QuickGame();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    bool		returnHit_;
    FadingTexture	pressEnter_;
  };
}

#endif /* !__QUICKGAME_HH__*/

//
// AdventureGame.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 15:57:15 2012 lois burg
// Last update Fri Jun  1 17:16:32 2012 lois burg
//

#ifndef		__ADVENTUREGAME_HH__
# define	__ADVENTUREGAME_HH__

# include	"FadingTexture.hh"
# include	"AContent.hh"

namespace	Bomberman
{
  class	AdventureGame : public AContent
  {
  public:
    AdventureGame();
    virtual ~AdventureGame();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    bool		returnHit_;
    FadingTexture	pressEnter_;
  };
}

#endif /* !__ADVENTUREGAME_HH__*/

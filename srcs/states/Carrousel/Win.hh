//
// Win.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 15:57:15 2012 lois burg
// Last update Sat Jun  2 19:11:04 2012 lois burg
//

#ifndef		__WIN_HH__
# define	__WIN_HH__

# include	"flatTexture.hh"
# include	"AContent.hh"

namespace	Bomberman
{
  class	Win : public AContent
  {
  public:
    Win(int winnerId);
    virtual ~Win();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    bool		returnHit_;
    flatTexture		*playerLabel_;
    flatTexture		winLabel_;
  };
}

#endif /* !__WIN_HH__*/

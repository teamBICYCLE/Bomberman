//
// Draw.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 15:57:15 2012 lois burg
// Last update Sat Jun  2 19:11:17 2012 lois burg
//

#ifndef		__DRAW_HH__
# define	__DRAW_HH__

# include	"flatTexture.hh"
# include	"AContent.hh"

namespace	Bomberman
{
  class	Draw : public AContent
  {
  public:
    Draw();
    virtual ~Draw();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    bool		returnHit_;
    flatTexture		drawLabel_;
  };
}

#endif /* !__DRAW_HH__*/

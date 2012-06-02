//
// Loose.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 15:57:15 2012 lois burg
// Last update Sat Jun  2 17:13:07 2012 lois burg
//

#ifndef		__LOOSE_HH__
# define	__LOOSE_HH__

# include	"AContent.hh"

namespace	Bomberman
{
  class	Loose : public AContent
  {
  public:
    Loose(int looserId);
    virtual ~Loose();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    int			looserId_;
    bool		returnHit_;
  };
}

#endif /* !__LOOSE_HH__*/

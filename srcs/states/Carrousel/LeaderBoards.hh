#ifndef		__LEADERBOARDS_HH__
# define	__LEADERBOARDS_HH__

# include   <GL/gl.h>
# include   <GDL/GameClock.hpp>
# include   <GDL/Input.hpp>
# include   <GDL/Text.hpp>
# include   <list>
# include	"AContent.hh"
# include   "Score.hh"

namespace	Bomberman
{
  class	LeaderBoards : public AContent
  {
  public:
    LeaderBoards();
    virtual ~LeaderBoards();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    void            refresh(void);

  private:
    Score       *score_;
    gdl::Text   *text_;
    std::list<std::string> *list_;
    bool refresh_;
  };
}

#endif /* !__LEADERBOARDS_HH__*/

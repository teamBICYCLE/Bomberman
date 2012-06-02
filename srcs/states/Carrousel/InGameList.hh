#ifndef     INGAMELIST_HH
# define    INGAMELIST_HH

# include   <GL/gl.h>
# include   <GDL/GameClock.hpp>
# include   <GDL/Input.hpp>
# include   <GDL/Text.hpp>
# include   <map>
# include	"AContent.hh"
# include   "SaveHandler.hh"

namespace	Bomberman
{
  class	InGameList : public AContent
  {
  public:
    InGameList(std::list<AObject*> &, GLvoid *data);
    virtual ~InGameList();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    void    down(StatesManager *);
    void    up(StatesManager *);
    void    action(StatesManager *);
    void    resume(StatesManager *);
    void    restart(StatesManager *);
    void    save(StatesManager *);
    void    quit(StatesManager *);

  private:
    SaveHandler *save_;
    std::list<AObject*> objs_;
    GLvoid  *screen_;
    std::map<gdl::Keys::Key, void(InGameList::*)(StatesManager *)> paramMap_;
    std::map<int, void(InGameList::*)(StatesManager *)> actionMap_;
    bool up_;
    bool down_;
    bool return_;
    int current_;
  };
}

#endif // INGAMELIST_HH

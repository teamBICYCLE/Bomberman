#ifndef     PREMADEMAP_HH
# define    PREMADEMAP_HH

# include <GL/gl.h>
# include <GDL/GameClock.hpp>
# include <GDL/Input.hpp>
# include <GDL/Text.hpp>
# include <vector>
# include "AContent.hh"
# include "flatTexture.hh"
# include "ModelHandler.hh"
# include   "CarrouselHandler.hh"

#define MAP_PATH    "Ressources/Map/"
#define PREMADE_PATH "Ressources/Screenshots/premade/"

using namespace Bomberman;

namespace	Bomberman
{
  class	PremadeMap : public AContent
  {
  public:
    PremadeMap();
    virtual ~PremadeMap();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    void drawReflect(void) const;
    void drawMapName(void) const;
    void drawArrow(void) const;
    void drawScreen(void) const;
    void refresh(void);
    void down(StatesManager *sMg);
    void up(StatesManager *sMg);
    void enter(StatesManager *sMg);

  private:
    gdl::Text		*text_;
    std::vector<std::string> maps_;
    std::map<gdl::Keys::Key, void(PremadeMap::*)(StatesManager *)> paramMap_;
    bool switch_;
    bool down_;
    bool up_;
    bool enter_;
    int current_;
  };
}

#endif // PREMADEMAP_HH

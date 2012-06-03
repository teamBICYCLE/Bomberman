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
    void refresh(void);

  private:
    gdl::Text		*text_;
    std::vector<std::string> maps_;
  };
}

#endif // PREMADEMAP_HH

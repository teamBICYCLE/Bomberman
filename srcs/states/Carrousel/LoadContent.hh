#ifndef     LOADCONTENT_HH
# define    LOADCONTENT_HH

# include <GL/gl.h>
# include <GDL/GameClock.hpp>
# include <GDL/Input.hpp>
# include <GDL/Text.hpp>
# include <list>
# include <map>
# include "StatesManager.hh"
# include "AContent.hh"
# include "SaveHandler.hh"
# include "flatTexture.hh"
# include "ModelHandler.hh"

class LoadContent : public AContent
{

public:
    LoadContent();
    virtual ~LoadContent();

public:
    virtual void update(gdl::Input & input, gdl::GameClock & gClock, StatesManager * sMg, CarrouselHandler * cH);
    virtual void draw(void);

private:
    void drawArrow(void) const;
    void refresh(StatesManager *sMg);
    void down(StatesManager *sMg);
    void up(StatesManager *sMg);
    void load(StatesManager *sMg);

private:
    SaveHandler *save_;
    gdl::Text   *text_;
    std::list< std::pair<std::string, std::string> > list_;
    uint        current_;
    std::map<gdl::Keys::Key, void(LoadContent::*)(StatesManager *)> paramMap_;
};

#endif // LOADCONTENT_HH

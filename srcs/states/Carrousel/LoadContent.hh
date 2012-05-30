#ifndef     LOADCONTENT_HH
# define    LOADCONTENT_HH

# include <GL/gl.h>
# include <GDL/GameClock.hpp>
# include <GDL/Input.hpp>
# include <GDL/Text.hpp>
# include <list>
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
    virtual void update(gdl::Input & input, gdl::GameClock & gClock, StatesManager * sMg);
    virtual void draw(void);

private:
    void refresh(void);
    void drawArrow(void) const;
    void down(void);
    void up(void);
    void load(StatesManager *sMg) const;

private:
    SaveHandler *save_;
    gdl::Text   *text_;
    bool        refresh_;
    bool        up_;
    bool        down_;
    bool        return_;
    std::list< std::pair<std::string, std::string> > list_;
    uint        current_;
};

#endif // LOADCONTENT_HH

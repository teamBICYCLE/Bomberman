#include <dirent.h>
#include <sys/types.h>
#include "PremadeMap.hh"

#include <iostream>

PremadeMap::PremadeMap()
: AContent(), text_(new gdl::Text())
{
    text_->setFont("Ressources/Fonts/Dimbo.ttf");
    PremadeMap::refresh();
    std::cout << maps_.size() << std::endl;
}

PremadeMap::~PremadeMap()
{
}

void PremadeMap::refresh(void)
{
    unsigned char isFile = 0x8;
    DIR *pdir;
    struct dirent *entry;

    maps_.clear();
    if ((pdir = opendir(MAP_PATH)))
      {
        while((entry = readdir(pdir)))
          {
            std::string name(entry->d_name);
            if (entry->d_type == isFile)
                maps_.push_back(name);
          }
      }
}

void PremadeMap::update(gdl::Input &input, gdl::GameClock &gClock, StatesManager *sMg,
                         CarrouselHandler * cH)
{
    (void)gClock;
    (void)sMg;
    (void)cH;
    (void)input;
}

void PremadeMap::draw(void)
{
    glPushMatrix();
    PremadeMap::drawReflect();
    glPopMatrix();
}

void PremadeMap::drawReflect(void) const
{
    flatTexture reflect(Bomberman::ModelHandler::get().getModel("loadmap_reflect"));
    glTranslated(515, 203, 0);
    reflect.draw();
}

#include <dirent.h>
#include <sys/types.h>
#include <fstream>
#include "Map.hh"
#include "PlayState.hh"
#include "PremadeMap.hh"

#include <iostream>

PremadeMap::PremadeMap()
: AContent(), text_(new gdl::Text())
{
    text_->setFont("Ressources/Fonts/Dimbo.ttf");
    text_->setSize(45);
    PremadeMap::refresh();

    paramMap_.insert(std::make_pair(gdl::Keys::Up, &PremadeMap::up));
    paramMap_.insert(std::make_pair(gdl::Keys::Down, &PremadeMap::down));
    paramMap_.insert(std::make_pair(gdl::Keys::Return, &PremadeMap::enter));
    down_ = false;
    up_ = false;
    enter_ = false;
    current_ = 0;
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
            if (entry->d_type == isFile && name.find("adventure") == std::string::npos)
                maps_.push_back(name);
          }
      }
}

void PremadeMap::update(gdl::Input &input, gdl::GameClock &gClock, StatesManager *sMg,
                         CarrouselHandler * cH)
{
    (void)gClock;
    (void)cH;

    for (std::map<gdl::Keys::Key, void(PremadeMap::*)(StatesManager *)>::iterator it = paramMap_.begin(); it != paramMap_.end(); ++it)
    if (input.isKeyDown(it->first))
        (this->*(it->second))(sMg);

    up_ = input.isKeyDown(gdl::Keys::Up);
    down_ = input.isKeyDown(gdl::Keys::Down);
    enter_ = input.isKeyDown(gdl::Keys::Return);
}

void PremadeMap::draw(void)
{
    PremadeMap::drawScreen();
    PremadeMap::drawReflect();
    PremadeMap::drawArrow();
    PremadeMap::drawMapName();
}

void PremadeMap::down(StatesManager *sMg)
{
    (void)sMg;
    if (!down_)
        current_ = ((current_ < (int)maps_.size() - 1) ? (current_ + 1) : (current_));
}

void PremadeMap::up(StatesManager *sMg)
{
    (void)sMg;
    if (!up_)
        current_ = ((current_ > 0) ? (current_ - 1) : (0));
}

void PremadeMap::enter(StatesManager *sMg)
{
    if (!enter_)
    {
        try {
          Character::CharacterId = 0;
          std::string name(MAP_PATH);

          name.append(maps_[current_]);
          Map	map(name);

          sMg->pushState(new PlayState(&map.getTerrain()), false);
        } catch (Map::Failure& e) {
          std::cerr << e.what() << std::endl;
        }
    };
}

void PremadeMap::drawScreen(void) const
{
    flatTexture     *screen;
    std::string     file;

    file.append(PREMADE_PATH);
    file.append(maps_[current_]);
    file.append(".png");

    std::ifstream   ifile(file);

    if (ifile)
        screen =  new flatTexture(file);
    else
        screen =  new flatTexture(Bomberman::ModelHandler::get().getModel("loadmap_na"));

    glPushMatrix();
    glTranslated(515, 203, 0);
    screen->draw();
    delete screen;
    glPopMatrix();
}

void PremadeMap::drawReflect(void) const
{
    glPushMatrix();
    flatTexture reflect(Bomberman::ModelHandler::get().getModel("loadmap_reflect"));
    glTranslated(515, 203, 0);
    reflect.draw();
    glPopMatrix();
}

void PremadeMap::drawMapName(void) const
{
    glPushMatrix();
    text_->setText(maps_[current_]);
    text_->setPosition(750, 275);
    text_->draw();
    glPopMatrix();
}

void PremadeMap::drawArrow(void) const
{
    glPushMatrix();
    flatTexture arrow(Bomberman::ModelHandler::get().getModel("double_arrow"));
    glTranslated(680, 562, 0);
    arrow.draw();
    glPopMatrix();
}

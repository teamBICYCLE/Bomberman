#include "InGameList.hh"
#include "flatTexture.hh"
#include "ModelHandler.hh"

using namespace	Bomberman;

InGameList::InGameList(std::list<AObject*> &objs, GLvoid *data, PlayState *ps)
    : AContent(), save_(new SaveHandler()), objs_(objs), screen_(data), ps_(ps)
{
    paramMap_.insert(std::make_pair(gdl::Keys::Up, &InGameList::up));
    paramMap_.insert(std::make_pair(gdl::Keys::Down, &InGameList::down));
    paramMap_.insert(std::make_pair(gdl::Keys::Return, &InGameList::action));

    actionMap_.insert(std::make_pair(0, &InGameList::resume));
    actionMap_.insert(std::make_pair(1, &InGameList::save));
    actionMap_.insert(std::make_pair(2, &InGameList::quit));

    up_ = false;
    down_ = false;
    return_ = false;
    current_ = 0;
}

InGameList::~InGameList()
{
}

void	InGameList::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH)
{
    (void)gClock;
    (void)cH;
    for (std::map<gdl::Keys::Key, void(InGameList::*)(StatesManager *)>::iterator it = paramMap_.begin(); it != paramMap_.end(); ++it)
      if (input.isKeyDown(it->first))
        (this->*(it->second))(sMg);
    up_ = input.isKeyDown(gdl::Keys::Up);
    down_ = input.isKeyDown(gdl::Keys::Down);
    return_ = input.isKeyDown(gdl::Keys::Return);
}

void	InGameList::draw(void)
{
    int y = 500;
    int yImg = 525;

    flatTexture overlay(Bomberman::ModelHandler::get().getModel("resume-exit_window"));
    flatTexture resume(Bomberman::ModelHandler::get().getModel("resume"));
    flatTexture save(Bomberman::ModelHandler::get().getModel("save"));
    flatTexture exit(Bomberman::ModelHandler::get().getModel("exit"));

    glPushMatrix();
    glTranslated(620, y - (125 * current_), 0);
    overlay.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(687, yImg, 0);
    resume.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(713, yImg - 125, 0);
    save.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(715, yImg - 250, 0);
    exit.draw();
    glPopMatrix();
}

void    InGameList::up(StatesManager *sMg)
{
    (void)sMg;
    if (!up_)
        current_ = ((current_ == 0) ? (2) : (current_ - 1));
}

void    InGameList::down(StatesManager *sMg)
{
    (void)sMg;
    if (!down_)
        current_ = ((current_ == 2) ? (0) : (current_ + 1));
}

void    InGameList::action(StatesManager *sMg)
{
    (void)sMg;
    if (!return_)
    {
        if (current_ >= 0 && current_ <= 2)
            (this->*(actionMap_[current_]))(sMg);
    }
}

void    InGameList::resume(StatesManager *sMg)
{
    sMg->popState();
}

void    InGameList::save(StatesManager *sMg)
{
    (void)sMg;
    save_->save(objs_, screen_);
}

void    InGameList::quit(StatesManager *sMg)
{
    sMg->popState();
    sMg->popState();
}

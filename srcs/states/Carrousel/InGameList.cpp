#include "InGameList.hh"
#include "flatTexture.hh"
#include "ModelHandler.hh"

using namespace	Bomberman;

InGameList::InGameList()
    : AContent(), save_(new SaveHandler())
{
    paramMap_.insert(std::make_pair(gdl::Keys::Up, &InGameList::up));
    paramMap_.insert(std::make_pair(gdl::Keys::Down, &InGameList::down));
    paramMap_.insert(std::make_pair(gdl::Keys::Return, &InGameList::action));

    actionMap_.insert(std::make_pair(0, &InGameList::resume));
    actionMap_.insert(std::make_pair(1, &InGameList::restart));
    actionMap_.insert(std::make_pair(2, &InGameList::save));
    actionMap_.insert(std::make_pair(3, &InGameList::quit));

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
    int y = 600;
    glPushMatrix();
    flatTexture overlay(Bomberman::ModelHandler::get().getModel("dot"));
    glTranslated(940, y - (125 * current_), 0);
    overlay.draw();
    glPopMatrix();
}

void    InGameList::up(StatesManager *sMg)
{
    (void)sMg;
    if (!up_)
        current_ = ((current_ == 0) ? (3) : (current_ - 1));
}

void    InGameList::down(StatesManager *sMg)
{
    (void)sMg;
    if (!down_)
        current_ = ((current_ == 3) ? (0) : (current_ + 1));
}

void    InGameList::action(StatesManager *sMg)
{
    (void)sMg;
    if (!return_)
    {
        if (current_ >= 0 && current_ <= 3)
            (this->*(actionMap_[current_]))(sMg);
    }
}

void    InGameList::resume(StatesManager *sMg)
{
    sMg->popState();
}

void    InGameList::restart(StatesManager *sMg)
{
    (void)sMg;
    // pas trop d'idee ...
    // Peut etre recuperer les infos du playstate
    // pop les States et refaire un new PlayState avec les infos
}

void    InGameList::save(StatesManager *sMg)
{
    (void)sMg;
    //save_->save(/*il faut recuperer la liste d'obj*/);
}

void    InGameList::quit(StatesManager *sMg)
{
    sMg->popState();
    sMg->popState();
}

#include "LoadContent.hh"
#include "SaveHandler.hh"
#include "PlayState.hh"

#include <iostream>

LoadContent::LoadContent()
    : AContent(), save_(new SaveHandler()), text_(new gdl::Text())
{
  text_->setFont("Ressources/Fonts/Dimbo.ttf");
  refresh_ = false;
  up_ = false;
  down_ = false;
  return_ = false;
  current_ = -1;
  LoadContent::refresh();
}

LoadContent::~LoadContent()
{
}

void LoadContent::refresh(void)
{
    list_ = save_->getSavedFiles();
}

void LoadContent::down(void)
{
    if (list_.size() == 0)
        current_ = -1;
    else if (current_ == (list_.size() - 1) || current_ == 2)
        current_ = 0;
    else
        current_ += 1;
}

void LoadContent::up(void)
{
    if (list_.size() == 0)
        current_ = -1;
    else if (current_ > 0)
        current_ -= 1;
    else
        current_ = (((list_.size() - 1) <= 2) ? (list_.size() - 1) : (2));
}

void LoadContent::load(StatesManager *sMg) const
{
    std::list< std::pair<std::string, std::string> >::const_iterator it;
    const std::list<AObject*> *obj;
    std::list<AObject*>::const_iterator it2;
    uint i = 0;

    if (current_ != static_cast<uint>(-1))
        for (it = list_.begin(); it != list_.end(); it++)
        {
            if (i == current_)
            {
                obj = save_->load(it->second);
                sMg->pushState(new PlayState(obj), false);
                break;
            }
            i++;
        }
}

void LoadContent::update(gdl::Input &input, gdl::GameClock &gClock, StatesManager *sMg,
                         CarrouselHandler * cH)
{
    (void)gClock;
    (void)sMg;
    (void)cH;
    if (input.isKeyDown(gdl::Keys::F5) && !refresh_)
        refresh();
    if (input.isKeyDown(gdl::Keys::Up) && !up_)
        LoadContent::up();
    if (input.isKeyDown(gdl::Keys::Down) && !down_)
        LoadContent::down();
    if (input.isKeyDown(gdl::Keys::Return) && !return_)
        LoadContent::load(sMg);

    refresh_ = input.isKeyDown(gdl::Keys::F5);
    up_ = input.isKeyDown(gdl::Keys::Up);
    down_ = input.isKeyDown(gdl::Keys::Down);
    return_ = input.isKeyDown(gdl::Keys::Return);

    if (list_.size() > 0 && current_ == static_cast<uint>(-1))
        current_ = 0;
}

void LoadContent::drawArrow(void) const
{
    if (current_ != static_cast<uint>(-1))
    {
        flatTexture     arrow(Bomberman::ModelHandler::get().getModel("overlay-load"));
        int align = current_ * 187;

        glPushMatrix();
        glTranslated(400, (540 - align), 0);
        arrow.draw();
        glPopMatrix();
    }
}

void LoadContent::draw(void)
{
    glPushMatrix();
    int align = 800;
    int alignImg = 553;
    int yImg = 272;
    int y = 310;
    int i = 0;
    std::list< std::pair<std::string, std::string> >::iterator it;

    LoadContent::drawArrow();
    for (it = list_.begin(); i < 3 && it != list_.end(); it++)
    {
        flatTexture     screen(save_->getScreenshot(it->second));
        text_->setText(it->first);
        text_->setPosition(align, y);
        text_->draw();

        glTranslated(alignImg, yImg, 0);
        screen.draw();

        y += 183;
        yImg += 182;
        i++;
    }
    for (; i < 3; i++)
    {
        text_->setText("Empty");
        text_->setPosition(align, y);
        text_->draw();
        y += 183;
    }
    glPopMatrix();
}

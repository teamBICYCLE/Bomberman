#include "KeyBindSlide.hh"
#include "flatTexture.hh"
#include "ModelHandler.hh"

using namespace	Bomberman;

KeyBindSlide::KeyBindSlide()
    : AContent(), text_(new gdl::Text()), keyboard_(new Keyboard(500, 500))
{
    current_ = 0;
    player_ = 0;
    up_ = false;
    down_ = false;
    tab_ = false;
    return_ = false;
    editingMode_ = false;
    text_->setFont("Ressources/Fonts/Dimbo.ttf");
    paramMap_.insert(std::make_pair(gdl::Keys::Up, &KeyBindSlide::up));
    paramMap_.insert(std::make_pair(gdl::Keys::Down, &KeyBindSlide::down));
    paramMap_.insert(std::make_pair(gdl::Keys::Tab, &KeyBindSlide::tab));
    paramMap_.insert(std::make_pair(gdl::Keys::Return, &KeyBindSlide::setEditingMode));
}

KeyBindSlide::~KeyBindSlide()
{
}

#include <iostream>

void	KeyBindSlide::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH)
{
    (void)gClock;
    (void)sMg;
    (void)cH;
    for (std::map<gdl::Keys::Key, void(KeyBindSlide::*)(void)>::iterator it = paramMap_.begin(); it != paramMap_.end(); ++it)
      if (input.isKeyDown(it->first))
        (this->*(it->second))();

    keyboard_->update(input);
    up_ = input.isKeyDown(gdl::Keys::Up);
    down_ = input.isKeyDown(gdl::Keys::Down);
    tab_ = input.isKeyDown(gdl::Keys::Tab);
    return_ = input.isKeyDown(gdl::Keys::Return);

    std::cout << keyboard_->getData() << std::endl;
    //cH->setArrowFocus(editingMode_);
}

void	KeyBindSlide::draw(void)
{
     KeyBindSlide::drawOverlay();
}

void    KeyBindSlide::drawOverlay(void) const
{
    flatTexture     overlay(Bomberman::ModelHandler::get().getModel("keybind-overlay"));
    int align = current_ * 50;
    int alignP = player_ * 453;

    glPushMatrix();
    glTranslated(607 + alignP, 503 - align, 0);
    overlay.draw();
    glPopMatrix();
    keyboard_->draw();
}

void    KeyBindSlide::down(void)
{
    if (!down_)
        current_ = ((current_ == 5) ? (0) : (current_ + 1));
}

void    KeyBindSlide::up(void)
{
    if (!up_)
        current_ = ((current_ != 0) ? (current_ - 1) : (5));
}

void    KeyBindSlide::tab(void)
{
    if (!tab_)
        player_ = ((player_ == 0) ? (1) : (0));
}

void    KeyBindSlide::setEditingMode(void)
{
    editingMode_ = !editingMode_;
}

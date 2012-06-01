#include "KeyBindSlide.hh"
#include "flatTexture.hh"
#include "ModelHandler.hh"

using namespace	Bomberman;

KeyBindSlide::KeyBindSlide()
    : AContent(), text_(new gdl::Text())
{
    current_ = 0;
    player_ = 0;
    up_ = false;
    down_ = false;
    tab_ = false;
    return_ = false;
    left_ = false;
    right_ = false;
    editingMode_ = false;
    text_->setFont("Ressources/Fonts/Dimbo.ttf");
    paramMap_.insert(std::make_pair(gdl::Keys::Up, &KeyBindSlide::up));
    paramMap_.insert(std::make_pair(gdl::Keys::Down, &KeyBindSlide::down));
    paramMap_.insert(std::make_pair(gdl::Keys::Tab, &KeyBindSlide::tab));
    paramMap_.insert(std::make_pair(gdl::Keys::Return, &KeyBindSlide::setEditingMode));

    KeysConfig *config_ = new KeysConfig();

    player1_.insert(std::make_pair(K_UP, config_->getStr(K_UP, 0)));
    player1_.insert(std::make_pair(K_RIGHT, config_->getStr(K_RIGHT, 0)));
    player1_.insert(std::make_pair(K_DOWN, config_->getStr(K_DOWN, 0)));
    player1_.insert(std::make_pair(K_LEFT, config_->getStr(K_LEFT, 0)));
    player1_.insert(std::make_pair(K_PUT_BOMB, config_->getStr(K_PUT_BOMB, 0)));
    player1_.insert(std::make_pair(K_PUT_MINE, config_->getStr(K_PUT_MINE, 0)));

    player2_.insert(std::make_pair(K_UP, config_->getStr(K_UP, 1)));
    player2_.insert(std::make_pair(K_RIGHT, config_->getStr(K_RIGHT, 1)));
    player2_.insert(std::make_pair(K_DOWN, config_->getStr(K_DOWN, 1)));
    player2_.insert(std::make_pair(K_LEFT, config_->getStr(K_LEFT, 1)));
    player2_.insert(std::make_pair(K_PUT_BOMB, config_->getStr(K_PUT_BOMB, 1)));
    player2_.insert(std::make_pair(K_PUT_MINE, config_->getStr(K_PUT_MINE, 1)));
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

    up_ = input.isKeyDown(gdl::Keys::Up);
    down_ = input.isKeyDown(gdl::Keys::Down);
    tab_ = input.isKeyDown(gdl::Keys::Tab);
    return_ = input.isKeyDown(gdl::Keys::Return);
}

void	KeyBindSlide::draw(void)
{
     KeyBindSlide::drawOverlay();
}

void    KeyBindSlide::drawOverlay(void) const
{   
    flatTexture overlay(Bomberman::ModelHandler::get().getModel("keybind_overlay_green"));

    int align = current_ * 50;
    int alignP = player_ * 453;

    glPushMatrix();
    glTranslated(608 + alignP, 504 - align, 0);
    overlay.draw();
    glPopMatrix();
}

void    KeyBindSlide::right(void)
{
    if (!right_)
        player_ = 1;
}

void    KeyBindSlide::left(void)
{
    if (!left_)
        player_ = 0;
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

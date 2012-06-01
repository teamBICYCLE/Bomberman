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
    editingMode_ = false;
    letbool_ = false;
    text_->setFont("Ressources/Fonts/Dimbo.ttf");
    paramMap_.insert(std::make_pair(gdl::Keys::Up, &KeyBindSlide::up));
    paramMap_.insert(std::make_pair(gdl::Keys::Down, &KeyBindSlide::down));
    paramMap_.insert(std::make_pair(gdl::Keys::Tab, &KeyBindSlide::tab));

    KeysConfig *config_ = new KeysConfig();

    player1_.insert(std::make_pair(0, K_LEFT, config_->getStr(K_LEFT, 0)));
    player1_.insert(std::make_pair(1, K_UP, config_->getStr(K_UP, 0)));
    player1_.insert(std::make_pair(2, K_RIGHT, config_->getStr(K_RIGHT, 0)));
    player1_.insert(std::make_pair(3, K_DOWN, config_->getStr(K_DOWN, 0)));
    player1_.insert(std::make_pair(4, K_PUT_BOMB, config_->getStr(K_PUT_BOMB, 0)));
    player1_.insert(std::make_pair(5, K_PUT_MINE, config_->getStr(K_PUT_MINE, 0)));

    player2_.insert(std::make_pair(K_LEFT, config_->getStr(K_LEFT, 1)));
    player2_.insert(std::make_pair(K_UP, config_->getStr(K_UP, 1)));
    player2_.insert(std::make_pair(K_RIGHT, config_->getStr(K_RIGHT, 1)));
    player2_.insert(std::make_pair(K_DOWN, config_->getStr(K_DOWN, 1)));
    player2_.insert(std::make_pair(K_PUT_BOMB, config_->getStr(K_PUT_BOMB, 1)));
    player2_.insert(std::make_pair(K_PUT_MINE, config_->getStr(K_PUT_MINE, 1)));
    ref_ = config_->getRef();
}

KeyBindSlide::~KeyBindSlide()
{
}

#include <iostream>

void	KeyBindSlide::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH)
{
    (void)gClock;
    (void)sMg;
    bool let;

    if (!editingMode_)
    {
        cH->setArrowFocus(true);
        for (std::map<gdl::Keys::Key, void(KeyBindSlide::*)(void)>::iterator it = paramMap_.begin(); it != paramMap_.end(); ++it)
        if (input.isKeyDown(it->first))
            (this->*(it->second))();

        up_ = input.isKeyDown(gdl::Keys::Up);
        down_ = input.isKeyDown(gdl::Keys::Down);
        tab_ = input.isKeyDown(gdl::Keys::Tab);
    }
    else
    {
        cH->setArrowFocus(false);
        for (std::map<const std::string, gdl::Keys::Key>::iterator it = ref_.begin(); it != ref_.end(); ++it)
            if (input.isKeyDown(it->second) && !letbool_)
                KeyBindSlide::setNewKey(it->first);
    }

    if (input.isKeyDown(gdl::Keys::Return) && !return_)
        KeyBindSlide::setEditingMode();
    return_ = input.isKeyDown(gdl::Keys::Return);

    let = input.isKeyDown((ref_.begin())->second);
    for (std::map<const std::string, gdl::Keys::Key>::iterator it = ref_.begin(); it != ref_.end(); ++it)
        if (let != true)
            let = input.isKeyDown(it->second);
    letbool_ = let;
}

void	KeyBindSlide::draw(void)
{
    if (!editingMode_)
        KeyBindSlide::drawOverlay();
     KeyBindSlide::drawKeys(0);
     KeyBindSlide::drawKeys(1);
}

void    KeyBindSlide::setNewKey(const std::string &str)
{
    std::map<eKeys, std::string> now;
    std::map<eKeys, std::string>::iterator it;
    int i = 0;

    now = ((player_ == 0) ? (player1_) : (player2_));
    for (it = now.begin(); it != now.end(); it++)
    {
        if (current_ == i)
            it->second = str;
        i++;
    }
    player1_ = ((player_ == 0) ? (now) : (player1_));
    player2_ = ((player_ == 1) ? (now) : (player2_));
    editingMode_ = false;
}

void    KeyBindSlide::drawOverlay(void) const
{   
    flatTexture *overlay;

    if (player_ == 0)
        overlay = new flatTexture(Bomberman::ModelHandler::get().getModel("keybind_overlay_green"));
    else
        overlay = new flatTexture(Bomberman::ModelHandler::get().getModel("keybind_overlay_red"));
    int align = current_ * 50;
    int alignP = player_ * 453;

    glPushMatrix();
    glTranslated(608 + alignP, 504 - align, 0);
    overlay->draw();
    glPopMatrix();
    delete overlay;
}

#include <iostream>

void    KeyBindSlide::drawKeys(int id) const
{
    std::map<eKeys, std::string> now;
    std::map<eKeys, std::string>::const_iterator it;
    int align = 620;
    int i = 0;
    int size;

    now = ((id == 0) ? (player1_) : (player2_));
    align = ((id == 1) ? (align + 455) : (align));
    for (it = now.begin(); it != now.end(); it++)
    {
        std::cout << it->second << std::endl;
        if (current_ == i && player_ == id && editingMode_);
        else
        {
            size = ((MAX_SIZE - 1 - (it->second.length())) * 5);
            //size = ((it->second.length() % 2 == 0) ? ((MAX_SIZE - (it->second.length() - 1)) * 5) : ((MAX_SIZE - (it->second.length())) * 5));
            text_->setText(it->second);
            text_->setSize(25);
            text_->setPosition(align + size, 365 + (i * 50));
            text_->draw();
        }
        i++;
    }
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

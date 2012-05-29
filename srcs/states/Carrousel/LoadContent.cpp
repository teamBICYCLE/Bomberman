#include "LoadContent.hh"
#include "SaveHandler.hh"

#include <iostream>

LoadContent::LoadContent()
    : AContent(), save_(new SaveHandler()), text_(new gdl::Text())
{
    text_->setFont("Ressources/Fonts/Dimbo.ttf");
    refresh_ = false;
    up_ = false;
    down_ = false;
    current_ = 0;
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
    if (current_ == (list_.size() - 1) || current_ == 2)
        current_ = 0;
    else
        current_ += 1;
}

void LoadContent::up(void)
{
    if (current_ > 0)
        current_ -= 1;
    else
        current_ = (((list_.size() - 1) <= 2) ? (list_.size() - 1) : (2));
}

void LoadContent::update(gdl::Input & input, gdl::GameClock & gClock, StatesManager *sMg)
{
    if (input.isKeyDown(gdl::Keys::F5) && !refresh_)
        refresh();
    if (input.isKeyDown(gdl::Keys::Up) && !up_)
        LoadContent::up();
    if (input.isKeyDown(gdl::Keys::Down) && !down_)
        LoadContent::down();

    refresh_ = input.isKeyDown(gdl::Keys::F5);
    up_ = input.isKeyDown(gdl::Keys::Up);
    down_ = input.isKeyDown(gdl::Keys::Down);
}

void LoadContent::drawArrow(void) const
{
    flatTexture     arrow(Bomberman::ModelHandler::get().getModel("overlay-load"));
    int align = current_ * 187;

    glPushMatrix();
    glTranslated(400, (540 - align), 0);
    arrow.draw();
    glPopMatrix();
}

void LoadContent::draw(void)
{
    glPushMatrix();
    int align = 700;
    int alignImg = 552;
    int yImg = 246;
    int y = 310;
    int i = 0;
    std::list< std::pair<std::string, std::string> >::iterator it;

    LoadContent::drawArrow();
    for (it = list_.begin(); i < 3 && it != list_.end(); it++)
    {
        text_->setText(it->first);
        text_->setPosition(align, y);
        text_->draw();

        // draw de l'image <- alignImg et yImg represente
        // les coordonnes de la ou il faut mettre l'image
        // merci thomas
        text_->setText(".");
        text_->setPosition(alignImg, yImg);
        text_->draw();

        y += 183;
        yImg += 183;
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
    //std::cout << "draw" << std::endl;
}

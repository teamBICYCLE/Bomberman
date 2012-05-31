//
// LeaderBoards.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Thu May 31 10:52:03 2012 lois burg
//

#include "LeaderBoards.hh"

using namespace	Bomberman;

LeaderBoards::LeaderBoards()
: AContent(), score_(new Score()), text_(new gdl::Text())
{
    text_->setFont("Ressources/Fonts/Dimbo.ttf");
    refresh_ = false;
    LeaderBoards::refresh();
}

LeaderBoards::~LeaderBoards()
{
}

void LeaderBoards::refresh(void)
{
    list_ = score_->getScores();
}

void	LeaderBoards::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH)
{
    (void)gClock;
    (void)sMg;
    (void)cH;
    if (input.isKeyDown(gdl::Keys::F5) && !refresh_)
        refresh();

    refresh_ = input.isKeyDown(gdl::Keys::F5);
}

void	LeaderBoards::draw(void)
{
    glPushMatrix();
    std::list<std::string>::iterator it;
    int i = 0;
    int align = 800;
    int y = 310;

    if (list_->size() > 0)
    {
        for (it = list_->begin(); it != list_->end() && i != 5; it++)
        {
            text_->setText(*it);
            text_->setPosition(align, y);
            text_->draw();
            y += 183;
            i++;
        }
    }
    glPopMatrix();
}

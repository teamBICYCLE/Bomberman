/**************************************************************************
** ItemList.cpp: Created on 26 May 2012 by duplom_t
** for class : ItemList
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include <algorithm>
#include "ItemList.hh"

ItemList::ItemList()
  : current_(0)
{
}

ItemList::~ItemList()
{
}

void ItemList::pushButton(AButton *button)
{
  items_.push_back(button);
}

void ItemList::update(gdl::Input &keys,
                      gdl::GameClock &gClock,
                      StatesManager *sMg,
                      CarrouselHandler * cH)
{
  (void)gClock;
  (void)cH;
  if (keys.isKeyDown(gdl::Keys::Up) && upPressed_)
  {
    if (current_ - 1 > current_)
      current_ = items_.size() - 1;
    else
      --current_;
  }
  if (keys.isKeyDown(gdl::Keys::Down) && downPressed_)
  {
    ++current_;
    if (current_ >= items_.size())
      current_ = 0;
  }
  if (keys.isKeyDown(gdl::Keys::Return))
  {
    items_[current_]->activate(sMg);
  }
  upPressed_ = !keys.isKeyDown(gdl::Keys::Up);
  downPressed_ = !keys.isKeyDown(gdl::Keys::Down);
}

void ItemList::draw()
{
  int i = 0;

  std::for_each(items_.begin(), items_.end(), [&](AButton * obj) -> void {
     if (i == static_cast<int>(current_))
      obj->drawHighlight();
     else
      obj->draw();
    ++i;
  });
}

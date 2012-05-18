/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return duplom_t
 * ----------------------------------------------------------------------------
 */

#include <algorithm>
#include "MenuEntry.hh"
#include "AGameState.hh"

namespace Bomberman {
MenuEntry::MenuEntry() : selected_(0) {
  items_.push_back(MenuLine("start"));
  items_.push_back(MenuLine("stop", 300.0f));
}

MenuEntry::~MenuEntry() {
}

void    MenuEntry::update(gdl::GameClock& clock, gdl::Input& keys, StatesManager * sMg)
{
  static bool  noUp = true, noDown = true;

  if (keys.isKeyDown(gdl::Keys::Up) && noUp)
  {
    if (selected_ - 1 > selected_)
      selected_ = items_.size() - 1;
    else
      --selected_;
  }
  if (keys.isKeyDown(gdl::Keys::Down) && noDown)
  {
    ++selected_;
    if (selected_ >= items_.size())
      selected_ = 0;
  }
  if (keys.isKeyDown(gdl::Keys::Return))
  {
    items_[selected_].activate(sMg);
  }

  // prevent keys to be consider pressed twice (force user to re-press)
  noUp = !keys.isKeyDown(gdl::Keys::Up);
  noDown = !keys.isKeyDown(gdl::Keys::Down);

  unsigned int i = 0;
  std::for_each(items_.begin(), items_.end(), [&i, &clock, this](MenuLine & obj) -> void {
    obj.update(clock, i == selected_);
    ++i;
  });
}

void    MenuEntry::draw()
{
  std::for_each(items_.begin(), items_.end(), [](MenuLine & obj) -> void {
    obj.draw();
  });
}

}

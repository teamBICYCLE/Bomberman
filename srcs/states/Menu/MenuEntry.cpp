/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return duplom_t
 * ----------------------------------------------------------------------------
 */

#include "MenuEntry.hh"

#include <algorithm>
#include "AGameState.hh"
#include "StartGame.hh"
#include "QuickStart.hh"
#include "Quit.hh"

namespace Menu {
MenuEntry::MenuEntry() : selected_(0) {
  items_.push_back(new StartGame("Ressources/Images/Menu/start.png",
                                 "Ressources/Images/Menu/start_h.png"));
  items_.push_back(new QuickStart("Ressources/Images/Menu/bomb.png",
                                 "Ressources/Images/Menu/bomb_h.png",
                                 Vector3d(0.0f, 250.0f, 0.0f)));
  items_.push_back(new Quit("Ressources/Images/Menu/stop.png",
                            "Ressources/Images/Menu/stop_h.png",
                            Vector3d(0.0f, 500.0f, 0)));
}

MenuEntry::~MenuEntry() {
}

void    MenuEntry::update(gdl::GameClock& clock, gdl::Input& keys,
                          StatesManager * sMg)
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
    items_[selected_]->activate(sMg);
  }

  // prevent keys to be consider pressed twice (force user to re-press)
  noUp = !keys.isKeyDown(gdl::Keys::Up);
  noDown = !keys.isKeyDown(gdl::Keys::Down);

  unsigned int i = 0;
  std::for_each(items_.begin(), items_.end(), [&i, &clock, this](MenuLine * obj) -> void {
    obj->update(clock, i == selected_);
    ++i;
  });
}

void    MenuEntry::draw()
{
  std::for_each(items_.begin(), items_.end(), [](MenuLine * obj) -> void {
    obj->draw();
  });
}

}

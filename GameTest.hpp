/**************************************************************************
** GameTest.hpp: Created on 21 Apr 2012 by duplom_t
** for class : GameTest
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef GAMETEST_HPP
#define GAMETEST_HPP

#include <list>
#include <GDL/Game.hpp>
#include "AObject.hpp"

class GameTest : public gdl::Game
{
public:
  void    initialize(void);
  void    update(void);
  void    draw(void);
  void    unload(void);

private:

  // Camera              camera_; @TODO
  std::list<AObject *> objects_;
};

#endif // GAMETEST_HPP

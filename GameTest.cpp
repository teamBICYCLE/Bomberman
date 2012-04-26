/**************************************************************************
** GameTest.cpp: Created on 21 Apr 2012 by duplom_t
** for class : GameTest
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "GameTest.hpp"
#include <iostream>

void    GameTest::initialize(void)
{
  window_.create();

//  for(std::list<AObject>)
}

void    GameTest::update(void)
{
  std::cout << "update" << std::endl;
}

void    GameTest::draw(void)
{
  std::cout << "draw" << std::endl;
}

void    GameTest::unload(void)
{
  std::cout << "unload" << std::endl;
}

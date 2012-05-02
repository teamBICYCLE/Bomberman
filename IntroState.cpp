/**************************************************************************
** IntroState.cpp: Created on 2 May 2012 by duplom_t
** for class : IntroState
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "IntroState.hh"
#include <iostream>

void  IntroState::init()
{

}

void  IntroState::cleanUp()
{
  std::cout << "clean up Intro" << std::endl;
}

void  IntroState::update(StatesManager * sMg)
{
  std::cout << "update Intro" << std::endl;
}

void  IntroState::draw(StatesManager * sMg)
{
  std::cout << "draw Intro" << std::endl;
}

void  IntroState::pause()
{
  std::cout << "pause Intro" << std::endl;
}

void  IntroState::resume()
{
  std::cout << "resume Intro" << std::endl;
}

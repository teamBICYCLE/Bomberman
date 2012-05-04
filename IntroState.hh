/**************************************************************************
** IntroState.hh: Created on 2 May 2012 by duplom_t
** for class : IntroState
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef INTROSTATE_HH
#define INTROSTATE_HH

#include "AGameState.hh"

class IntroState : public AGameState
{
public:
  virtual void init(gdl::GameClock *clock, gdl::Input *input);
  virtual void cleanUp();

  virtual void update(StatesManager *);
  virtual void draw(StatesManager *);
  virtual void pause();
  virtual void resume();
};

#endif // INTROSTATE_HH

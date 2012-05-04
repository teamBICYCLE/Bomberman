/**************************************************************************
** AGameState.hh: Created on 2 May 2012 by duplom_t
** for class :
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef		_AGAMESTATE_HH
# define	_AGAMESTATE_HH

# include	<cstdlib>
# include	<GDL/Input.hpp>
# include	<GDL/GameClock.hpp>

class StatesManager;

class AGameState
{
public:
  virtual void init(gdl::GameClock *clock, gdl::Input *input) = 0;
  virtual void cleanUp() = 0;

  virtual void update(StatesManager *) = 0;
  virtual void draw(StatesManager *) = 0;
  virtual void pause() = 0;
  virtual void resume() = 0;

  void    changeState(StatesManager *, AGameState *);

protected:
  AGameState() {}
};

#include "StatesManager.hh"

#endif // AGAMESTATE_HH

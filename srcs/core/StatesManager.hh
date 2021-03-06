/**************************************************************************
** StatesManager.hh: Created on 2 May 2012 by duplom_t
** for class : StatesManager
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef STATESMANAGER_HH
#define STATESMANAGER_HH

#include <GDL/Game.hpp>
#include <vector>
#include <exception>
#include "AGameState.hh"

class StatesManager : public gdl::Game
{
private:
  class Exception : public std::exception
  {
  public:
    Exception(const std::string &);
    Exception(const Exception &);
    virtual ~Exception() throw() {}
    const char *        what() const throw();

  private:
    std::string   what_;
  };

public:
  StatesManager(const std::string &);
  virtual ~StatesManager();

  virtual void      initialize();
  virtual void      unload();

  void      changeState(AGameState *);
  bool      pushState(AGameState *, bool init = true);
  void      popState(void);
  void      clearStates(void);

  virtual void      update();
  virtual void      draw();
  void              start(AGameState * state);
  void              quit();

  gdl::Input        &getInput(void);
  gdl::GameClock    &getGameClock(void);

private:
  double		     elapseTime_;
  std::vector<AGameState *>  states_;
};

#endif // STATESMANAGER_HH

/**************************************************************************
** StatesManager.cpp: Created on 2 May 2012 by duplom_t
** for class : StatesManager
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "StatesManager.hh"

StatesManager::Exception::Exception(const std::string & what)
  : what_(what) {}

StatesManager::Exception::Exception(const Exception & other)
  : what_(other.what_) {}

const char *  StatesManager::Exception::what() const throw()
{
  return ("State Manager: " + this->what_).c_str();
}

StatesManager::StatesManager(const std::string & winTitle, AGameState * state)
  : gdl::Game()
{
  this->initialize(winTitle);
  this->changeState(state);
}

StatesManager::~StatesManager()
{
  this->clearStates();
}

void      StatesManager::initialize()
{
  this->window_.create();
}

void      StatesManager::initialize(const std::string & winTitle)
{
  this->window_.setTitle(winTitle);
  this->initialize();
}

void      StatesManager::unload()
{
  this->clearStates();
}

void      StatesManager::changeState(AGameState * state)
{
  this->clearStates();
  this->pushState(state);
}

void      StatesManager::pushState(AGameState * state)
{
  if (!this->states_.empty())
    this->states_.back()->pause();
  this->states_.push_back(state);
  this->states_.back()->init();
}

void      StatesManager::popState(void)
{
  if (!this->states_.empty())
    {
      this->states_.back()->cleanUp();
      this->states_.pop_back();
    }
  if (!this->states_.empty())
    this->states_.back()->resume();
}

void      StatesManager::clearStates(void)
{
  while (!states_.empty())
    {
      this->states_.back()->cleanUp();
      this->states_.pop_back();
    }
}

void      StatesManager::update()
{
  if (!this->states_.empty())
    this->states_.back()->update(this);
  else
    throw Exception("No state to be update");
}

void      StatesManager::draw()
{
  if (!this->states_.empty())
    this->states_.back()->draw(this);
  else
    throw Exception("No state to be drawn");
}

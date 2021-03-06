/**************************************************************************
** StatesManager.cpp: Created on 2 May 2012 by duplom_t
** for class : StatesManager
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include <unistd.h>
#include "StatesManager.hh"
#include "ModelHandler.hh"
#include "TexturedCube.hh"
#include "gdlModel.hh"
#include "RotatingImg.hh"
#include "ExplosionBlock.hh"
#include "flatTexture.hh"

StatesManager::Exception::Exception(const std::string & what)
  : what_(what) {}

StatesManager::Exception::Exception(const Exception & other)
  : what_(other.what_) {}

const char *  StatesManager::Exception::what() const throw()
{
  return ("State Manager: " + this->what_).c_str();
}

StatesManager::StatesManager(const std::string & winTitle)
  : gdl::Game()
{
  this->window_.setTitle(winTitle);
  this->window_.setHeight(900);
  this->window_.setWidth(1600);
  this->window_.setFullscreen(true);
}

 StatesManager::~StatesManager()
{
  this->clearStates();
}

void      StatesManager::initialize()
{
  this->window_.create();
  gdlModel*   marvin = new gdlModel("Ressources/Assets/marvin.fbx");

  gdl::Model::cut_animation(marvin->getModel(), "Take 001", 0, 35, "start");
  gdl::Model::cut_animation(marvin->getModel(), "Take 001", 36, 54, "run");
  gdl::Model::cut_animation(marvin->getModel(), "Take 001", 60, 120, "stop");


  Bomberman::ModelHandler::get().storeModel(
        new TexturedCube("Ressources/Images/Play/block.png"),
        "block");
  Bomberman::ModelHandler::get().storeModel(
        new TexturedCube("Ressources/Images/Play/fireblock.png"),
        "fireblock");
  Bomberman::ModelHandler::get().storeModel(
        new TexturedCube("Ressources/Images/Play/brick.png"),
        "brick");

  Bomberman::ModelHandler::get().storeModel(
        new RotatingImg("Ressources/Images/Play/bomb_simple.png"),
        "bombup");
  Bomberman::ModelHandler::get().storeModel(
        new RotatingImg("Ressources/Images/Play/mine_simple.png"),
        "mineup");
  Bomberman::ModelHandler::get().storeModel(
        new RotatingImg("Ressources/Images/Play/kick_simple.png"),
        "kickup");
  Bomberman::ModelHandler::get().storeModel(
        new RotatingImg("Ressources/Images/Play/range_simple.png"),
        "rangeup");
  Bomberman::ModelHandler::get().storeModel(
        new RotatingImg("Ressources/Images/Play/speed_simple.png"),
        "speedup");

  Bomberman::ModelHandler::get().storeModel(
        new TexturedCube(""), "cube");
  Bomberman::ModelHandler::get().storeModel(
        marvin, "bombman");
  Bomberman::ModelHandler::get().storeModel(
        new gdlModel("Ressources/Assets/bomb.fbx"), "bomb");
  Bomberman::ModelHandler::get().storeModel(
        new gdlModel("Ressources/Assets/mine.fbx"), "mine");
  Bomberman::ModelHandler::get().storeModel(
        new gdlModel("Ressources/Assets/ghost.fbx"), "ghost");
  Bomberman::ModelHandler::get().storeModel(
        new gdlModel("Ressources/Assets/monster.fbx"), "monster");
  Bomberman::ModelHandler::get().storeModel(
        new ExplosionBlock("Ressources/Images/Play/explosion.png"), "explosion");
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

bool      StatesManager::pushState(AGameState * state, bool init)
{
  if (init && !state->init())
    return false;
  if (!this->states_.empty())
    this->states_.back()->pause();
  this->states_.push_back(state);
  return true;
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
    this->states_.back()->update(this, elapseTime_);
  else
    this->quit();
}

void      StatesManager::draw()
{
  int   time;

  if (!this->states_.empty())
    this->states_.back()->draw(this);
  else
    this->quit();

  elapseTime_ = gameClock_.getElapsedTime();
  time = ((1.0f/60.0f) - elapseTime_) * 1000000;
  usleep(time > 0 ? time : 0);
}

void StatesManager::start(AGameState *state)
{
  this->pushState(state);
  this->run();
}

void StatesManager::quit()
{
  this->window_.close();
}

gdl::Input  &StatesManager::getInput(void)
{
    return input_;
}

gdl::GameClock & StatesManager::getGameClock(void)
{
    return gameClock_;
}

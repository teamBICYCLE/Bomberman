
/*
 * File:   ModelHandler.cpp
 * Author: duplom_t
 *
 * Created on May 16, 2012, 12:54 AM
 */

#include "ModelHandler.hh"
#include <iostream>
#include "flatTexture.hh"

using namespace Bomberman;

ModelHandler::ModelHandler()
{
}


ModelHandler::~ModelHandler()
{
}

void      ModelHandler::preload()
{
  storeModel(new flatTexture("Ressources/Images/Menu/bg.png"),
        "mainbg");
  storeModel(new flatTexture("Ressources/Images/Menu/left.png"),
        "left");
  storeModel(new flatTexture("Ressources/Images/Menu/right.png"),
        "right");

  /* Save load */
  storeModel(new flatTexture("Ressources/Images/Menu/bg-load.png"),
        "bg-load");
  storeModel(new flatTexture("Ressources/Images/Menu/overlay-load.png"),
        "overlay-load");

  /* Arrows */
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-load-left.png"),
        "arrow-load-left");
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-load-right.png"),
        "arrow-load-right");
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-adventure-left.png"),
        "arrow-adventure-left");
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-adventure-right.png"),
        "arrow-adventure-right");
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-keybind-left.png"),
        "arrow-keybind-left");
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-keybind-right.png"),
        "arrow-keybind-right");
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-settings-left.png"),
        "arrow-settings-left");
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-settings-right.png"),
        "arrow-settings-right");

  storeModel(new flatTexture("Ressources/Images/Menu/arrow-customgame-left.png"),
        "arrow-customgame-left");
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-customgame-right.png"),
        "arrow-customgame-right");

  storeModel(new flatTexture("Ressources/Images/Menu/arrow-leaderboard-left.png"),
        "arrow-leaderboard-left");
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-leaderboard-right.png"),
        "arrow-leaderboard-right");

  storeModel(new flatTexture("Ressources/Images/Menu/arrow-loadmap-left.png"),
        "arrow-loadmap-left");
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-loadmap-right.png"),
        "arrow-loadmap-right");

  storeModel(new flatTexture("Ressources/Images/Menu/arrow-quickgame-left.png"),
        "arrow-quickgame-left");
  storeModel(new flatTexture("Ressources/Images/Menu/arrow-quickgame-right.png"),
        "arrow-quickgame-right");

  storeModel(new flatTexture("Ressources/Images/Menu/left.png"),
        "left");
  storeModel(new flatTexture("Ressources/Images/Menu/right.png"),
        "right");

  /* Overlays */
  storeModel(new flatTexture("Ressources/Images/Menu/custom_arrows.png"),
        "custom_arrows");
  storeModel(new flatTexture("Ressources/Images/Menu/custom_arrows_overlay.png"),
        "custom_arrows_overlay");
  storeModel(new flatTexture("Ressources/Images/Menu/join-overlay.png"),
        "join-overlay");

  /* Buttons */
  storeModel(new flatTexture("Ressources/Images/Menu/go-overlay.png"),
        "go-overlay");
  storeModel(new flatTexture("Ressources/Images/Menu/create-button.png"),
        "create-button");
  storeModel(new flatTexture("Ressources/Images/Menu/create-button-overlay.png"),
        "create-button-overlay");
  storeModel(new flatTexture("Ressources/Images/Menu/join-button-overlay.png"),
        "join-button-overlay");
  storeModel(new flatTexture("Ressources/Images/Menu/waiting-button.png"),
        "waiting-button");
  storeModel(new flatTexture("Ressources/Images/Menu/dot.png"),
        "dot");

  /* Games */
  storeModel(new flatTexture("Ressources/Images/Menu/bg-quickgame.png"),
        "bg-quickgame");
  storeModel(new flatTexture("Ressources/Images/Menu/bg-adventure.png"),
        "bg-adventure");
  storeModel(new flatTexture("Ressources/Images/Menu/bg-leaderboards.png"),
        "bg-leaderboards");
  storeModel(new flatTexture("Ressources/Images/Menu/bg-customgame.png"),
        "bg-customgame");
  storeModel(new flatTexture("Ressources/Images/Menu/bg-hostgame.png"),
        "bg-hostgame");
  storeModel(new flatTexture("Ressources/Images/Menu/bg-joingame.png"),
        "bg-joingame");
  storeModel(new flatTexture("Ressources/Images/Menu/bg-keybind.png"),
        "bg-keybind");
  storeModel(new flatTexture("Ressources/Images/Menu/press-enter.png"),
        "press-enter");

  storeModel(new flatTexture("Ressources/Images/Menu/keybind-overlay.png"),
        "keybind-overlay");


  storeModel(new flatTexture("Ressources/Images/Play/three.png"),
        "three");
  storeModel(new flatTexture("Ressources/Images/Play/two.png"),
        "two");
  storeModel(new flatTexture("Ressources/Images/Play/one.png"),
        "one");
  storeModel(new flatTexture("Ressources/Images/Play/go.png"),
        "go");
}

void      ModelHandler::storeModel(AModel * model, const std::string & name)
{
  objects_[name] = model;
}

AModel &  ModelHandler::getModel(const std::string &name)
{
  if (objects_.find(name) != objects_.end())
    return objects_[name]->clone();
  else
    throw std::exception();
}

ModelHandler &ModelHandler::get()
{
  static ModelHandler self;

  return self;
}



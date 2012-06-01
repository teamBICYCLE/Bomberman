
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
  storeModel(new flatTexture("Ressources/Images/Menu/custom_arrows.png"),
        "custom_arrows");
  storeModel(new flatTexture("Ressources/Images/Menu/custom_arrows_overlay.png"),
        "custom_arrows_overlay");
  storeModel(new flatTexture("Ressources/Images/Menu/go-overlay.png"),
        "go-overlay");
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
  storeModel(new flatTexture("Ressources/Images/Menu/left.png"),
        "left");
  storeModel(new flatTexture("Ressources/Images/Menu/right.png"),
        "right");

  /* Games */
  storeModel(new flatTexture("Ressources/Images/Menu/bg-quickgame.png"),
        "bg-quickgame");
  storeModel(new flatTexture("Ressources/Images/Menu/bg-adventure.png"),
        "bg-adventure");
  storeModel(new flatTexture("Ressources/Images/Menu/bg-leaderboards.png"),
        "bg-leaderboards");
  storeModel(new flatTexture("Ressources/Images/Menu/bg-customgame.png"),
        "bg-customgame");
  storeModel(new flatTexture("Ressources/Images/Menu/bg-keybind.png"),
        "bg-keybind");

  storeModel(new flatTexture("Ressources/Images/Menu/keybind-overlay.png"),
        "keybind-overlay");
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



/*
 * File:   ModelHandler.cpp
 * Author: duplom_t
 *
 * Created on May 16, 2012, 12:54 AM
 */

#include "ModelHandler.hh"
#include <iostream>

using namespace Bomberman;

ModelHandler::ModelHandler()
{
}


ModelHandler::~ModelHandler()
{
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
    return objects_["cube"]->clone();
}

ModelHandler &ModelHandler::get()
{
  static ModelHandler self;

  return self;
}



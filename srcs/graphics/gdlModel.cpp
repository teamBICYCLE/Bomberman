/**************************************************************************
** gdlModel.cpp: Created on 21 May 2012 by duplom_t
** for class : gdlModel
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "gdlModel.hh"
#include "unavalaibleRessource.hh"

gdlModel::gdlModel(const std::string & path)
  : AModel(), path_(path)
{
  this->model_ = gdl::Model::load(path);
  if (!this->model_.isValid())
    throw new unavalaibleRessource(path);
}

gdlModel::gdlModel(const AModel & orig)
  : model_(dynamic_cast<const gdlModel *>(&orig)->model_)
{
}

void gdlModel::draw()
{
  model_.draw();
}

void gdlModel::update(gdl::GameClock &clock)
{
  model_.update(clock);
}

AModel &gdlModel::clone()
{
  return *(new gdlModel(path_));
}

gdl::Model  & gdlModel::getModel()
{
  return this->model_;
}

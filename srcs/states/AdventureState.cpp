//
// AdventureState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:00:30 2012 lois burg
// Last update Sun Jun  3 13:55:00 2012 thibault carpentier
//

#include <GL/gl.h>
#include <GL/glu.h>
#include <GDL/Text.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Vector3d.hh"
#include "Player.hh"
#include "AdventureState.hh"
#include "Map.hh"
#include "Carrousel/Win.hh"
#include "SaveHandler.hh"

using namespace	Bomberman;

AdventureState::AdventureState()
  : PlayState(), curMapId_(0), mapBaseName_("./Ressources/Map/adventure"), nbMaps_(5)
{
}

AdventureState::~AdventureState()
{
}

bool	AdventureState::init()
{
  bool			success = true;
  std::stringstream	ss;

  try {
    Thinking::Brain::getBrain(0, 0);
    characterToUpdate_ = -1;
    ss << mapBaseName_ << curMapId_;
    curMap_ = new Map(ss.str());
    Character::CharacterId = 0;
    mapH_ = curMap_->getHeight();
    mapW_ = curMap_->getWidth();
    camera_.setHeightWidth(mapW_, mapH_);
    objs_.insert(objs_.end(), curMap_->getTerrain().begin(), curMap_->getTerrain().end());
    danger = &Thinking::Brain::getBrain(mapW_, mapH_)->danger_;
    ++curMapId_;
  } catch (Map::Failure& e) {
    success = false;
    std::cerr << e.what() << std::endl;
  }
  return (true);
}

void	AdventureState::cleanUp()
{
  std::cout << "clean up Adventure" << std::endl;
  Thinking::Brain::getBrain(0, 0);
  delete curMap_;
  PlayState::cleanUp();
}

void	AdventureState::win(StatesManager *mngr)
{
  CarrouselHandler	*cH;
  std::stringstream	ss;

  (void)mngr;
  std::cout << "YOU WIN" << std::endl;
  if (curMapId_ != nbMaps_)
    ++curMapId_;
  if (curMapId_ == nbMaps_)
    {
      std::cout << "CONGRATS!" << std::endl;
      cH = createInGameCH();
      cH->pushPage(new APage(new Win(winnerId_ + 1), "bg-ingame", "empty-arrows", "empty-arrows"));
      cH->setArrowFocus(false);
      cH->setEscapeFocus(false);
      mngr->pushState(cH);
      // mngr->popState();
    }
  else
    {
      delete curMap_;
      Thinking::Brain::getBrain(0, 0);
      ss << mapBaseName_ << curMapId_;
      try {
        clearObjs();
        Character::CharacterId = 0;
        curMap_ = new Map(ss.str());
        mapH_ = curMap_->getHeight();
        mapW_ = curMap_->getWidth();
        camera_.setHeightWidth(mapW_, mapH_);
        objs_.insert(objs_.end(), curMap_->getTerrain().begin(), curMap_->getTerrain().end());
	danger = &Thinking::Brain::getBrain(mapW_, mapH_)->danger_;
      } catch (Map::Failure& e) {
        std::cerr << e.what() << std::endl;
        mngr->popState();
      }
    }
}

void	AdventureState::gameOver(StatesManager *mngr)
{
  std::stringstream	ss;

  (void)mngr;
  std::cout << "YOU LOSE :(" << std::endl;
  curMapId_ = 0;
  delete curMap_;
  Thinking::Brain::getBrain(0, 0);
  ss << mapBaseName_ << curMapId_;
  try {
    clearObjs();
    Character::CharacterId = 0;
    curMap_ = new Map(ss.str());
    mapH_ = curMap_->getHeight();
    mapW_ = curMap_->getWidth();
    camera_.setHeightWidth(mapW_, mapH_);
    objs_.insert(objs_.end(), curMap_->getTerrain().begin(), curMap_->getTerrain().end());
    danger = &Thinking::Brain::getBrain(mapW_, mapH_)->danger_;
  } catch (Map::Failure& e) {
    std::cerr << e.what() << std::endl;
    mngr->popState();
  }
}

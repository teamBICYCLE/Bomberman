//
// PlayState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:00:30 2012 lois burg
// Last update Thu May 31 14:45:10 2012 thibault carpentier
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Vector3d.hh"
#include "Player.hh"
#include "PlayState.hh"
#include "Map.hh"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GDL/Text.hpp>

#include "SaveHandler.hh"

using namespace	Bomberman;

PlayState::PlayState(void)
  : bestScore_(0), winnerId_(0), characterToUpdate_(-1)
{
  Character::CharacterId = 0;
}

PlayState::PlayState(const std::list<AObject*> *list)
    : objs_(*list), winnerId_(0), characterToUpdate_(-1)
{
  Character::CharacterId = 0;
  img_ = gdl::Image::load("Ressources/Images/Play/floor.png");
  bestScore_ = 0;
  characterToUpdate_ = -1;
  mapH_ = PlayState::getHeight(list);
  mapW_ = PlayState::getWidth(list);
}

PlayState::~PlayState(void)
{
}

bool  PlayState::init()
{
  bool	success;

  img_ = gdl::Image::load("Ressources/Images/Play/floor.png");
  success = true;
  try {

    //    Map	map(13, 13, 1, 10, 0);
    Map         map("Ressources/Map/map5");
    // int	viewport[4];

    mapH_ = map.getHeight();
    mapW_ = map.getWidth();
    characterToUpdate_ = -1;
//    glGetIntegerv(GL_VIEWPORT, viewport);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0, viewport[2], viewport[3], 0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
    objs_.insert(objs_.end(), map.getTerrain().begin(), map.getTerrain().end());
  } catch (Map::Failure& e) {
    success = false;
    std::cerr << e.what() << std::endl;
  }
  return (success);
}

void  PlayState::cleanUp()
{
  std::cout << "clean up Play" << std::endl;
  clearObjs();
}

void	PlayState::clearObjs(void)
{
 for (std::list<AObject*>::iterator it = objs_.begin(); it != objs_.end(); ++it)
   delete (*it);
  objs_.clear();
}

void  PlayState::update(StatesManager *sMg)
{
  int		nbPlayers = 0;
  int		nbMonsters = 0;
  std::list<AObject*>::iterator	it;
  bool		update_ia = true;

  camera_.update(sMg->getGameClock(), sMg->getInput(), objs_);
  for (it = objs_.begin(); it != objs_.end();)
    {
      if (dynamic_cast<Player*>(*it))
        {
          ++nbPlayers;
          if (bestScore_ < static_cast<Player*>(*it)->getScore())
            {
              bestScore_ = static_cast<Player*>(*it)->getScore();
              winnerId_ = static_cast<Player*>(*it)->getId();
            }
        }
      else if (dynamic_cast<Monster*>(*it))
        {
          if (update_ia)
            {
              static_cast<Monster*>(*it)->getBrain()->updateDangerMap(objs_);
              update_ia = false;
            }
          ++nbMonsters;
        }
      if (!(*it)->toRemove())
        {
          if (!dynamic_cast<Player*>(*it) || (dynamic_cast<Player*>(*it) && static_cast<Player*>(*it)->getId() == characterToUpdate_) ||
              characterToUpdate_ == -1)
            (*it)->update(sMg->getGameClock(), sMg->getInput(), objs_);
          ++it;
        }
      else
        it = objs_.erase(it);
    }
  // bind touche echap
  PlayState::checkEndGame(sMg, nbPlayers, nbMonsters);
}

void	PlayState::win(StatesManager *mngr)
{
  std::cout << "PLAYER " << winnerId_ + 1 << " WIN" << std::endl;
  saveScore();
  mngr->popState();//passer sur winstate
}

void	PlayState::gameOver(StatesManager *mngr)
{
  std::cout << "PLAYER " << winnerId_ + 1 << " LOOSE" << std::endl;
  saveScore();
  mngr->popState();//passer sur gameOverstate
}

void	PlayState::checkEndGame(StatesManager *mngr, int nbPlayers, int nbMonsters)
{
  if (bestScore_ != -1)
    {
      if (!nbPlayers)
        gameOver(mngr);
      else if ((nbPlayers == 1 && !nbMonsters))
        win(mngr);
    }
}

void	PlayState::saveScore(void) const
{
  std::ofstream	leaderboards("./Ressources/Scores/leaderboards.sc", std::ios::app);

  if (leaderboards.good())
    {
      std::cout << bestScore_ << std::endl;
      leaderboards << "AAAA: " << bestScore_ << std::endl;
      leaderboards.close();
    }
  std::cout << "GAME OVER! Highscore: " << bestScore_ << std::endl;
}

#define MULTZ 1.0f

void  PlayState::draw(StatesManager * sMg)
{
  (void)sMg;
  camera_.draw();
  camera_.drawRepere();
  glPushMatrix();
  //    glTranslated(-0.5f, -0.5f, 0);
  glEnable(GL_TEXTURE_2D);
  if (img_.isValid())
    {
      img_.bind();
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
  glBegin(GL_QUADS);
  glNormal3d(0, 0, 1);
  glTexCoord2d(0.0f, 0.0f); glVertex3f(0, 0, 0);
  glTexCoord2d(static_cast<double>(this->mapW_) / 2.0f, 0.0f);
  glVertex3f(this->mapW_, 0, 0);
  glTexCoord2d(static_cast<double>(this->mapW_) / 2.0f, static_cast<double>(this->mapH_) /2.0f);
  glVertex3f(this->mapW_, this->mapH_, 0);
  glTexCoord2d(0.0f, static_cast<double>(this->mapH_) /2.0f);
  glVertex3f(0, this->mapH_, 0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
  glPushMatrix();
  std::for_each(objs_.begin(), objs_.end(), [](AObject *obj) -> void {
      obj->draw();
    });
  glPopMatrix();
  glFlush();
  // basic fps time handling
}

void  PlayState::pause()
{
  std::cout << "pause Play" << std::endl;
}

void  PlayState::resume()
{
  std::cout << "resume Play" << std::endl;
}

uint PlayState::getHeight(const std::list<AObject*> *list) const
{
    std::list<AObject*>::const_iterator it;
    uint maxY = list->front()->getPos().y;

    for (it = list->begin(); it != list->end(); it++)
    {
        if ((*it)->getPos().y > maxY)
            maxY = (*it)->getPos().y;
    }
    return maxY;
}

uint PlayState::getWidth(const std::list<AObject*> *list) const
{
    std::list<AObject*>::const_iterator it;
    uint maxX = list->front()->getPos().x;

    for (it = list->begin(); it != list->end(); it++)
    {
        if ((*it)->getPos().x > maxX)
            maxX = (*it)->getPos().x;
    }
    return maxX;
}

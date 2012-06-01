//
// PlayState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:00:30 2012 lois burg
// Last update Thu May 31 16:41:42 2012 lois burg
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
#include "Carrousel/CarrouselHandler.hh"
#include "Carrousel/LoadContent.hh"
#include "Score.hh"

using namespace	Bomberman;

PlayState::PlayState(void)
  : bestScore_(0), winnerId_(0), characterToUpdate_(-1), escapeDisable_(false),
  readyUp_(3.0f), lastTime_(-1)
{
  Character::CharacterId = 0;
  img_ = gdl::Image::load("Ressources/Images/Play/floor.png");
  bg_ = gdl::Image::load("Ressources/Images/Play/bg.png");
}

PlayState::PlayState(const std::list<AObject*> *list)
    : objs_(*list), winnerId_(0), characterToUpdate_(-1), escapeDisable_(false),
      readyUp_(3.0f), lastTime_(-1)
{
  Character::CharacterId = 0;
  img_ = gdl::Image::load("Ressources/Images/Play/floor.png");
  bg_ = gdl::Image::load("Ressources/Images/Play/bg.png");
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

  success = true;
  try {

    //    Map	map(13, 13, 1, 10, 0);
    Map         map("Ressources/Map/map2");
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
  float		now = sMg->getGameClock().getTotalGameTime();

  camera_.update(sMg->getGameClock(), sMg->getInput(), objs_);
  if (lastTime_ == -1)
    lastTime_ = now;
  if (readyUp_ > 0)
    {
      readyUp_ -= now - lastTime_;
      lastTime_ = now;
    }
  for (it = objs_.begin(); readyUp_ <= 0 && it != objs_.end();)
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
  if (sMg->getInput().isKeyDown(gdl::Keys::Escape) && !escapeDisable_)
    {
      GLvoid    *data = (unsigned char *)(calloc(1600 * 900 * 3, sizeof(unsigned char)));
      CarrouselHandler  *cH;

      glReadPixels(0, 0, 1600, 900, GL_RGB, GL_UNSIGNED_BYTE, data);
      cH = new CarrouselHandler(data);
      std::cout << "failed to read" << std::endl;
      cH->pushPage(new APage(new LoadContent(), "bg-load", "arrow-load-left", "arrow-load-right"));
      sMg->pushState(cH);
      escapeDisable_ = true;
    }
  else if (!sMg->getInput().isKeyDown(gdl::Keys::Escape))
    escapeDisable_ = false;
  PlayState::checkEndGame(sMg, nbPlayers, nbMonsters);
}

void	PlayState::win(StatesManager *mngr)
{
    Score score;

    std::cout << "PLAYER " << winnerId_ + 1 << " WIN" << std::endl;
    score.save(bestScore_);
    mngr->popState();//passer sur winstate
}

void	PlayState::gameOver(StatesManager *mngr)
{
    Score score;

    std::cout << "PLAYER " << winnerId_ + 1 << " LOOSE" << std::endl;
    score.save(bestScore_);
    mngr->popState();//passer sur gameOverstate
}

void	PlayState::checkEndGame(StatesManager *mngr, int nbPlayers, int nbMonsters)
{
  if (bestScore_ != -1 && readyUp_ <= 0)
    {
      if (!nbPlayers)
        gameOver(mngr);
      else if ((nbPlayers == 1 && !nbMonsters))
        win(mngr);
    }
}

//void	PlayState::saveScore(void) const
//{
//  std::ofstream	leaderboards("./Ressources/Scores/leaderboards.sc", std::ios::app);

//  if (leaderboards.good())
//    {
//      std::cout << bestScore_ << std::endl;
//      leaderboards << "AAAA: " << bestScore_ << std::endl;
//      leaderboards.close();
//    }
//  std::cout << "GAME OVER! Highscore: " << bestScore_ << std::endl;
//}

void  PlayState::draw(StatesManager * sMg)
{
  double      h = this->mapH_, w = this->mapW_;
  (void)sMg;
  camera_.draw();
  camera_.drawRepere();

  glDepthMask(GL_FALSE);
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  if (bg_.isValid())
    {
    bg_.bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
  glColor3d(0, 1, 0);
  glBegin(GL_QUADS);
  glTexCoord2d(1, 0); glVertex3d(-w, -h, 0);
  glTexCoord2d(0, 0); glVertex3d(w + (2*w), -h, 0);
  glTexCoord2d(0, 1); glVertex3d(w + (2*w) , h + (2*h), 0);
  glTexCoord2d(1, 1); glVertex3d(-w, h + (2*h), 0);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  glDepthMask(GL_TRUE);

  glPushMatrix();
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

//
// PlayState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:00:30 2012 lois burg
// Last update Tue May 22 15:14:58 2012 thibault carpentier
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

bool  PlayState::init()
{
  bool	success;

  img_ = gdl::Image::load("Ressources/Images/Play/floor.png");
  success = true;
  try {
   // Map	map(13, 13, 1, 1, 1);
        Map	map("Ressources/Map/map2");
    // int	viewport[4];

    bestScore_ = 0;
    mapH_ = map.getHeight();
    mapW_ = map.getWidth();
    std::cout << mapH_ << " " << mapW_ << std::endl;
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
  objs_.clear();
}

void  PlayState::update(StatesManager * sMg)
{
  int		nbPlayers = 0;
  int		nbMonsters = 0;
  std::list<AObject*>::iterator	it;

  camera_.update(sMg->getGameClock(), sMg->getInput());
  for (it = objs_.begin(); it != objs_.end();)
    {
      if (dynamic_cast<Player*>(*it))
      {
          ++nbPlayers;
          if (bestScore_ < static_cast<Player*>(*it)->getScore())
              bestScore_ = static_cast<Player*>(*it)->getScore();
      }
      else if (dynamic_cast<Monster*>(*it))
          ++nbMonsters;

      if (!(*it)->toRemove())
      {
          (*it)->update(sMg->getGameClock(), sMg->getInput(), objs_);
          ++it;
      }
      else
          it = objs_.erase(it);
    }
  if (bestScore_ != -1)
  {
      if (!nbPlayers)
          gameOver(sMg);
      else if ((nbPlayers == 1 && !nbMonsters))
          win(sMg);
  }
}

void	PlayState::win(StatesManager *mngr)
{
  static bool LOL = false;

  if (LOL)
    return;
  LOL = true;
  (void)mngr;//switcher sur winstate
  std::cout << "YOU WIN" << std::endl;
  saveScore();
}

void	PlayState::gameOver(StatesManager *mngr)
{
  static bool LOL = false;

  if (LOL)
    return;
  LOL = true;
  (void)mngr;//switcher sur gameoverstate
  std::cout << "YOU LOSE" << std::endl;
  saveScore();
}

void	PlayState::saveScore(void) const
{
  std::ofstream	leaderboards("./Ressources/scores/leaderboards.sc", std::ios::app);

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
  glTexCoord2d(static_cast<double>(this->mapH_) / 2.0f, 0.0f);
  glVertex3f(this->mapH_, 0, 0);
  glTexCoord2d(static_cast<double>(this->mapH_) / 2.0f, static_cast<double>(this->mapW_) /2.0f);
  glVertex3f(this->mapH_, this->mapW_, 0);
  glTexCoord2d(0.0f, static_cast<double>(this->mapW_) /2.0f);
  glVertex3f(0, this->mapW_, 0);
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

//
// PlayState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:00:30 2012 lois burg
// Last update Fri May 18 18:13:05 2012 lois burg
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

  success = true;
  try {
    SaveHandler s;
    Map	map(13, 13, 2);
    // int	viewport[4];

    bestScore_ = 0;
    mapH_ = 13;
    mapW_ = 13;
//    glGetIntegerv(GL_VIEWPORT, viewport);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0, viewport[2], viewport[3], 0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
    objs_.insert(objs_.end(), map.getTerrain().begin(), map.getTerrain().end());
   // s.save(objs_);
   // s.load(objs_);
  } catch (Map::Failure& e) {
    success = false;
    std::cerr << e.what() << std::endl;
  }
  return (success);
}

void  PlayState::cleanUp()
{
  std::cout << "clean up Play" << std::endl;
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
  if ((!nbPlayers || (nbPlayers == 1 && !nbMonsters)) && bestScore_ != -1)
    saveScore(bestScore_);//push du statut gameover
}

void	PlayState::saveScore(int score) const
{
  static bool LOL = false;
  std::ofstream	leaderboards("./Ressources/scores/leaderboards.sc", std::ios::app);

  if (LOL)
    return;
  if (leaderboards.good())
    {
      LOL = true;
      std::cout << score << std::endl;
      leaderboards << "AAAA: " << score << std::endl;
      leaderboards.close();
    }
  std::cout << "GAME OVER! Highscore: " << score << std::endl;
}

#define MULTZ 1.0f

void  PlayState::draw(StatesManager * sMg)
{
  (void)sMg;
  camera_.draw();
    camera_.drawRepere();
    glPushMatrix();
//    glTranslated(-0.5f, -0.5f, 0);



    glBegin(GL_QUADS);
    glColor3f(0, 0, 1.0f);
    glVertex3f(0, 0, 0);
    glVertex3f((this->mapH_ * MULTZ), 0, 0);
    glVertex3f((this->mapH_ * MULTZ), (this->mapW_ * MULTZ), 0);
    glVertex3f(0, (this->mapW_ * MULTZ), 0);
    glEnd();
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

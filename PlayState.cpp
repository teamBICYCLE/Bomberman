//
// PlayState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:00:30 2012 lois burg
// Last update Sat May  5 17:03:11 2012 romain sylvian
//

#include <iostream>
#include <algorithm>
#include "Vector3d.hh"
#include "Player.hh"
#include "PlayState.hh"
#include "Map.hh"

#include <GL/gl.h>
#include <GL/glu.h>

using namespace	Bomberman;

bool  PlayState::init()
{
  bool	success;

  success = true;
  try {
    Map	map(13, 13, 4);
    int	viewport[4];

    mapH_ = 13;
    mapW_ = 13;
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
}

void  PlayState::update(StatesManager * sMg)
{
  camera_.update(sMg->getGameClock(), sMg->getInput());
  std::for_each(objs_.begin(), objs_.end(), [sMg](AObject *obj) -> void {
      obj->update(sMg->getGameClock(), sMg->getInput());
    });
}

#define MULTZ 40.0f

void  PlayState::draw(StatesManager * sMg)
{
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//  int viewport[4];

//  glGetIntegerv(GL_VIEWPORT, viewport);
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  gluOrtho2D(0, viewport[2], viewport[3], 0);
//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();
//  glPushMatrix();
  std::cout << this->mapH_ << " " << this->mapW_ << std::endl;
  camera_.draw();
//  glBegin(GL_QUADS);
//  glColor3d(0, 0, 1.0f);
//  glVertex3d(0, 0, 0);
//  glVertex3d(this->mapH_ * MULTZ, 0, 0);
//  glVertex3d(this->mapH_ * MULTZ, this->mapW_ * MULTZ, 0);
//  glVertex3d(0, this->mapW_ * MULTZ, 0);
//  glEnd();
  std::for_each(objs_.begin(), objs_.end(), [](AObject *obj) -> void {
      obj->draw();
    });
glPopMatrix();
}

void  PlayState::pause()
{
  std::cout << "pause Play" << std::endl;
}

void  PlayState::resume()
{
  std::cout << "resume Play" << std::endl;
}

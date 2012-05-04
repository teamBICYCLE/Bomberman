//
// PlayState.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:00:30 2012 lois burg
// Last update Fri May  4 16:29:53 2012 lois burg
//

#include <iostream>
#include <algorithm>
#include "Vector3d.hh"
#include "Player.hh"
#include "PlayState.hh"
#include "Block.hh"
#include "Brick.hh"

#include <GL/gl.h>
#include <GL/glu.h>

using namespace	Bomberman;

void  PlayState::init()
{
  int viewport[4];

  glGetIntegerv(GL_VIEWPORT, viewport);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, viewport[2], viewport[3], 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  objs_.push_back(new Player(Vector3d(), Vector3d(), Vector3d()));
  objs_.push_back(new Block(Vector3d(0, 0, 0), Vector3d(), Vector3d(50, 50, 0)));
  objs_.push_back(new Brick(Vector3d(50, 50, 0), Vector3d(), Vector3d(50, 50, 0)));
}

void  PlayState::cleanUp()
{
  std::cout << "clean up Play" << std::endl;
}

void  PlayState::update(StatesManager * sMg)
{
  std::for_each(objs_.begin(), objs_.end(), [sMg](AObject *obj) -> void {
      obj->update(sMg->getGameClock(), sMg->getInput());
    });
}

void  PlayState::draw(StatesManager * sMg)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  int viewport[4];

  glGetIntegerv(GL_VIEWPORT, viewport);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, viewport[2], viewport[3], 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();
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

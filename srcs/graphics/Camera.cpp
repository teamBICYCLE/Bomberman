/**************************************************************************
** Camera.cpp: Created on 5 May 2012 by duplom_t
** for class : Camera
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include <cmath>
#include <algorithm>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <algorithm>
#include <SFML/Window.hpp>
#include <algorithm>
#include "Player.hh"
#include "Camera.hh"

Camera::Camera(size_t mapW, size_t mapH)
  : position_(-1.f, -1.f, -1.0f), mapW_(mapW), mapH_(mapH), anim_(2.5f), lastTime_(-1)
{
  this->initialize();
}

void Camera::setHeightWidth(size_t mapW, size_t mapH)
{
  mapW_ = mapW;
  mapH_ = mapH;
}

void    Camera::initialize()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void    Camera::update(const gdl::GameClock & gameClock, gdl::Input & input,
                       std::list<Bomberman::AObject*>& objs)
{
  Vector3d    position, zoom;
  Vector3d    min(-1, -1, 0), max(0, 0, 0);
  float       i = 0.0f;
  float       now = gameClock.getTotalGameTime();

  (void)gameClock;
  (void)input;
  if (input.isKeyDown(gdl::Keys::Up))
    glDisable(GL_LIGHTING);

  std::for_each(objs.begin(), objs.end(), [&](Bomberman::AObject * obj) -> void {
      if (dynamic_cast<Bomberman::Player *>(obj))
	{
	  Vector3d local = obj->getPos();

	  if (local.x < min.x || min.x == -1)
	    min.x = local.x;
	  if (local.x > max.x)
	    max.x = local.x;
	  if (local.y < min.y || min.y == -1)
	    min.y = local.y;
	  if (local.y > max.y)
	    max.y = local.y;
	  position += obj->getPos();
	  ++i;
	}
    });
  max.x = (max.x - min.x) + 2;
  max.x = max.x >= 16 ? max.x : 16;
  max.y = (max.y - min.y) + 1.125;
  max.y = max.y >= 9 ? max.y : 9;
  if (max.x / 16.0f >= max.y / 9.0f)
    {
      zoom.x = max.x;
      zoom.y = zoom.x * (9.0f/16.0f);
    }
  else
    {
      zoom.y = max.y;
      zoom.x = zoom.y * (16.0f/9.0f);
    }
  if (i)
    position /= i;

#define MAX_X_VALUE ((mapW_ / 2.0f) < (zoom.x / 2.0f) - 2.0f ? (mapW_ / 2.0f) : (zoom.x / 2.0f) - 2.0f)
  if (position.x < MAX_X_VALUE)
    position.x = MAX_X_VALUE;
  else if (position.x > mapW_ - MAX_X_VALUE)
    position.x = mapW_ - MAX_X_VALUE;
#undef MAX_X_VALUE

#define MAX_Y_VALUE ((mapH_ / 2.0f) < (zoom.y / 2.0f) - 2.0f  ? (mapH_ / 2.0f) : (zoom.y / 2.0f) - 2.0f)
  if (position.y < MAX_Y_VALUE)
    position.y = MAX_Y_VALUE;
  else if (position.y > mapH_ - MAX_Y_VALUE)
    position.y = mapH_ - MAX_Y_VALUE;
  position.y -= 0.5;
#undef MAX_Y_VALUE

  if (anim_ <= 0)
    {
      attenuateTransition(position_, position);
      attenuateTransition(zoom_, zoom);
    }

  if (lastTime_ == -1)
    lastTime_ = now;
  if (anim_ > 0)
    {
      position_ = position;
      zoom_ = zoom;
      anim_ -= now - lastTime_;
      lastTime_ = now;
      position_.y += exp(anim_) - 1;
      zoom_ /= exp(anim_ * 1.0f);
    }
}

void    Camera::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glEnable(GL_BLEND) ;
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-zoom_.x / 2, zoom_.x / 2, -zoom_.y / 2, zoom_.y / 2, this->zNear, this->zFar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glScaled(1, -1, 1);
  gluLookAt(position_.x, position_.y + 3.0f, 4.0f,
            position_.x, position_.y, position_.z,
            0.0, 1, 0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void   Camera::drawRepere()
{
  glBegin(GL_LINES);
  glColor3f(0, 0, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 1);
  glEnd();

  glBegin(GL_LINES);
  glColor3f(0, 1, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 1, 0);
  glEnd();

  glBegin(GL_LINES);
  glColor3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(1, 0, 0);
  glEnd();
  glColor3f(1, 1, 1);
}

void Camera::attenuateTransition(Vector3d &old, const Vector3d &dir, float max)
{
  float j;

#define ABS(x) (x >= 0 ? x : -x)
  for (j = 1.0f;  ABS(old.x - dir.x) / j > max ||
       ABS(old.y - dir.y) / j > max; j += 0.5);
  old.x -= (old.x - dir.x) / j;
  old.y -= (old.y - dir.y) / j;
}

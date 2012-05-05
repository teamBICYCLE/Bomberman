/**************************************************************************
** Camera.cpp: Created on 5 May 2012 by duplom_t
** for class : Camera
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "Camera.hh"
#include <GL/gl.h>
#include <GL/glu.h>

Camera::Camera()
  :position_(0.0f, 0.0f, 900.0f), rotation_(0.0f, 0.0f, 0.0f)
{
  this->initialize();
}

void    Camera::initialize()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(this->fov, this->winxSize / this->winySize,
                 this->zNear, this->zFar);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void    Camera::update(const gdl::GameClock & gameClock, const gdl::Input & input)
{

}

void    Camera::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(this->fov, this->winxSize / this->winySize,
                 this->zNear, this->zFar);
  gluLookAt(position_.x, position_.y, position_.z,
            0, 0, 0,
            0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  std::cout << "camera draw" << std::endl;
}

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
#include <SFML/Window.hpp>


Camera::Camera()
  :position_(5.0f, 3.0f, 11.0f), rotation_(0.0f, 0.0f, 0.0f)
{
  this->initialize();
}

void    Camera::initialize()
{
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  gluPerspective(this->fov, this->winxSize / this->winySize,
//                 this->zNear, this->zFar);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

}

void    Camera::update(const gdl::GameClock & gameClock, gdl::Input & input)
{
  
  //  if (input.isKeyDown(gdl::Keys::Up))
  //    position_.x -= 1;
  //  if (input.isKeyDown(gdl::Keys::Down))
  //    position_.x += 1;
}

void    Camera::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.76f, 0.12f, 0.37f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
// glOrtho(-50, 600, -50, 600, 1, 100000);
  gluPerspective(this->fov, this->winxSize / this->winySize,
                 this->zNear, this->zFar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(position_.x, position_.y, position_.z,
            5, 5, 0,
            0, 1, 0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  
  //glEnable(GL_LIGHTING);
  //glEnable(GL_LIGHT0);
  
  GLfloat  pos[4];
  pos[0] = 0;
  pos[1] = 0;
  pos[2] = 100;
  pos[3] = 1;
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();
//  glEnable(GL_DEPTH_TEST);
//  glDepthFunc(GL_LEQUAL);
}
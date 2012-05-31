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
#include <GL/glut.h>
#include <SFML/Window.hpp>
#include <algorithm>
#include "Player.hh"

Camera::Camera()
  :position_(5.f, 3.f, 1.0f)
{
  this->initialize();
}

void    Camera::initialize()
{
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  gluPerspective(Camera::fov, Camera::winxSize / this->winySize,
//                 this->zNear, Camera::zFar);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_LIGHTING);
}

void    Camera::update(const gdl::GameClock & gameClock, gdl::Input & input,
                       std::list<Bomberman::AObject*>& objs)
{
  Vector3d    position;
  Vector3d    min(0, 0, 0), max(0, 0, 0);
  int         i = 0;

  (void)gameClock;
  (void)input;
  if (input.isKeyDown(gdl::Keys::Up))
    glDisable(GL_LIGHTING);
  std::for_each(objs.begin(), objs.end(), [&](Bomberman::AObject * obj) -> void {
     if (dynamic_cast<Bomberman::Player *>(obj))
  {
                Vector3d local = obj->getPos();

                if (local.x < min.x)
                min.x = local.x;
  if (local.x > max.x)
    max.x = local.x;
  if (local.y < min.y)
    min.y = local.y;
  if (local.y > max.y)
    max.y = local.y;
      position += obj->getPos();
      ++i;
  }
  });
max.x = (max.x - min.x);
max.x = max.x >= 16 ? max.x : 16;
max.y = (max.y - min.y);
max.y = max.y >= 9 ? max.y : 9;
if (max.x / 16 >= max.y / 9)
{
  zoom_.x = max.x;
  zoom_.y = zoom_.x * (9.0f/16.0f);
}
else
{
zoom_.y = max.y;
zoom_.x = zoom_.y * (16.0f/9.0f);
}
position /= i;
position_ = position;
  //  if (input.isKeyDown(gdl::Keys::Down))
  //    position_.x += 1;
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
  //gluPerspective(this->fov, this->winxSize / this->winySize,
   //             this->zNear, this->zFar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glScaled(1, -1, 1);
  gluLookAt(position_.x, position_.y + 3.0f, 4.0f,
           position_.x, position_.y, position_.z,
            0.0, 1, 0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glEnable(GL_LIGHT0);
  GLfloat ambient[] = { 0.13,0.13,0.13,1.0 };
  GLfloat diffuse[] = { 0.8,0.8,0.8,1.0 };
  GLfloat specular[] = { 0.5,0.5,0.5,1.0 };
  GLfloat shinines[] = { 5.0 };
  glEnable(GL_COLOR_MATERIAL);
//              glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
//  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
//  glMaterialfv(GL_FRONT,GL_DIFFUSE, diffuse);
  //glMaterialfv(GL_FRONT,GL_SPECULAR, specular);
//  glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
//  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
  //glMaterialfv(GL_FRONT,GL_SHININESS, shinines);
  GLfloat  pos[4];
  pos[0] = -20;
  pos[1] = -20;
  pos[2] = 60;
  pos[3] = 1;
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();
//  glEnable(GL_DEPTH_TEST);
//  glDepthFunc(GL_LEQUAL);
}

void   Camera::drawRepere()
{
   glBegin(GL_LINES);
    glColor3f(0, 0, 100);
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

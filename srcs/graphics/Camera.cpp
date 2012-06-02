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
  : position_(5.f, 3.f, 1.0f), mapW_(0), mapH_(0), anim_(2.5f), lastTime_(-1)
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
  //  glMatrixMode(GL_PROJECTION);
  //  glLoadIdentity();
  //  gluPerspective(Camera::fov, Camera::winxSize / this->winySize,
  //                 this->zNear, Camera::zFar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  //glEnable(GL_LIGHTING);
}

void    Camera::update(const gdl::GameClock & gameClock, gdl::Input & input,
                       std::list<Bomberman::AObject*>& objs)
{
  Vector3d    position;
  Vector3d    min(-1, -1, 0), max(0, 0, 0);
  int         i = 0;
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

#define MAX_X_VALUE ((mapW_ / 2) < (zoom_.x / 2) - 2 ? (mapW_ / 2) : (zoom_.x / 2) - 2)
  if (position_.x < MAX_X_VALUE)
position_.x = MAX_X_VALUE;
  else if (position_.x > mapW_ - MAX_X_VALUE)
position_.x = mapW_ - MAX_X_VALUE;
#undef MAX_X_VALUE

#define MAX_Y_VALUE ((mapH_ / 2) < (zoom_.y / 2) - 2  ? (mapH_ / 2) : (zoom_.y / 2) - 2)
if (position_.y < MAX_Y_VALUE)
  position_.y = MAX_Y_VALUE;
else if (position_.y > mapH_ - MAX_Y_VALUE)
  position_.y = mapH_ - MAX_Y_VALUE;
position_.y -= 0.5;
#undef MAX_Y_VALUE

std::cout << "anim = " << anim_<< std::endl;
if (lastTime_ == -1)
  lastTime_ = now;
if (anim_ > 0)
{
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

  //  glEnable(GL_LIGHT0);
  //  GLfloat ambient[] = { 0.13,0.13,0.13,1.0 };
  //  GLfloat diffuse[] = { 0.8,0.8,0.8,1.0 };
  //  GLfloat specular[] = { 0.5,0.5,0.5,1.0 };
  //  GLfloat shinines[] = { 5.0 };
  //  glEnable(GL_COLOR_MATERIAL);
  //              glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
  //  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  //  glMaterialfv(GL_FRONT,GL_DIFFUSE, diffuse);
  //  glMaterialfv(GL_FRONT,GL_SPECULAR, specular);
  //  glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
  //  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
  //  glMaterialfv(GL_FRONT,GL_SHININESS, shinines);
  //  GLfloat  pos[4];
  //  pos[0] = -20;
  //  pos[1] = -20;
  //  pos[2] = 60;
  //  pos[3] = 1;
  //  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  //  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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

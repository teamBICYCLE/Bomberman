/**************************************************************************
** Camera.hh: Created on 5 May 2012 by duplom_t
** for class : Camera
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef CAMERA_HH
#define CAMERA_HH

#include <GDL/GameClock.hpp>
#include <GDL/Input.hpp>
#include "Vector3d.hh"

namespace Bomberman {class AObject;}

class Camera
{
public:
  Camera();

  void    initialize(void);
  void    update(const gdl::GameClock &, gdl::Input &, std::list<Bomberman::AObject*>& objs);
  void    draw(void);

  void    drawRepere(void);

private:
static const float fov = 70.0f;
static const float winxSize = 800.0f;
static const float winySize = 600.0f;
static const float zNear = 1.0f;
static const float zFar = 1000.0f;
   // const float fov = 70.0f;
   // const float winxSize = 1600.0f;
   // const float winySize = 900.0f;
   // const float zNear = 0.f;
   // const float zFar = 1000.0f;

protected:
  Vector3d    position_;
  Vector3d    zoom_;
};

#include "AObject.hh"

#endif // CAMERA_HH

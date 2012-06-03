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
  Camera(size_t mapW = 0, size_t mapH = 0);

  void    setHeightWidth(size_t mapW, size_t mapH);
  void    initialize(void);
  void    update(const gdl::GameClock &, gdl::Input &, std::list<Bomberman::AObject*>& objs);
  void    draw(void);

  void    drawRepere(void);
  void    attenuateTransition(Vector3d & old, const Vector3d & dir, float max = 0.05);

private:
  static constexpr float fov = 70.0f;
  static constexpr float winxSize = 800.0f;
  static constexpr float winySize = 600.0f;
  static constexpr float zNear = -1000.0f;
  static constexpr float zFar = 1000.0f;
protected:
  Vector3d    position_;
  Vector3d    zoom_;
  size_t      mapW_;
  size_t      mapH_;
  float       anim_;
  float       lastTime_;
};

#include "AObject.hh"

#endif // CAMERA_HH

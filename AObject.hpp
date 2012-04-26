/**************************************************************************
** AObject.hpp: Created on 21 Apr 2012 by duplom_t
** for class : AObject
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef AOBJECT_HPP
#define AOBJECT_HPP

#include <GDL/GameClock.hpp>
#include <GDL/Input.hpp>
#include "Vector3f.hpp"

class AObject
{
public:
  AObject(void);
  virtual void    initialize(void) = 0;
  virtual void    update(const gdl::GameClock &, gdl::Input &) = 0;
  virtual void    draw(void) = 0;

protected:
  Vector3f        position_;
  Vector3f        rotation_;
};

#endif // AOBJECT_HPP

/**************************************************************************
** Vector3f.cpp: Created on 21 Apr 2012 by duplom_t
** for class : Vector3f
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "Vector3f.hpp"

Vector3f::Vector3f(void)
  : x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3f::Vector3f(float x, float y, float z)
  : x(x), y(y), z(z)
{
}

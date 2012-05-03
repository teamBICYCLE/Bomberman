//
// Vector3.cpp for  in /home/jonathan/Projets/Bomberman/srcs
//
// Made by Jonathan Machado
// Login   <jonathan.machado@epitech.net>
//
// Started on  Thu Apr 26 20:21:29 2012 Jonathan Machado
// Last update Thu May  3 16:42:31 2012 lois burg
//

#include <cmath>
#include "Vector3d.hh"

Vector3d::Vector3d(double x, double y, double z)
: x(x), y(y), z(z)
{
}


Vector3d::Vector3d(const double *v)
: x(v[0]), y(v[1]), z(v[2])
{
}


Vector3d::Vector3d(const Vector3d &v)
: x(v.x), y(v.y), z(v.z)
{
}

Vector3d&	Vector3d::operator=(const Vector3d& v)
{
  set(v.x, v.y, v.z);
  return *this;
}

void		Vector3d::set(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

double&		Vector3d::operator[](int i)
{
  switch (i)
    {
    case 0:
      return x;
      break;
    case 1:
      return y;
      break;
    case 2:
      return z;
      break;
    default:
      return x;
    }
  return x;
}

double		Vector3d::operator[](int i) const
{
  switch (i)
    {
    case 0:
      return x;
      break;
    case 1:
      return y;
      break;
    case 2:
      return z;
      break;
    default:
      return 0.0d;
    }
  return 0.0d;
}

Vector3d&	Vector3d::operator+=(const Vector3d& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

Vector3d&	Vector3d::operator-=(const Vector3d& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

Vector3d&	 Vector3d::operator*=(double s)
{
  x *= s;
  y *= s;
  z *= s;
  return *this;
}

Vector3d&	 Vector3d::operator/=(double s)
{
  x /= s;
  y /= s;
  z /= s;
  return *this;
}

Vector3d	 Vector3d::operator+(const Vector3d& v) const
{
  return Vector3d(x + v.x,  y + v.y, z + v.z);
}

Vector3d	 Vector3d::operator-(const Vector3d& v) const
{
  return Vector3d(x - v.x, y - v.y, z - v.z);
}

Vector3d	 Vector3d::operator-(void) const
{
  return Vector3d(-x, -y, -z);
}

Vector3d	 Vector3d::operator*(double s) const
{
  return Vector3d(x * s, y * s, z * s);
}

Vector3d	 Vector3d::operator/(double s) const
{
  return Vector3d(x / s, y / s, z / s);
}

bool		 Vector3d::operator==(const Vector3d& v) const
{
  return ((x == v.x) &&
	  (y == v.y) &&
	  (z == v.z));
}

bool		Vector3d::operator!=(const Vector3d& v) const
{
  return ((x != v.x) ||
	  (y != v.y) ||
	  (z != v.z));
}

double		Vector3d::length() const
{
  return sqrt(lengthSquared());
}

double		 Vector3d::lengthSquared() const
{
  return x * x + y * y + z * z;
}

void		 Vector3d::normalize()
{
  double len = length();
  if (len > 0)
    {
      x /= len;
      y /= len;
      z /= len;
    }
}

double		 Vector3d::dot(const Vector3d& v) const
{
  return x * v.x + y * v.y + z * v.z;
}

Vector3d	 Vector3d::cross(const Vector3d& v) const
{
  return Vector3d(y * v.z - z * v.y,
		  z * v.x - x * v.z,
		  x * v.y - y * v.x);
}

double		 Vector3d::distance(const Vector3d& v) const
{
  return sqrt(distanceSquared(v));
}

double		 Vector3d::distanceSquared(const Vector3d& v) const
{
  double dx, dy, dz;
  dx = x - v.x;
  dy = y - v.y;
  dz = z - v.z;
  return dx * dx + dy * dy + dz * dz;
}

Vector3d	operator*(double s, const Vector3d& v)
{
  return v * s;
}

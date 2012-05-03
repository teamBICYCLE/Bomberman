/*
** Vector3.h for  in /home/jonathan/Projets/Bomberman/srcs
**
** Made by Jonathan Machado
** Login   <jonathan.machado@epitech.net>
**
** Started on  Thu Apr 26 20:25:57 2012 Jonathan Machado
// Last update Sun Apr 29 13:22:21 2012 Jonathan Machado
*/

#ifndef __VECTOR3D_HPP__
# define __VECTOR3D_HPP__
# include <iostream>

class Vector3d
    {
    public:
      Vector3d(double x = 0, double y = 0, double z = 0);
      Vector3d(const double *v);
      Vector3d(const Vector3d &v);
      Vector3d& operator= (const Vector3d& v);
      void set(double x, double y, double z);

      double& operator[](int i);
      double operator[](int i) const;

      Vector3d& operator+=(const Vector3d& v);
      Vector3d& operator-=(const Vector3d& v);
      Vector3d& operator*=(double s);
      Vector3d& operator/=(double s);
      Vector3d operator+(const Vector3d& v) const;
      Vector3d operator-(const Vector3d& v) const;
      Vector3d operator*(double s) const;
      Vector3d operator/(double s) const;
      Vector3d operator-() const;
      bool operator==(const Vector3d& v) const;
      bool operator!=(const Vector3d& v) const;

      double length() const;
      double lengthSquared() const;
      void normalize();
      double dot(const Vector3d& v) const;
      Vector3d cross(const Vector3d& v) const;
      double distance(const Vector3d& v) const;
      double distanceSquared(const Vector3d& v) const;

      double	x;
      double	y;
      double	z;
    };

inline std::ostream& operator<< (std::ostream& s, const Vector3d& v)
{
  return s << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

#endif /* __VECTOR3D_HPP__ */

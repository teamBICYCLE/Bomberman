/**************************************************************************
** TexturedCube.hh: Created on 21 May 2012 by duplom_t
** for class : TexturedCube
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef TEXTUREDCUBE_HH
# define TEXTUREDCUBE_HH

# include "AModel.hh"
# include <GL/gl.h>
# include <GL/glut.h>
# include <GDL/Image.hpp>
# include <string>

class TexturedCube : public AModel
{
public:
  TexturedCube(const std::string & imgpath);
  TexturedCube(const AModel & orig);
  virtual ~TexturedCube() {}

public:
  void      draw();
  void      update(gdl::GameClock & clock);
  AModel &  clone();
  void      setBuild();

private:
  GLuint      list_;
  gdl::Image  img_;
  float       coef_;
  float       incValue_;
  float       delay_;
};

#endif // TEXTUREDCUBE_HH

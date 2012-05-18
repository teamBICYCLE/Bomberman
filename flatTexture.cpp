/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return duplom_t
 * ----------------------------------------------------------------------------
 */


#include <GL/gl.h>

#include "flatTexture.hh"
#include <iostream>

flatTexture::flatTexture(const std::string & path) {
  this->tex_ = gdl::Image::load(path);
  std::cout << "texture created" << std::endl;
}

flatTexture::flatTexture(const flatTexture& orig)
: tex_(orig.tex_) {
}

flatTexture::~flatTexture() {
}

void            flatTexture::draw()
{
  double        x = static_cast<double>(tex_.getWidth()),
          y = static_cast<double>(tex_.getHeight());
  
  this->tex_.bind();
  glBegin(GL_QUADS);
  glTexCoord2i(0, 0);
  glVertex2d(0.0f, 0.0f);
  glTexCoord2i(1, 0);
  glVertex2d(x, 0.0f);
  glTexCoord2i(1, 1);
  glVertex2d(x, y);
  glTexCoord2i(0, 1);
  glVertex2d(0.0f, y);
  glEnd();
}

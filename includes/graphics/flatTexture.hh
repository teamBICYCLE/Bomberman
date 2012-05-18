/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return duplom_t
 * ----------------------------------------------------------------------------
 */

#ifndef         FLATTEXTURE_HH
# define	FLATTEXTURE_HH

# include <string>
# include <GDL/Image.hpp>

class flatTexture {
public:
  flatTexture(const std::string & path);
  flatTexture(const flatTexture& orig);
  virtual ~flatTexture();
  
  void          draw();

private:
  gdl::Image    tex_;
};

#endif	/* FLATTEXTURE_HH */


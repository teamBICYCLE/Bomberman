/**************************************************************************
** RotatingImg.hh: Created on 22 May 2012 by duplom_t
** for class : RotatingImg
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef   ROTATINGIMG_HH
# define  ROTATINGIMG_HH

# include   <GDL/Image.hpp>
# include   "AModel.hh"

class RotatingImg : public AModel
{
public:
  RotatingImg(const std::string & imgpath);
  RotatingImg(const AModel & orig);
  virtual ~RotatingImg();

public:
  void      draw();
  void      update(gdl::GameClock & clock);
  AModel &  clone();

private:
  gdl::Image  img_;
  double      angle_;
};

#endif // ROTATINGIMG_HH

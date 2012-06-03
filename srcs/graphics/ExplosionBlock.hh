/**************************************************************************
** ExplosionBlock.hh: Created on 23 May 2012 by duplom_t
** for class : ExplosionBlock
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef EXPLOSIONBLOCK_HH
#define EXPLOSIONBLOCK_HH

#include <GDL/Image.hpp>
#include "AModel.hh"

class ExplosionBlock : public AModel
{
public:
  ExplosionBlock(const std::string & imgpath);
  ExplosionBlock(const AModel & orig);
  virtual ~ExplosionBlock();


public:
  void      draw();
  void      update(gdl::GameClock & clock);
  AModel &  clone();

private:
  gdl::Image  img_;
  int         iter_;
  double      lastTime_;
  double      maxTime_;
};

#endif // EXPLOSIONBLOCK_HH

/**************************************************************************
** Credits.hh: Created on 3 Jun 2012 by duplom_t
** for class : Credits
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef CREDITS_HH
#define CREDITS_HH

#include "AContent.hh"
#include "flatTexture.hh"

class Credits : public AContent
{
public:
  Credits();
  virtual ~Credits();
  virtual void    update(gdl::Input & input, gdl::GameClock & gClock,
                         StatesManager * sMg, CarrouselHandler * cH);
  virtual void    draw(void);

private:
  flatTexture     bg_;
};

#endif // CREDITS_HH

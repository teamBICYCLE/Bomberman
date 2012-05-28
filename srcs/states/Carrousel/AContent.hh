/**************************************************************************
** AContent.hh: Created on 26 May 2012 by duplom_t
** for class : AContent
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef ACONTENT_HH
#define ACONTENT_HH

# include <GDL/GameClock.hpp>
# include <GDL/Input.hpp>
# include "StatesManager.hh"

class AContent
{
public:
  virtual ~AContent();
  virtual void    update(gdl::Input & input, gdl::GameClock & gClock,
                         StatesManager * sMg) = 0;
  virtual void    draw() = 0;
};

#endif // ACONTENT_HH

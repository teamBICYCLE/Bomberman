/**************************************************************************
** Quit.cpp: Created on 18 May 2012 by duplom_t
** for class : Quit
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "Quit.hh"

namespace Menu {

Quit::Quit(const std::string & normalImagePath,
           const std::string & highlightImagePath,
           const Vector3d & pos)
  : MenuLine(normalImagePath, highlightImagePath, pos)
{
}

void    Quit::activate(StatesManager *sMg)
{
  sMg->popState();
}

}

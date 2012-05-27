/**************************************************************************
** QuickStart.cpp: Created on 20 May 2012 by duplom_t
** for class : QuickStart
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "QuickStart.hh"

#include "ClientState.hh"

namespace Menu {

QuickStart::QuickStart(const std::string & normalImagePath,
           const std::string & highlightImagePath,
           const Vector3d & pos)
  : MenuLine(normalImagePath, highlightImagePath, pos)
{
}

void    QuickStart::activate(StatesManager *sMg)
{
  // sMg->pushState(new Bomberman::ClientState("localhost"));
  sMg->pushState(new Bomberman::PlayState());
}

}

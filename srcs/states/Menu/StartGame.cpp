/**************************************************************************
** StartGame.cpp: Created on 18 May 2012 by duplom_t
** for class : StartGame
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "StartGame.hh"

#include "PlayState.hh"
#include "AdventureState.hh"
#include "ServerState.hh"

namespace Menu {
StartGame::StartGame(const std::string & normalImagePath,
                     const std::string & highlightImagePath,
                     const Vector3d & pos)
  : MenuLine(normalImagePath, highlightImagePath, pos)
{
}

void    StartGame::activate(StatesManager *sMg)
{
  //sMg->pushState(new Bomberman::AdventureState());
  // sMg->pushState(new Bomberman::Online::ServerState(2), true);
}

}


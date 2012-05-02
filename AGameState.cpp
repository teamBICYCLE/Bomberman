/**************************************************************************
** AGameState.cpp: Created on 2 May 2012 by duplom_t
** for class :
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "AGameState.hh"

void            AGameState::changeState(StatesManager * mg, AGameState * s)
{
  mg->changeState(s);
}

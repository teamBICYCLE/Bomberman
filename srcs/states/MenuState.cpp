/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return duplom_t
 * ----------------------------------------------------------------------------
 */


#include "MenuState.hh"
#include "MenuEntry.hh"

namespace Bomberman {
MenuState::MenuState() {
}

MenuState::~MenuState()
{
}

bool    MenuState::init()
{
    return true;
}
void    MenuState::cleanUp()
{
}

void    MenuState::update(StatesManager * sMg)
{
  test_.update(sMg->getGameClock(), sMg->getInput(), sMg);
}

void    MenuState::draw(StatesManager *)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 800, 800, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_TEXTURE_2D);
  test_.draw();
}

void    MenuState::pause()
{
}

void    MenuState::resume()
{
}
}

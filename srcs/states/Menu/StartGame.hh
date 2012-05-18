/**************************************************************************
** StartGame.hh: Created on 18 May 2012 by duplom_t
** for class : StartGame
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef STARTGAME_HH
# define STARTGAME_HH

# include "MenuLine.hh"

namespace Menu {
class StartGame : public MenuLine
{
public:
  StartGame(const std::string & normalImagePath,
           const std::string & highlightImagePath,
           const Vector3d & pos = Vector3d(0, 0, 0));

  virtual void      activate(StatesManager * sMg);
};
}

#endif // STARTGAME_HH

/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return duplom_t
 * ----------------------------------------------------------------------------
 */

#ifndef         MENUENTRY_HH
# define	MENUENTRY_HH

# include <vector>
# include <string>
# include <GDL/GameClock.hpp>
# include "AObject.hh"
# include "MenuLine.hh"

namespace Bomberman {  
class MenuEntry {
public:
  MenuEntry();
  virtual ~MenuEntry();

  void                          addEntry(const std::string & name);
  
  virtual void                  update(gdl::GameClock& clock, 
          gdl::Input& keys, StatesManager * sMg);
    virtual void		draw(void);
  private:
    unsigned int                  selected_;
    std::vector<MenuLine>         items_;
};
}

#endif	/* MENUENTRY_HH */


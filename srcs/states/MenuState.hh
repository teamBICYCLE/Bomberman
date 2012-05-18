/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return duplom_t
 * ----------------------------------------------------------------------------
 */

#ifndef         MENUSTATE_HH
# define	MENUSTATE_HH

# include "AGameState.hh"
# include "MenuEntry.hh"

namespace Bomberman {
class MenuState : public AGameState {
public:
  MenuState();
  virtual ~MenuState();
  
  virtual bool init();
  virtual void cleanUp();

  virtual void update(StatesManager *);
  virtual void draw(StatesManager *);
  virtual void pause();
  virtual void resume();
  
private:
  // std::vector<AObject *>         scene_;
  MenuEntry     test_;
  
private:
  MenuState(const MenuState& orig);
};
}

#endif	/* MENUSTATE_HH */


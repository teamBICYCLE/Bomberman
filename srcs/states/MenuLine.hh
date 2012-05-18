/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return duplom_t
 * ----------------------------------------------------------------------------
 */

#ifndef         MENULINE_HH
# define	MENULINE_HH

# include <string>
# include <GDL/GameClock.hpp>
# include "StatesManager.hh"
# include "flatTexture.hh"

namespace Bomberman {
class MenuLine {
public:
  MenuLine(const std::string & name, double offset = 0);
  MenuLine(const MenuLine& orig);
  virtual ~MenuLine();
  
  virtual void          update(gdl::GameClock& clock, bool highlight);
  virtual void          draw(void);
  void                  activate(StatesManager * sMg);
  
private:
  std::string           name_;
  bool                  highlighted_;
  flatTexture           image_;
  double                offset_;
  
};
}

#endif	/* MENULINE_HH */


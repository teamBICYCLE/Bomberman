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
# include "Vector3d.hh"

namespace Menu {
class MenuLine {
public:
  MenuLine(const std::string & normalImagePath,
           const std::string & highlightImagePath,
           const Vector3d & pos);
  MenuLine(const MenuLine& orig);
  virtual ~MenuLine();

  void              update(gdl::GameClock& clock, bool highlight);
  void              draw(void);
  virtual void      activate(StatesManager * sMg) = 0;

private:
  bool                  highlighted_;
  flatTexture           normal_;
  flatTexture           highlight_;
  Vector3d              pos_;
};
}

#endif	/* MENULINE_HH */


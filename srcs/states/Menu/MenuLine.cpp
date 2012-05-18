/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return duplom_t
 * ----------------------------------------------------------------------------
 */

#include <iostream>

#include <GL/gl.h>

#include "MenuLine.hh"
#include "PlayState.hh"


namespace Menu {
  MenuLine::MenuLine(const std::string & normalImagePath,
           const std::string & highlightImagePath,
           const Vector3d & pos)
    : highlighted_(false), normal_(normalImagePath),
      highlight_(highlightImagePath), pos_(pos)
{
}

MenuLine::MenuLine(const MenuLine& orig) :
highlighted_(orig.highlighted_), normal_(orig.normal_),
  highlight_(orig.highlight_), pos_(orig.pos_)
{
}

MenuLine::~MenuLine() {
}

void            MenuLine::update(gdl::GameClock& clock, bool highlight)
{
  (void)clock;
  highlighted_ = highlight;
}

void            MenuLine::draw()
{
  glPushMatrix();
  glTranslated(pos_.x, pos_.y, 0);
  if (highlighted_)
    highlight_.draw();
  else
    normal_.draw();
  glPopMatrix();
}

}

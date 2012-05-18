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


namespace Bomberman {
MenuLine::MenuLine(const std::string & name, double offset) 
: name_(name), highlighted_(false), image_("Ressources/Images/Menu/" + name + ".png"),
offset_(offset) {
}

MenuLine::MenuLine(const MenuLine& orig) :
name_(orig.name_), highlighted_(orig.highlighted_), image_(orig.image_),
offset_(orig.offset_) {
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
  if (highlighted_)
    glScaled(1.1f, 1.1f, 1.1f);
  glTranslated(0, offset_, 0);
  image_.draw();
  glPopMatrix();
}

void            MenuLine::activate(StatesManager * sMg)
{
  sMg->pushState(new Bomberman::PlayState());
  std::cout << "clicked" << std::endl;
}

}
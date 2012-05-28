/**************************************************************************
** APage.hh: Created on 25 May 2012 by duplom_t
** for class : APage
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef APAGE_HH
# define APAGE_HH

# include <GDL/Input.hpp>
# include <GDL/GameClock.hpp>
# include <GDL/Image.hpp>
# include "StatesManager.hh"
# include "flatTexture.hh"
# include "AContent.hh"

class APage
{
public:
  APage(AContent * content, const std::string & background,
        const std::string & leftImg, const std::string & rightImg);
  virtual ~APage();

  virtual void  update(gdl::Input & input, gdl::GameClock &gClock,
                       StatesManager * sMg);
  virtual void  draw();
  virtual void  drawLeft();
  virtual void  drawRight();

private:
  AContent *    content_;
  flatTexture   background_;
  flatTexture   leftImg_;
  flatTexture   rightImg_;
};

#endif // APAGE_HH

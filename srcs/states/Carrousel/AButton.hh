/**************************************************************************
** AButton.hh: Created on 26 May 2012 by duplom_t
** for class : AButton
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef ABUTTON_HH
#define ABUTTON_HH

# include "Vector3d.hh"
# include "flatTexture.hh"
# include "StatesManager.hh"

class AButton
{
public:
  AButton(const std::string & normal, const std::string & hightlight,
          const Vector3d & pos);
  virtual ~AButton();

  void          update();
  void          draw();
  void          drawHighlight();
  virtual void  activate(StatesManager * sMg) = 0;

private:
  flatTexture   normal_;
  flatTexture   hightlight_;
  Vector3d      pos_;
};

#endif // ABUTTON_HH

/**************************************************************************
** CarrouselHandler.hh: Created on 25 May 2012 by duplom_t
** for class : CarrouselHandler
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef   CARROUSELHANDLER_HH
# define  CARROUSELHANDLER_HH

# include <vector>
# include <GL/gl.h>
# include "AGameState.hh"
# include "APage.hh"

class CarrouselHandler : public AGameState
{
public:
  CarrouselHandler(const std::string &bg, const std::string & music = "");
  CarrouselHandler(GLvoid * data, const std::string & music = "");
  virtual ~CarrouselHandler();

  void          pushPage(APage *);

  virtual bool init();
  virtual void cleanUp();
  virtual void update(StatesManager *, double delta = -1);
  virtual void draw(StatesManager *);
  virtual void pause();
  virtual void resume();

  void        setArrowFocus(bool val);
  void        setArrowFocusLeft(bool val);
  void        setArrowFocusRight(bool val);
  void        setEscapeFocus(bool val);
  bool        getArrowFocusLeft() const;
  bool        getArrowFocusRight() const;
  bool        getEscapeFocus() const;

  void          drawPreviousPreview();
  void          drawNextPreview();

  void          createMainMenu();
  void          createInGameMenu();


  CarrouselHandler &      operator++();
  CarrouselHandler &      operator--();

private:
  std::vector<APage *>   pages_;
  int                    activ_;
  bool                   leftPressed_;
  bool                   rightPressed_;
  bool                   escPressed_;
  bool                    arrowsFocusLeft_;
  bool                    arrowsFocusRight_;
  bool                    escFocus_;
  flatTexture             bg_;
  GLvoid                  *data_;
  bool                    imgBg_;
  gdl::Image              overlay_;
  float                   offset_;
  std::string             music_;
};

#endif // CARROUSELHANDLER_HH

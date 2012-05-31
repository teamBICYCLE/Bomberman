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
# include "AGameState.hh"
# include "APage.hh"

class CarrouselHandler : public AGameState
{
public:
  CarrouselHandler();
  virtual ~CarrouselHandler();

  void          pushPage(APage *);

  virtual bool init();
  virtual void cleanUp();
  virtual void update(StatesManager *);
  virtual void draw(StatesManager *);
  virtual void pause();
  virtual void resume();

  void        setArrowFocus(bool val);
  void        setArrowFocusLeft(bool val);
  void        setArrowFocusRight(bool val);
  bool        getArrowFocusLeft() const;
  bool        getArrowFocusRight() const;

  void          drawPreviousPreview();
  void          drawNextPreview();


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
};

#endif // CARROUSELHANDLER_HH

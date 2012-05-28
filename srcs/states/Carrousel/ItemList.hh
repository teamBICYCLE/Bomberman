/**************************************************************************
** ItemList.hh: Created on 26 May 2012 by duplom_t
** for class : ItemList
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef ITEMLIST_HH
#define ITEMLIST_HH

# include <vector>
# include "AContent.hh"
# include "AButton.hh"

class ItemList : public AContent
{
public:
  ItemList();
  virtual ~ItemList();

  void          pushButton(AButton * button);
  virtual void  update(gdl::Input &input,
                       gdl::GameClock &gClock,
                       StatesManager *sMg);
  virtual void  draw();

private:
  unsigned int              current_;
  std::vector<AButton *>    items_;
  bool                      upPressed_;
  bool                      downPressed_;
};

#endif // ITEMLIST_HH

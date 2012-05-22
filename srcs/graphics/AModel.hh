/**************************************************************************
** AModel.hh: Created on 21 May 2012 by duplom_t
** for class : Model
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef   AMODEL_HH
# define  AMODEL_HH

# include <GDL/GameClock.hpp>

class AModel
{
public:
  AModel();
  virtual ~AModel() {}

public:
  virtual void        update(gdl::GameClock& clock) = 0;
  virtual void        draw() = 0;
  virtual AModel &    clone() = 0;
};

#endif // AMODEL_HH

/**************************************************************************
** gdlModel.hh: Created on 21 May 2012 by duplom_t
** for class : gdlModel
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef GDLMODEL_HH
#define GDLMODEL_HH

# include "AModel.hh"
# include <GDL/Model.hpp>

class gdlModel : public AModel
{
public:
  gdlModel(const std::string & path = "");
  gdlModel(const  AModel & orig);
  virtual ~gdlModel() {}

public:
  virtual void      draw();
  virtual void      update(gdl::GameClock & clock);
  virtual AModel &  clone();
  gdl::Model &      getModel();

private:
 gdl::Model         model_;
 const std::string  path_;
};

#endif // GDLMODEL_HH

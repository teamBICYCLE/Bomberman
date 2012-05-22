/*
 * File:   ModelHandler.hh
 * Author: duplom_t
 *
 * Created on May 16, 2012, 12:54 AM
 */

#ifndef         MODELHANDLER_HH
# define	MODELHANDLER_HH

# include <map>
# include <string>
# include "AModel.hh"

namespace Bomberman
{
class ModelHandler {
public:
  ~ModelHandler();

  void          storeModel(AModel * model, const std::string & name);
  AModel &      getModel(const std::string & name);
  static ModelHandler& get();

private:
  std::map<std::string, AModel*>        objects_;

private:
  ModelHandler();
  ModelHandler(const ModelHandler& orig);
  ModelHandler &              operator=(const ModelHandler &);
  static ModelHandler         self_;
};
}
#endif	/* MODELHANDLER_HH */


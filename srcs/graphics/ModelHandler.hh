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
# include "AObject.hh"

namespace Bomberman
{
class ModelHandler {
public:
  ModelHandler();
  ~ModelHandler();
  
  bool          loadModel(const std::string & path, const std::string & name);
  
private:
  std::map<std::string, AObject*>        objects_;
  
private:
  ModelHandler(const ModelHandler& orig);
  ModelHandler &        operator=(const ModelHandler &);
};
}
#endif	/* MODELHANDLER_HH */


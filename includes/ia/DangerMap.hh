//
// DangerMap.hh for  in /home/carpen_t/projets/c++/Bomberman
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Wed May 16 14:50:57 2012 thibault carpentier
// Last update Wed May 16 15:00:41 2012 thibault carpentier
//

#ifndef _DANGERMAP_H_
# define _DANGERMAP_H_

# include <list>
# include "AObject.hh"

using namespace Bomberman;

namespace Bomberman
{
  namespace Thinking
  {
    class DangerMap
    {
    private:
      DangerMap(DangerMap const &);
      DangerMap& operator=(DangerMap const &);

    public:
      DangerMap(std::list<AObject*> map);
      ~DangerMap(void);
    };
  }
}
#endif /*!_DANGERMAP_H_*/

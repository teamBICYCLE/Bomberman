//
// DangerMap.hh for  in /home/carpen_t/projets/c++/Bomberman
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May 18 14:30:13 2012 thibault carpentier
// Last update Fri May 18 17:55:56 2012 Jonathan Machado
//

#ifndef _DANGERMAP_H_
# define _DANGERMAP_H_
# include <list>
# include <utility>
# include <vector>
# include "AObject.hh"

namespace Bomberman
{
  class DangerMap
  {

  private:
    DangerMap(DangerMap const &);
    DangerMap& operator=(DangerMap const &);

    std::vector<std::vector<std::pair<int, int> > > danger_;
    int x_, y_;

  public:
    DangerMap(int, int);
    ~DangerMap(void);
  };
}

#endif /*!_DANGERMAP_H_*/

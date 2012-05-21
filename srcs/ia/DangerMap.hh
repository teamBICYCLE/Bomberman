//
// DangerMap.hh for  in /home/carpen_t/projets/c++/Bomberman
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May 18 14:30:13 2012 thibault carpentier
// Last update Mon May 21 09:43:29 2012 thibault carpentier
//

#ifndef _DANGERMAP_H_
# define _DANGERMAP_H_

# include <map>
# include <list>
# include <utility>
# include <vector>
# include "AObject.hh"

namespace Bomberman
{
  class DangerMap
  {
    typedef int (Bomberman::DangerMap::*fctMeth)(const std::list<AObject*>::const_iterator &);

  private:
    DangerMap(DangerMap const &);
    DangerMap& operator=(DangerMap const &);

    void resetDanger(void);
    int updateDanger(const std::list<AObject *>::const_iterator &it);
    void updateCaseVison(const std::list<AObject *>::const_iterator &it, int x, int y);

    int powerupDanger(const std::list<AObject *>::const_iterator &it);
    int mineDanger(const std::list<AObject*>::const_iterator &it);
    int explosionDanger(const std::list<AObject*>::const_iterator &it);
    int playerDanger(const std::list<AObject*>::const_iterator &it);
    int monsterDanger(const std::list<AObject*>::const_iterator &it);
    int blockDanger(const std::list<AObject*>::const_iterator &it);
    int bomberDanger(const std::list<AObject*>::const_iterator &it);

    std::vector<std::vector<std::pair<int, int> > > danger_;
    int x_, y_;
    std::list<AObject*> objs_;
    std::map<std::string, fctMeth> dangerMeth_;

  public:
    DangerMap(int, int);
    ~DangerMap(void);

    void updateGameVision(const std::list<AObject*>&objs);
  };
}

#endif /*!_DANGERMAP_H_*/

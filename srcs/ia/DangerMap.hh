//
// DangerMap.hh for  in /home/carpen_t/projets/c++/Bomberman
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May 18 14:30:13 2012 thibault carpentier
// Last update Sat May 26 16:38:49 2012 thibault carpentier
//

#ifndef _DANGERMAP_H_
# define _DANGERMAP_H_

# include <map>
# include <list>
# include <utility>
# include <vector>
# include "AObject.hh"
# include "Bomb.hh"

namespace Bomberman
{
  class DangerMap
  {
    typedef void (Bomberman::DangerMap::*fctMeth)(const std::list<AObject*>::const_iterator &, int, int);

  private:
    DangerMap(DangerMap const &);
    DangerMap& operator=(DangerMap const &);

    void resetDanger(void);
    void setDanger(int x, int y, int danger);
    void updateDanger(const std::list<AObject *>::const_iterator &it, int x, int y);
    void updateCaseVison(const std::list<AObject *>::const_iterator &it, int x, int y);

    // void powerupDanger(const std::list<AObject *>::const_iterator &it, int x, int y);
    // void mineDanger(const std::list<AObject*>::const_iterator &it, int x, int y);
    // void explosionDanger(const std::list<AObject*>::const_iterator &it, int x, int y);
    // void playerDanger(const std::list<AObject*>::const_iterator &it, int x, int y);
    // void monsterDanger(const std::list<AObject*>::const_iterator &it, int x, int y);
    // void blockDanger(const std::list<AObject*>::const_iterator &it, int x, int y);
    // void bomberDanger(const std::list<AObject*>::const_iterator &it, int x, int y);

    void setRangeDanger(int range, int x, int y, int danger);
    Bomb *isPosValid(bool &valid, int x, int y);

    std::vector<std::vector<std::pair<int, int> > > danger_;
    std::list<AObject*> objs_;
    std::map<std::string, fctMeth> dangerMeth_;

  public:
    DangerMap(int, int);
    ~DangerMap(void);

    int x_, y_;
    std::list<AObject*> getObjs(void) const;
    void updateGameVision(const std::list<AObject*>&objs);
    int getDanger(int x, int y) const;
  };
}

#endif /*!_DANGERMAP_H_*/

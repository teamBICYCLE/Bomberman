//
// Map.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May  4 15:29:12 2012 lois burg
// Last update Fri May  4 15:33:24 2012 lois burg
//

#ifndef		__MAPMANAGER_HH__
# define	__MAPMANAGER_HH__

# include	"AObject.hh"
# include   "Block.hh"
# include   "Brick.hh"

namespace	Bomberman
{
  class	Map
  {

  public:
    Map(void);
    Map(const std::string& fileName);
    ~Map(void);

  public:
    void getFromFile(const std::string& fileName);
    bool checkType(char c) const;
    AObject *createType(char c, unsigned int x, unsigned int y) const;
    const std::vector<AObject*>&	getTerrain(void) const;

  private:
    std::vector<AObject*>	terrain_;
  };
}

#endif /* !__MAPMANAGER_HH__*/

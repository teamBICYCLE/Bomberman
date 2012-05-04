//
// Map.hh for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Fri May  4 18:29:27 2012 geoffroy lafontaine
// Last update Fri May  4 18:29:28 2012 geoffroy lafontaine
//

#ifndef		__MAPMANAGER_HH__
# define	__MAPMANAGER_HH__

# include	<ostream>
# include	"AObject.hh"
# include   "Block.hh"
# include   "Brick.hh"

namespace	Bomberman
{
  class	Map
  {

  public:
    Map(unsigned int width = 13, unsigned int height = 13, unsigned int nbPlayers = 1);
    Map(const std::string& fileName);
    ~Map(void);

  public:
    void                            getFromFile(const std::string& fileName);
    bool                            checkType(char c) const;
    AObject                         *createType(char c, unsigned int x, unsigned int y) const;
    const std::vector<AObject*>&	getTerrain(void) const;
    void                            addPlayers(unsigned int, unsigned int, unsigned int);
    void                            generateBricks(unsigned int, unsigned int, unsigned int);

  private:
    std::vector<AObject*>	terrain_;
  };
}

#endif /* !__MAPMANAGER_HH__*/

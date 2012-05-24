//
// Map.hh for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Fri May  4 18:29:27 2012 geoffroy lafontaine
// Last update Tue May 22 13:27:58 2012 geoffroy lafontaine
//

#ifndef		__MAPMANAGER_HH__
# define	__MAPMANAGER_HH__

# include	<ostream>
# include	<stdexcept>
# include	<sys/types.h>
# include	"AObject.hh"
# include	"Block.hh"
# include	"Brick.hh"
# include	"Player.hh"
# include	"Monster.hh"
# include	"Ghost.hh"

# define	MAP_FILE_EMPTY          '.'
# define	MAP_FILE_BLOCK          'W'
# define	MAP_FILE_BRICK          'B'
# define	MAP_FILE_PLAYER         'P'
# define	MAP_FILE_MONSTER        'M'
# define	MAP_FILE_GHOST          'G'
# define	MAP_FILE_FIREBLOCK_UP	'U'
# define	MAP_FILE_FIREBLOCK_DOWN	'D'
# define	MAP_FILE_FIREBLOCK_LEFT	'L'
# define	MAP_FILE_FIREBLOCK_RIGT	'R'
# define	MAP_FILE_ALLOWED        ".WBPMGUDLR"

namespace	Bomberman
{
  class	Map
  {
  public:
    class	Failure : public std::runtime_error
    {
    public:
      Failure(const std::string& func, const std::string& msg) throw();
      Failure(const Failure&) throw();
      Failure& operator=(const Failure&) throw();
      virtual ~Failure() throw();

    public:
      std::string		getFunc(void) const throw();
      std::string		getMsg(void) const throw();

    public:
      virtual const char*	what() const throw();

    private:
      std::string		mFunc;
      std::string		mMsg;
    };

  public:
    Map(uint width = 13, uint height = 13,
	uint nbPlayers = 1, uint nbMonsters = 5, uint nbGhosts = 0);
    Map(const std::string& fileName);
    ~Map(void);

  public:
    const std::list<AObject*>&	getTerrain(void) const;

  public:
    static const int		BlockSize;

  protected:
    void    setFromFile(std::list<std::string> &map);
    void    mapFileIsValid(std::list<std::string> &map) const;
    void    getFromFile(const std::string&);
    void    addBlocks(const std::string &, int, std::list<AObject*> *);
    void    addBricks(const std::string &, int, std::list<AObject*> *);
    void    addGhosts(const std::string &, int, std::list<AObject*> *, Thinking::Brain *);
    void    addMonsters(const std::string &, int, std::list<AObject*> *, Thinking::Brain *);
    void    addPlayers(std::list<std::string> &map);

  protected:
    void	generatePlayers(void);
    void	generateBricks(void);
    void	generateBorder(void);
    void	generateMonsters(uint);
    void	generateGhosts(uint);
    void	placePlayer(uint, uint);
    void	placeMonster(uint, uint, Thinking::Brain *);
    void	placeGhost(uint, uint, Thinking::Brain *);
    void	clearPlace(uint, uint);

  public:
    uint    getWidth(void) const;
    uint    getHeight(void) const;
    uint    getNbPlayers(void) const;
    uint    getNbMonsters(void) const;
    uint    getNbGhosts(void) const;

  private:
    std::list<AObject*>	terrain_;
    uint                width_;
    uint                height_;
    uint		nbPlayers_;
    uint		nbMonsters_;
    uint		nbGhosts_;
  };
}

#endif /* !__MAPMANAGER_HH__*/

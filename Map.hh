//
// Map.hh for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Fri May  4 18:29:27 2012 geoffroy lafontaine
// Last update Tue May  8 15:06:29 2012 geoffroy lafontaine
//

#ifndef		__MAPMANAGER_HH__
# define	__MAPMANAGER_HH__

# include	<ostream>
# include	<stdexcept>
# include	"AObject.hh"
# include	"Block.hh"
# include	"Brick.hh"

# define	MAP_FILE_EMPTY		'.'
# define	MAP_FILE_BLOCK		'W'
# define	MAP_FILE_BRICK		'B'
# define	MAP_FILE_PLAYER		'J'
# define	MAP_FILE_ALLOWED	".WBJ"

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
    Map(unsigned int width = 13, unsigned int height = 13,
	unsigned int nbPlayers = 1);
    Map(const std::string& fileName);
    ~Map(void);

  public:
    const std::vector<AObject*>&	getTerrain(void) const;

  protected:
    void	getFromFile(const std::string& fileName);
    bool	checkType(char c) const;
    AObject	*createType(char, unsigned int, unsigned int, bool *) const;
    void	addPlayers(unsigned int, unsigned int, unsigned int);
    void	generateBricks(unsigned int, unsigned int, unsigned int);
    void	clearPlace(unsigned int, unsigned int);

  private:
    std::vector<AObject*>	terrain_;
  };
}

#endif /* !__MAPMANAGER_HH__*/

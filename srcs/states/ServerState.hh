//
// ServerState.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Tue May 22 17:52:44 2012 lois burg
// Last update Fri Jun  1 11:22:54 2012 lois burg
//

#ifndef		__SERVERSTATE_HH__
# define	__SERVERSTATE_HH__

# include	<vector>
# include	"PracticalSocket.h"
# include	"AObject.hh"
# include	"Map.hh"
# include	"PlayState.hh"
# include	"Select.hh"

namespace	Bomberman
{
  namespace	Online
  {
    class	ServerState : public PlayState
    {
    public:
      ServerState(int mapWidth, int mapHeight, uint nbPlayers, TCPServerSocket*& serv, std::vector<TCPSocket*>& clients);
      virtual ~ServerState();

    public:
      virtual bool init();
      virtual void cleanUp();

      virtual void update(StatesManager *mngr);

      // virtual void win(StatesManager *mngr);
      // virtual void gameOver(StatesManager *mngr);
      virtual void checkEndGame(StatesManager *mngr, int nbPlayers, int nbMonsters);

    private:
      int			nbPlayers_;
      TCPServerSocket*&		serv_;
      std::vector<TCPSocket*>&	clients_;
      Select			select_;
    };
  }
}

#endif /* !__SERVERSTATE_HH__*/

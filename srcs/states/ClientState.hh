//
// ClientState.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Tue May 22 17:52:44 2012 lois burg
// Last update Sat May 26 16:18:49 2012 lois burg
//

#ifndef		__CLIENTSTATE_HH__
# define	__CLIENTSTATE_HH__

# include	<vector>
# include	"PracticalSocket.h"
# include	"AObject.hh"
# include	"Map.hh"
# include	"PlayState.hh"
# include	"Select.hh"

namespace	Bomberman
{
    namespace Online
    {
      class	ClientState : public PlayState
      {
      public:
        ClientState(const std::string& host);
        virtual ~ClientState();

      public:
        virtual bool init();
        virtual void cleanUp();

        virtual void update(StatesManager *mngr);

        virtual void win(StatesManager *mngr);
        virtual void gameOver(StatesManager *mngr);

      private:
        std::string		host_;
        int             playerNbr_;
        TCPSocket		*serv_;
        Select          select_;
        bool            disconnected_;
      };
    }
}

#endif /* !__CLIENTSTATE_HH__*/

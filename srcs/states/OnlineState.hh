//
// OnlineState.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Tue May 22 17:52:44 2012 lois burg
// Last update Tue May 22 17:58:10 2012 lois burg
//

#ifndef		__ONLINESTATE_HH__
# define	__ONLINESTATE_HH__

# include	<QTcpServer>
# include	"AObject.hh"
# include	"Map.hh"
# include	"PlayState.hh"

namespace	Bomberman
{
  class	OnlineState : public PlayState
  {
  public:
    OnlineState(uint nbPlayers, const std::string& host = "");
    virtual ~OnlineState();

  public:
    virtual bool init();
    virtual void cleanUp();

    virtual void win(StatesManager *mngr);
    virtual void gameOver(StatesManager *mngr);

  private:
    uint	nbPlayers_;
    QTcpServer	*serv_;
  };
}
#endif /* !__ONLINESTATE_HH__*/

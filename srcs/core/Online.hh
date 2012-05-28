//
// Online.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Sat May 26 16:26:23 2012 lois burg
// Last update Sun May 27 15:15:44 2012 lois burg
//

#ifndef		__ONLINE_HH__
# define	__ONLINE_HH__

# include	<iostream>
# include	<list>
# include	"AObject.hh"
# include	"Player.hh"
# include	"PracticalSocket.h"

namespace	Bomberman
{
  namespace	Online
  {
    const std::string	Disconnected = "[__DISCONNECTED__]";
    const in_port_t	ServPort = 24542;

    Player	*getPlayerWithId(const std::list<AObject*>& objs, int id);
    void	sendPacket(std::iostream& sockStream, const Packet& p);
    Packet	recvPacket(std::iostream& sockStream, bool& disconnected);
    void	updatePlayerWithId(const std::list<AObject*>& objs, int id, const Packet& p);
    void	forwardPacket(std::vector<TCPSocket*>& clients, int senderSockDesc, const Packet& p);
  }
}

#endif /* !__ONLINE_HH__*/

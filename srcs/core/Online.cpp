//
// Online.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Sat May 26 16:28:00 2012 lois burg
// Last update Tue May 29 10:53:27 2012 lois burg
//

#include <utility>
#include <algorithm>
#include "PracticalSocket.h"
#include "Packet.hh"
#include "Online.hh"

using namespace Bomberman;
using namespace Online;

Player	*Bomberman::Online::getPlayerWithId(const std::list<AObject*>& objs, int id)
{
  std::list<AObject*>::const_iterator it;

  for (it = objs.begin(); it != objs.end(); ++it)
    if (dynamic_cast<Player*>(*it) && static_cast<Player*>(*it)->getId() == id)
      return (static_cast<Player*>(*it));
  return (NULL);
}

void	Bomberman::Online::sendPacket(std::iostream& sockStream, const Packet& p)
{
  try {
    sockStream << Packet::serialize(p);
    sockStream.flush();
  } catch (SocketException& e) {
    std::cerr << "sendPacket network error: " << e.what() << std::endl;
  }
}

Packet	Bomberman::Online::recvPacket(std::iostream& sockStream, bool& disconnected)
{
  Packet	p;
  std::string	pkt = Online::Disconnected;
  std::string::iterator it;

  try {
    sockStream >> pkt;
    if (pkt == Online::Disconnected)
      disconnected = true;
    else
      {
	while ((it = std::find(pkt.begin(), pkt.end(), '-')) != pkt.end())
	  (*it) = ' ';
	p = Packet::unserialize(pkt);
      }
  } catch (SocketException& e) {
    std::cerr << "recvPacket network error: " << e.what() << std::endl;
  }
  return (p);
}

void	Bomberman::Online::updatePlayerWithId(std::list<AObject*>& objs, int id, const Packet& p, gdl::GameClock& clock, gdl::Input& keys)
{
  Player	*plyr;

  if ((plyr = getPlayerWithId(objs, id)))
    plyr->applyPacket(p, clock, keys, objs);
}

void	Bomberman::Online::forwardPacket(std::vector<TCPSocket*>& clients, int senderSockDesc, const Packet& p)
{
  std::for_each(clients.begin(), clients.end(), [senderSockDesc, p] (TCPSocket *s) -> void {
      if (s && s->getSockDesc() != senderSockDesc)
	sendPacket(s->getStream(), p);
    });
}

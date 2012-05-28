//
// Packet.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Sat May 26 12:00:22 2012 lois burg
// Last update Sat May 26 18:43:59 2012 lois burg
//

#include <sstream>
#include "Packet.hh"

using namespace	Bomberman;
using namespace	Online;

Packet::Packet()
  : type(UndefPkt), id(-1), x(0), y(0), z(0)
{
}

std::string	Packet::serialize(const Packet& p)
{
  std::stringstream ss;

  ss << p.type << "-" << p.id << "-" << p.x << "-" << p.y << "-" << p.z << std::endl;
  return (ss.str());
}

Packet		Packet::unserialize(const std::string& s)
{
  Packet	p;
  int		type;
  std::stringstream ss;

  ss << s;
  ss >> type;
  p.type = static_cast<PacketType>(type);
  ss >> p.id;
  ss >> p.x;
  ss >> p.y;
  ss >> p.z;
  return (p);
}

bool	Packet::operator==(const Packet& other)
{
  return ((type == other.type) && (id == other.id) &&
	  (x == other.x) && (y == other.y) && (z == other.z));
}

bool	Packet::operator!=(const Packet& other)
{
  return (!operator==(other));
}

std::ostream&	Bomberman::Online::operator<<(std::ostream& os, const Packet& p)
{
  os << "\tType: " << p.type << "\n\tPlayer id: " << p.id << "\n\tX: " << p.x << "\n\tY: " << p.y << "\n\tZ: " << p.z;
  return (os);
}

//
// Packet.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Sat May 26 12:00:22 2012 lois burg
// Last update Tue May 29 11:15:08 2012 lois burg
//

#include <sstream>
#include "Packet.hh"

using namespace	Bomberman;
using namespace	Online;

Packet::Packet()
  : id(-1), up(false), down(false), left(false),
    right(false), bomb(false), mine(false)
{
}

bool	Packet::isUseful(void) const
{
  return (up || down || left ||
	  right || bomb || mine);
}

std::string	Packet::serialize(const Packet& p)
{
  std::stringstream ss;

  ss << p.id << "-" << p.up << "-" << p.down << "-" << p.left << "-" << p.right << "-" << p.bomb << "-" << p.mine << std::endl;
  return (ss.str());
}

Packet		Packet::unserialize(const std::string& s)
{
  Packet	p;
  std::stringstream ss;

  ss << s;
  ss >> p.id;
  ss >> p.up;
  ss >> p.down;
  ss >> p.left;
  ss >> p.right;
  ss >> p.bomb;
  ss >> p.mine;
  return (p);
}

bool	Packet::operator==(const Packet& other)
{
  return ((id == other.id) && (up == other.up) && (down == other.down) &&
	  (left == other.left) && (right == other.right) && (bomb == other.bomb) && (mine == other.mine));
}

bool	Packet::operator!=(const Packet& other)
{
  return (!operator==(other));
}

std::ostream&	Bomberman::Online::operator<<(std::ostream& os, const Packet& p)
{
  os << "\tPlayer id: " << p.id << std::boolalpha << "\n\tUp: " << p.up << "\n\tDown: " << p.down << "\n\tLeft: " << p.left << "\n\tRight: " << p.right << "\n\tBomb: " << p.bomb << "\n\tMine: " << p.mine;
  return (os);
}

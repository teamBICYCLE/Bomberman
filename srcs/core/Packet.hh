//
// Packet.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Sat May 26 11:59:16 2012 lois burg
// Last update Mon May 28 16:45:56 2012 lois burg
//

#ifndef		__PACKET_HH__
# define	__PACKET_HH__

# include	<ostream>
# include	<string>

namespace	Bomberman
{
  namespace	Online
  {
    enum	PacketType
      {
	UndefPkt,
	BombPkt,
	PlayerPkt
      };

    struct	Packet
    {
      Packet();

      PacketType type;
      int	id;
      double	x;
      double	y;
      double	z;

      bool	up;
      bool	down;
      bool	left;
      bool	right;
      bool	bomb;
      bool	mine;

      static std::string	serialize(const Packet& p);
      static Packet		unserialize(const std::string& s);
      bool			isUseful(void) const;

      bool	operator==(const Packet& other);
      bool	operator!=(const Packet& other);
    };

    std::ostream&	operator<<(std::ostream& os, const Packet& p);
  }
}

#endif /* !__PACKET_HH__*/

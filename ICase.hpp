//
// ICase.hpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 14:04:13 2012 lois burg
// Last update Wed May  2 14:25:46 2012 lois burg
//

#ifndef		__ICASE_HPP__
# define	__ICASE_HPP__

namespace Bomberman
{
  class	ICase
  {
  public:
    virtual ~ICase() {}

  public:
    enum	CaseType
      {
	BOMB = 0,
	POWERUP,
	BLOCK
      };

  public:
    virtual void	morph();
  };
}
#endif /* !__ICASE_HPP__*/

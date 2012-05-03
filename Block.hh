//
// Block.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:02:52 2012 lois burg
// Last update Thu May  3 15:31:59 2012 lois burg
//

#ifndef		__BLOCK_HH__
# define	__BLOCK_HH__

# include	"AObject.hh"

namespace	Bomberman
{
  class	Block : public AObject
  {
  public:
    Block(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
    virtual ~Block();

  public:
    virtual void		update(const gdl::GameClock& clock, const gdl::Input& keys);
    virtual void		draw(void);
    virtual const std::string&	type(void) const;
  };
}
#endif /* !__BLOCK_HH__*/

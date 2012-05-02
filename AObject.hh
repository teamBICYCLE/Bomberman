//
// AObject.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:30:16 2012 lois burg
// Last update Wed May  2 18:43:45 2012 lois burg
//

#ifndef		__AOBJECT_HH__
# define	__AOBJECT_HH__

# include	<GDL/GameClock.hpp>
# include	<GDL/Input.hpp>

class	AObject
{
public:
  AObject(void);
  //AObject(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz);
  virtual ~AObject(void);

public:
  virtual void	update(const gdl::GameClock& clock, const gdl::Input& keys) = 0;
  virtual void	draw(void) = 0;

private:
  //Vector3d	pos_;
  //Vector3d	rot_;
  //Vector3d	sz_;
};

#endif /* !__AOBJECT_HH__*/

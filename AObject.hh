//
// AObject.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:30:16 2012 lois burg
// Last update Thu May  3 12:21:43 2012 lois burg
//

#ifndef		__AOBJECT_HH__
# define	__AOBJECT_HH__

# include	<GDL/GameClock.hpp>
# include	<GDL/Input.hpp>
# include	<GDL/Model.hpp>
# include	<string>

namespace	Bomberman
{
  class	AObject
  {
  public:
    AObject(const std::string& modelName);
    //AObject(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& modelName);
    virtual ~AObject(void);

  public:
    virtual void		update(const gdl::GameClock& clock, const gdl::Input& keys) = 0;
    virtual void		draw(void) = 0;
    virtual const std::string&	type(void) const = 0;

  private:
    AObject(const AObject& other);
    AObject& operator=(const AObject& other);

  protected:
    //Vector3d		pos_;
    //Vector3d		rot_;
    //Vector3d		sz_;
    gdl::Model		model_;
    const std::string	type_;
  };
}
#endif /* !__AOBJECT_HH__*/

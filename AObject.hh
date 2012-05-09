//
// AObject.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:30:16 2012 lois burg
// Last update Wed May  9 17:33:58 2012 Jonathan Machado
//

#ifndef		__AOBJECT_HH__
# define	__AOBJECT_HH__

# include	<GDL/GameClock.hpp>
# include	<GDL/Input.hpp>
# include	<GDL/Model.hpp>
# include	<string>
# include	"Vector3d.hh"

namespace	Bomberman
{
  class	AObject
  {
  public:
    AObject(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& modelName);
    virtual ~AObject(void);

  public:
    virtual void		update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs) = 0;
    virtual void		draw(void) = 0;
    virtual const std::string&	type(void) const = 0;
    virtual void		setPos(const Vector3d &);
    virtual void		setRot(const Vector3d &);
    virtual void		setSize(const Vector3d &);

    virtual const Vector3d&	getPos(void) const;
    virtual const Vector3d&	getRot(void) const;
    virtual const Vector3d&	getSize(void) const;
    virtual const std::string&	getType(void) ;

  private:
    AObject(const AObject& other);
    AObject& operator=(const AObject& other);

  protected:
    Vector3d		pos_;
    Vector3d		rot_;
    Vector3d		sz_;
    gdl::Model  	model_;
    const std::string	type_;
  };
}
#endif /* !__AOBJECT_HH__*/

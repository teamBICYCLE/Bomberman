//
// BoundingBox.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 15:02:09 2012 lois burg
// Last update Mon May 21 16:45:49 2012 Jonathan Machado
//

#ifndef		__BOUNDING_BOX_HH__
# define	__BOUNDING_BOX_HH__

# include	<QDataStream>
# include	"AObject.hh"
# include	"Vector3d.hh"

namespace	Bomberman
{
  class	BoundingBox
  {
  public:
    BoundingBox(const Vector3d& pos, const Vector3d& sz, const AObject *owner);
    BoundingBox(const BoundingBox &other, const AObject *owner);
    virtual ~BoundingBox();

  public:
    virtual bool collideWith(const AObject *obj);
    virtual bool collideWith(const Vector3d &pos, const Vector3d &sz);
    bool	isAbove(void) const;
    bool	isBelow(void) const;
    bool	isLeft(void) const;
    bool	isRight(void) const;

  public:
    bool	collideLeft(const Vector3d &pos, const Vector3d &sz);
    bool	collideRight(const Vector3d &pos, const Vector3d &sz);
    bool	collideUp(const Vector3d &pos, const Vector3d &sz);
    bool	collideDown(const Vector3d &pos, const Vector3d &sz);
    void	resetColliding(void);

  protected:
    const Vector3d&	pos_;
    const Vector3d&	sz_;
    const AObject	*owner_;
    bool		above_;
    bool		below_;
    bool		left_;
    bool		right_;
  };
}

#endif /* !__BOUNDING_BOX_HH__*/

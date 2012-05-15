//
// BoundingBox.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May 10 15:02:09 2012 lois burg
// Last update Sun May 13 14:22:21 2012 lois burg
//

#ifndef		__BOUNDING_BOX_HH__
# define	__BOUNDING_BOX_HH__

# include   <QDataStream>
# include	"AObject.hh"
# include	"Vector3d.hh"

namespace	Bomberman
{
  class	BoundingBox
  {
  public:
    BoundingBox(const Vector3d& pos, const Vector3d& sz, const AObject *owner);
    virtual ~BoundingBox();

  public:
    bool	collideWith(const AObject *obj);
    bool	isAbove(void) const;
    bool	isBelow(void) const;
    bool	isLeft(void) const;
    bool	isRight(void) const;

  private:
    bool	collideLeft(const AObject *obj);
    bool	collideRight(const AObject *obj);
    bool	collideUp(const AObject *obj);
    bool	collideDown(const AObject *obj);

  private:
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

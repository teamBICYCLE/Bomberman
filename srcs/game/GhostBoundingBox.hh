//
// GhostBoundingBox.hh for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Thu May 17 16:05:43 2012 geoffroy lafontaine
// Last update Mon May 21 16:52:58 2012 Jonathan Machado
//

#ifndef		__GHOST_BOUNDING_BOX_HH__
# define	__GHOST_BOUNDING_BOX_HH__

# include	<QDataStream>
# include	"AObject.hh"
# include	"Vector3d.hh"
# include	"BoundingBox.hh"

namespace	Bomberman
{
  class GhostBoundingBox : public BoundingBox
  {
  public:
    GhostBoundingBox(const Vector3d& pos, const Vector3d& sz, const AObject *owner);
    GhostBoundingBox(const GhostBoundingBox &other, const AObject *owner);
    virtual ~GhostBoundingBox();

  public:
    virtual bool collideWith(const AObject *obj);
    virtual bool collideWith(const Vector3d &pos, const Vector3d &size);
  };
}

#endif /* !__GHOST_BOUNDING_BOX_HH__*/

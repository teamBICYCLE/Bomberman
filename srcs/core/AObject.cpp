//
// AObject.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 18:33:56 2012 lois burg
// Last update Sat May 26 17:48:01 2012 thibault carpentier
//

#include "AObject.hh"
#include "Character.hh"
#include "Explosion.hh"
#include "ModelHandler.hh"

#include "Mine.hh"

using namespace Bomberman;

AObject::AObject(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz, const std::string& modelName)
  : pos_(pos), rot_(rot), sz_(sz), type_(modelName), removeLater_(false)
{
}

AObject::~AObject(void)
{
}

void AObject::setPos(const Vector3d &pos)
{
    pos_ = pos;
}

void AObject::setRot(const Vector3d &rot)
{
    rot_ = rot;
}

void AObject::setSize(const Vector3d &sz)
{
    sz_ = sz;
}

const Vector3d &AObject::getPos(void) const
{
    return pos_;
}

const Vector3d &AObject::getRot(void) const
{
    return rot_;
}

const Vector3d &AObject::getSize(void) const
{
    return sz_;
}

const std::string &AObject::getType(void) const
{
    return type_;
}

//const AModel &AObject::getModel(void) const
//{
//    return model_;
//}

bool	AObject::toRemove(void) const
{
  return (removeLater_);
}

void	AObject::destroy(void)
{
  removeLater_ = true;
}

void	AObject::interact(Character *ch, std::list<AObject*>& objs)
{
  (void)objs;
  ch->bump(pos_);
}

void	AObject::interact(Explosion *e, std::list<AObject*>& objs)
{
  (void)e;
  (void)objs;
}

void    AObject::toQvariant(QSettings &w) const
{
    (void)w;
}

void	AObject::setDanger(std::vector<std::vector<std::pair<int, int> > > &map, std::list<AObject*>objs,
			   int x, int y) const
{
  (void)x;
  (void)y;
  (void)map;
  (void)objs;
}

void	AObject::setVirtualPheromones(std::vector<std::vector<std::pair<int, int> > > &map,
				      std::list<AObject*>objs) const
{
  (void)map;
  (void)objs;
}

void	AObject::setDangerMap(int x, int y, int danger,
			      std::vector<std::vector<std::pair<int, int> > > &map) const
{
  map[y][x].first = (danger > map[y][x].first ? danger : map[y][x].first);
  if (map[y][x].first > DANGER_MAX)
    map[y][x].first = DANGER_MAX;
  if (map[y][x].first < DANGER_MIN)
    map[y][x].first = DANGER_MIN;
}

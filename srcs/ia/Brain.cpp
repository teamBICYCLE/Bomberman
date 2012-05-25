//
// Brain.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon May 14 13:25:13 2012 thibault carpentier
// Last update Thu May 24 18:24:53 2012 thibault carpentier
// Last update Mon May 21 17:19:47 2012 Jonathan Machado
// Last update Fri May 18 17:54:49 2012 Jonathan Machado
//

#include <algorithm>
#include "Brain.hh"
#include "Block.hh"
#include "Brick.hh"
#include "Bomb.hh"
#include "Mine.hh"

using namespace Bomberman;
using namespace Thinking;
using namespace LuaVirtualMachine;

Brain::Brain(int x, int y)
    : Script(), danger_(x, y), x_(x), y_(y)
{
  lua_State *state = getVM().getLua();

  lua_pushinteger(state, eDirection::UP);
  lua_setglobal(state, "UP");
  lua_pushinteger(state, eDirection::RIGHT);
  lua_setglobal(state, "RIGHT");
  lua_pushinteger(state, eDirection::DOWN);
  lua_setglobal(state, "DOWN");
  lua_pushinteger(state, eDirection::LEFT);
  lua_setglobal(state, "LEFT");
  lua_pushinteger(state, eDirection::NODIR);
  lua_setglobal(state, "NODIR");
  lua_pushinteger(state, eDirection::NODIR);
  lua_setglobal(state, "NODIR");
  lua_pushinteger(state, eEnnemyType::MONSTER);
  lua_setglobal(state, "MONSTER");
  lua_pushinteger(state, eEnnemyType::GHOST);
  lua_setglobal(state, "GHOST");

  meth_[registerFct("isCrossable")] = &Brain::isCrossable;
  meth_[registerFct("getDanger")] = &Brain::getDanger;
}

Brain::Brain(const Brain &other)
    : Script(), danger_(other.x_, other.y_)
{
    decision_ = other.decision_;

    lua_State *state = getVM().getLua();

    lua_pushinteger(state, eDirection::UP);
    lua_setglobal(state, "UP");
    lua_pushinteger(state, eDirection::RIGHT);
    lua_setglobal(state, "RIGHT");
    lua_pushinteger(state, eDirection::DOWN);
    lua_setglobal(state, "DOWN");
    lua_pushinteger(state, eDirection::LEFT);
    lua_setglobal(state, "LEFT");
    lua_pushinteger(state, eDirection::NODIR);
    lua_setglobal(state, "NODIR");
    lua_pushinteger(state, eDirection::NODIR);
    lua_setglobal(state, "NODIR");
    lua_pushinteger(state, eEnnemyType::MONSTER);
    lua_setglobal(state, "MONSTER");
    lua_pushinteger(state, eEnnemyType::GHOST);
    lua_setglobal(state, "GHOST");

    meth_[registerFct("isCrossable")] = &Brain::isCrossable;
    meth_[registerFct("getDanger")] = &Brain::getDanger;

    x_ = other.x_;
    y_ = other.y_;
}

Brain::Brain()
    : Script(), danger_(0, 0), x_(0), y_(0)
{
    lua_State *state = getVM().getLua();

    lua_pushinteger(state, eDirection::UP);
    lua_setglobal(state, "UP");
    lua_pushinteger(state, eDirection::RIGHT);
    lua_setglobal(state, "RIGHT");
    lua_pushinteger(state, eDirection::DOWN);
    lua_setglobal(state, "DOWN");
    lua_pushinteger(state, eDirection::LEFT);
    lua_setglobal(state, "LEFT");
    lua_pushinteger(state, eDirection::NODIR);
    lua_setglobal(state, "NODIR");
    lua_pushinteger(state, eDirection::NODIR);
    lua_setglobal(state, "NODIR");
    lua_pushinteger(state, eEnnemyType::MONSTER);
    lua_setglobal(state, "MONSTER");
    lua_pushinteger(state, eEnnemyType::GHOST);
    lua_setglobal(state, "GHOST");

    meth_[registerFct("isCrossable")] = &Brain::isCrossable;
    meth_[registerFct("getDanger")] = &Brain::getDanger;
}

Brain::~Brain(void)
{}

int Brain::scriptCalling(VirtualMachine &vm, int fctNb)
{
  if (meth_.find(fctNb) != meth_.end())
    return ((this->*meth_[fctNb])(vm));
  return (-1);
}

void Brain::getReturn(VirtualMachine &vm, const std::string &strFunc)
{
  lua_State	*state = vm.getLua();

  decision_ = eDirection::NODIR;
  if (strFunc == "thinking")
    {
      if (lua_gettop(state) == 1 && lua_isnumber(state, 1))
	decision_ = static_cast<eDirection>(lua_tonumber(state, 1));
    }
  return;
}

eDirection Brain::getDecision(void) const
{
  return (decision_);
}

void Brain::updateDangerMap(std::list<AObject*> &objs)
{
  danger_.updateGameVision(objs);
}

bool Brain::isParamsPosition(VirtualMachine &vm) const
{
  lua_State *state = vm.getLua();

  if (lua_gettop(state) >= 2 && lua_isnumber(state, 1) && lua_isnumber(state, 2))
    return (true);
  return (false);
}

int Brain::getDanger(VirtualMachine &vm)
{
  int danger = DANGER_MAX + 1;
  int x, y;

  if (isParamsPosition(vm))
    {
      x = lua_tonumber(vm.getLua(), 1);
      y = lua_tonumber(vm.getLua(), 2);
      if (x >= 0 && x < danger_.x_ && y >= 0 && y < danger_.y_)
	danger = danger_.getDanger(x, y);
    }
  lua_pushnumber(vm.getLua(), danger);
  return (1);
}

int Brain::getX(void) const
{
    return x_;
}

int Brain::getY(void) const
{
    return y_;
}

int Brain::isCrossable(VirtualMachine &vm)
{
  std::list<AObject*> objs = danger_.getObjs();
  int valid = -1;
  double x, y;

  if (isParamsPosition(vm) && lua_gettop(vm.getLua()) == 3)
    {
      x = lua_tonumber(vm.getLua(), 1);
      y = lua_tonumber(vm.getLua(), 2);
      BoundingBox bb(Vector3d(x, y, 0), Vector3d(0.6, 0.6, 0), NULL);
      valid = 0;
      if (x >= 0 && x < danger_.x_ && y >= 0 && y < danger_.y_)
  	{
	  valid = 1;
 	  std::for_each(objs.begin(), objs.end(), [&](AObject *obj) -> void {
  	      if (valid && bb.collideWith(obj))
  		{
  		  if (((lua_tonumber(vm.getLua(), 3) == MONSTER) && dynamic_cast<Brick*>(obj))
		      || dynamic_cast<Block*>(obj) || dynamic_cast<Bomb*>(obj))
		    valid = 0;
  		}
  	    });
  	}
    }
  lua_pushnumber(vm.getLua(), valid);
  return (1);
}

/* Serialization */

void Brain::serialize(QDataStream &out) const
{
  out << x_;
  out << y_;
}

void Brain::unserialize(QDataStream &in)
{
    in >> x_;
    in >> y_;
}

QDataStream &operator<<(QDataStream &out, const Brain &b)
{
  b.serialize(out);
  return out;
}

QDataStream &operator>>(QDataStream &in, Brain &b)
{
  b.unserialize(in);
  return in;
}

//
// Brain.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon May 14 13:25:13 2012 thibault carpentier
// Last update Mon May 21 15:21:18 2012 thibault carpentier
// Last update Fri May 18 17:54:49 2012 Jonathan Machado
//

#include <algorithm>
#include "Brain.hh"
#include "Block.hh"
#include "Brick.hh"
#include "Bomb.hh"

using namespace Bomberman;
using namespace Thinking;
using namespace LuaVirtualMachine;

Brain::Brain(int x, int y)
  : danger_(x, y)
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

int Brain::isCrossable(VirtualMachine &vm)
{
  std::list<AObject*> objs = danger_.getObjs();
  int valid = -1;
  int x, y;

  if (isParamsPosition(vm) && lua_gettop(vm.getLua()) == 3)
    {
      x = lua_tonumber(vm.getLua(), 1);
      y = lua_tonumber(vm.getLua(), 2);
      valid = 0;
      if (x >= 0 && x < danger_.x_ && y >= 0 && y < danger_.y_)
  	{
	  valid = 1;
 	  std::for_each(objs.begin(), objs.end(), [&](AObject *obj) -> void {
  	      if (valid && static_cast<int>(obj->getPos().x) == x && static_cast<int>(obj->getPos().y == y))
  		{
  		  if (((lua_tonumber(vm.getLua(), 3) == MONSTER) && dynamic_cast<Brick*>(obj))
		      || dynamic_cast<Block*>(obj) || dynamic_cast<Bomb*>(obj))
  		    valid = 0;
  		}
  	    });
  	}
    }
  std::cout << "Rturning " << valid  << std::endl;
  lua_pushnumber(vm.getLua(), valid);
  return (1);
}

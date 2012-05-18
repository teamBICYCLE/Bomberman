//
// Brain.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon May 14 13:25:13 2012 thibault carpentier
// Last update Thu May 17 13:59:24 2012 thibault carpentier
//

#include "Brain.hh"

using namespace Bomberman;
using namespace Thinking;
using namespace LuaVirtualMachine;

Brain::Brain(void)
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


  meth_[registerFct("test")] = &Brain::test;
}

Brain::~Brain(void)
{}

int Brain::scriptCalling(VirtualMachine &vm, int fctNb)
{
  (void)vm;
  if (meth_.find(fctNb) != meth_.end())
    return (this->*meth_[fctNb])(vm);
  return (-1);
}

int Brain::test(VirtualMachine&vm)
{
  (void)vm;
  std::cout << "test fct" << std::endl;
  return (0);
}

void Brain::getReturn(VirtualMachine &vm, const std::string &strFunc)
{
  lua_State	*state = vm.getLua();

  decision_ = eDirection::NODIR;
  if (strFunc == "thinking")
    {
      if (lua_gettop(state) == 1 && lua_isnumber(state, 1))
	decision_ = (eDirection)lua_tonumber(state, 1);
    }
  return;
}

eDirection Brain::getDecision(void) const
{
  return (decision_);
}

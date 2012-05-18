//
// RestoreStack.cpp for  in /home/jonathan/Projets/iabomber
//
// Made by Jonathan Machado
// Login   <jonathan.machado@epitech.net>
//
// Started on  Sat May  5 16:20:38 2012 Jonathan Machado
// Last update Sat May 12 13:45:27 2012 thibault carpentier
//

#include "RestoreStack.hh"

using namespace Bomberman;
using namespace LuaVirtualMachine;

RestoreStack::RestoreStack(VirtualMachine &vm)
  : state_(vm.getLua()), iTop_(0)
{
  if (vm.isFonctionnal())
    iTop_ = lua_gettop(state_);
}

RestoreStack::~RestoreStack(void)
{
  lua_settop(state_, iTop_);
}

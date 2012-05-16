//
// main.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May  4 14:35:58 2012 thibault carpentier
// Last update Mon May 14 15:03:09 2012 thibault carpentier
//

#include <assert.h>
#include <iostream>
#include <cstdlib>
#include "Brain.hh"
#include "VirtualMachine.hh"
#include "Script.hh"

using namespace Thinking;
using namespace Bomberman;
using namespace LuaVirtualMachine;

int main(void)
{
  Brain ms;

  ms.compileFile ("lua/test.lua");
  assert(ms.fctExist("test"));
  ms.selectFct("thinking");
  ms.addParam (2);
  ms.callFct(1);
  return (EXIT_SUCCESS);
}

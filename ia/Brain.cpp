//
// Brain.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon May 14 13:25:13 2012 thibault carpentier
// Last update Mon May 14 15:59:43 2012 thibault carpentier
//

#include "Brain.hh"

using namespace Bomberman;
using namespace Thinking;

Brain::Brain(void)
{
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
  return (0);
}

void Brain::getReturn(VirtualMachine &vm, const std::string &strFunc)
{
  (void)vm;
  (void)strFunc;
  return;
}

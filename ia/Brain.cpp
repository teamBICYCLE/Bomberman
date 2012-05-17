//
// Brain.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon May 14 13:25:13 2012 thibault carpentier
// Last update Thu May 17 10:44:45 2012 thibault carpentier
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
  std::cout << "test fct" << std::endl;
  return (0);
}

void Brain::getReturn(VirtualMachine &vm, const std::string &strFunc)
{
  lua_State	*state = vm.getLua();
  int		i = 0;

  decision_ =eDirection::NODIR;
  if (strFunc == "thinking")
    {
      if (lua_gettop(state) == 1 && lua_isnumber(state, 1))
	i = lua_tonumber(state, 1);
      std::cout << "i = " << i  << std::endl;
      switch (i)
	{
	case 1:
	  {
	    decision_ = UP;
	    break;
	  }
	case 2:
	  {
	    decision_ = RIGHT;
	    break;
	  }
	case 3:
	  {
	    decision_ = DOWN;
	    break;
	  }
	case 4:
	  {
	    decision_ = LEFT;
	    break;
	  }
	default :
	  {
	    decision_ = NODIR;
	    break;
	  }
	}
    }
  return;
}

eDirection Brain::getDecision(void) const
{
  return (decision_);
}

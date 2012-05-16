//
// DangerMap.cpp for  in /home/carpen_t/projets/c++/Bomberman
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Wed May 16 14:51:01 2012 thibault carpentier
// Last update Wed May 16 15:03:41 2012 thibault carpentier
//

#include "DangerMap.hh"

using namespace Thinking;

DangerMap::DangerMap(std::list<AObject*> map)
{
  std::list<AObject*>::iterator it;

  for (it = map.begin(); it != map.end(); ++it)
    {
      std::cout << (*it)->type() << std::endl;
    }
(void)map;
}

DangerMap::~DangerMap(void)
{}

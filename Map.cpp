//
// MapManager.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May  4 15:28:37 2012 lois burg
// Last update Fri May  4 16:10:48 2012 lois burg
//

#include <algorithm>
#include "Map.hh"

using namespace Bomberman;

Map::Map(void)
{
}

Map::Map(const std::string& fileName)
{
}

Map::~Map(void)
{
}

const std::vector<AObject*>&	Map::getTerrain(void) const
{
  return (terrain_);
}

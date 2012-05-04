//
// Map.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May  4 15:28:37 2012 lois burg
// Last update Fri May  4 18:22:53 2012 lois burg
//

#include <iostream>
#include <fstream>
#include "Map.hh"

using namespace Bomberman;

Map::Failure::Failure(const std::string& func, const std::string& msg) throw()
  : std::runtime_error(msg), mFunc(func), mMsg(msg)
{
}

Map::Failure::~Failure() throw()
{
}

Map::Failure::Failure(const Map::Failure& other) throw()
  : std::runtime_error(other.getMsg()), mFunc(other.getFunc()), mMsg(other.getMsg())
{
}

Map::Failure&	Map::Failure::operator=(const Map::Failure& other) throw()
{
  if (&other != this)
    {
      mFunc = other.getFunc();
      mMsg = other.getMsg();
    }
  return (*this);
}

std::string	Map::Failure::getFunc(void) const throw()
{
  return (mFunc);
}

std::string	Map::Failure::getMsg(void) const throw()
{
  return (mMsg);
}

const char	*Map::Failure::what(void) const throw()
{
  return (("Map failure: " + mFunc + " failed - " + mMsg).c_str());
}

Map::Map(void)
{
}

Map::Map(const std::string& fileName)
{
    Map::getFromFile(fileName);
}

Map::~Map(void)
{
}

const std::vector<AObject*>&	Map::getTerrain(void) const
{
  if (terrain_.empty())
    throw Map::Failure("getTerrain", "Loaded map is empty.");
  return (terrain_);
}

bool Map::checkType(char c) const
{
    if (c == 'W' || c == 'B')
        return true;
    return false;
}

AObject *Map::createType(char c, unsigned int x, unsigned int y) const
{
    if (c == 'W')
      return new Block(Vector3d(x * 10, y * 10, 0), Vector3d(), Vector3d(10, 10, 0));
    return new Brick(Vector3d(x * 10, y * 10, 0), Vector3d(), Vector3d(10, 10, 0));
}

void Map::getFromFile(const std::string& fileName)
{
  std::string line;
  std::ifstream infile;
  unsigned int x;
  unsigned int y = 0;

  infile.open(fileName.c_str());
  while(!infile.eof())
    {
      getline(infile, line);
      for (x = 0; x != line.length(); x++)
	if (checkType(line[x]))
	  terrain_.push_back(createType(line[x], x, y));
      y++;
    }
  infile.close();
}

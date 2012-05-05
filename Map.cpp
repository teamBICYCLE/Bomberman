// Map.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Fri May  4 18:30:00 2012 geoffroy lafontaine
// Last update Sat May  5 12:36:31 2012 romain sylvian
//

#include <iterator>
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

Map::Map(unsigned int width, unsigned int height, unsigned int nbPlayers)
{
  for (unsigned int y = 1; y < height - 1; y += 2)
    {
      for (unsigned int x = 1; x < width - 1; x += 2)
        {
          terrain_.push_back(new Block(Vector3d(x * 40, y * 40, 0), Vector3d(0,0,0), Vector3d(40, 40, 0)));
        }
    }
  addPlayers(width, height, nbPlayers);
  generateBricks(width, height, nbPlayers);
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

void				Map::generateBricks(unsigned int width, unsigned int height,
						    unsigned int nbPlayers)
{
  unsigned int				nbBricks = 0;
  std::vector<AObject*>::iterator	it;

  nbBricks = (width * height) - terrain_.size() - (3 * nbPlayers) - ((width > height ? width : height));
  do {
    unsigned int x = rand() % width;
    unsigned int y = rand() % height;

    if ((x % 2) && (width - 1) > (x + 1))
      ++x;
    if ((y % 2) && (height - 1) > (y + 1))
      ++y;
    for (it = terrain_.begin(); it != terrain_.end(); ++it)
      {
        if ((*it)->getPos().x != x && (*it)->getPos().y != y)
          {
            terrain_.push_back(new Brick(Vector3d(x * 40, y * 40, 0), Vector3d(0, 0, 0), Vector3d(40, 40, 0)));
            --nbBricks;
            break;
          }
      }
  }
  while (nbBricks > 0);
}

void				Map::addPlayers(unsigned int width, unsigned int height,
						unsigned int nbPlayers)
{
  terrain_.push_back(new Player(Vector3d(0,0,0), Vector3d(0,0,0), Vector3d(40, 40, 0)));
  if (nbPlayers > 1)
    terrain_.push_back(new Player(Vector3d((width - 1) * 40, (height - 1) * 40, 0), Vector3d(0,0,0), Vector3d(40, 40, 0)));
  if (nbPlayers > 2)
    terrain_.push_back(new Player(Vector3d(0, (height - 1) * 40, 0), Vector3d(0,0,0), Vector3d(40, 40, 0)));
  if (nbPlayers > 3)
    terrain_.push_back(new Player(Vector3d((width - 1) * 40, 0, 0), Vector3d(0,0,0), Vector3d(40, 40, 0)));
}

bool Map::checkType(char c) const
{
  if (std::string(MAP_FILE_ALLOWED).find(c) == std::string::npos)
    throw Map::Failure("checkType", "Illegal character.");
  else if (c == MAP_FILE_BLOCK || c == MAP_FILE_BRICK || c == MAP_FILE_PLAYER)
    return true;
  return false;
}

AObject *Map::createType(char c, unsigned int x, unsigned int y, bool *player) const
{
    if (c == MAP_FILE_BLOCK)
      return new Block(Vector3d(x * 40, y * 40, 0), Vector3d(), Vector3d(40, 40, 0));
    else if (c == MAP_FILE_BRICK)
      return new Brick(Vector3d(x * 40, y * 40, 0), Vector3d(), Vector3d(40, 40, 0));
    *player = true;
    return new Player(Vector3d(x * 40, y * 40, 0), Vector3d(0,0,0), Vector3d(40, 40, 0));
}

void Map::getFromFile(const std::string& fileName)
{
  std::string line;
  std::ifstream infile;
  unsigned int x;
  unsigned int y = 0;
  bool	player = false;

  infile.open(fileName.c_str());
  if (infile.fail())
    throw Map::Failure("getFromFile", "File doesn't exist.");
  while(!infile.eof())
    {
      getline(infile, line);
      for (x = 0; x != line.length(); x++)
	if (checkType(line[x]))
	  terrain_.push_back(createType(line[x], x, y, &player));
      y++;
    }
  infile.close();
  if (!player)
    throw Map::Failure("getFromFile", "No player seted in map.");
}

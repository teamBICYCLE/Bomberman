// Map.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Fri May  4 18:30:00 2012 geoffroy lafontaine
// Last update Wed May  9 15:58:49 2012 geoffroy lafontaine
//

#include <algorithm>
#include <iterator>
#include <utility>
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
    for (unsigned int x = 1; x < width - 1; x += 2)
      terrain_.push_back(new Block(Vector3d(x, y, 0), Vector3d(0,0,0), Vector3d(1, 1, 0)));
  generateBricks(width, height, nbPlayers);
  addPlayers(width, height, 1);
}

Map::Map(const std::string& fileName)
{
    Map::getFromFile(fileName);
}

Map::~Map(void)
{
}

const std::list<AObject*>&	Map::getTerrain(void) const
{
  if (terrain_.empty())
    throw Map::Failure("getTerrain", "Loaded map is empty.");
  return (terrain_);
}

void					Map::generateBricks(unsigned int width,
							    unsigned int height,
							    unsigned int nbPlayers)
{
  unsigned int				nbBricks;
  std::list<AObject*>::iterator		it;
  unsigned int				x;
  unsigned int				y;
  bool					find = false;

  nbBricks = (width * height) - terrain_.size() - (3 * nbPlayers);
  do {
    x = rand() % width;
    y = rand() % height;
    if ((x % 2) == 0 || (y % 2) == 0)
      {
	for (it = terrain_.begin(); it != terrain_.end() && !find; ++it)
	  if ((*it)->getPos().x == (x ) && (*it)->getPos().y == (y ))
	    find = true;
	if (!find)
	  {
	    terrain_.push_back(new Brick(Vector3d(x , y , 0), Vector3d(0, 0, 0), Vector3d(1, 1, 0)));
	    --nbBricks;
	  }
	find = false;
      }
  }
  while (nbBricks > 0);
}

void				Map::addPlayers(unsigned int width, unsigned int height,
						unsigned int nbPlayers)
{
  (void)width;
  (void)height;
  placePlayer(0,0);
  // placePlayer(width,0);
  // placePlayer(0,height);
  // placePlayer(width,height);
  // for (int i = 0; i < nbPlayers; ++i)
  //   {
      
  //   }
}

void				Map::placePlayer(unsigned int x, unsigned int y)
{
  terrain_.push_back(new Player(Vector3d(x, y, 0), Vector3d(0,0,0), Vector3d(0.5, 0.5, 0)));
  clearPlace(0, 0);  
}

void				Map::clearPlace(unsigned int x, unsigned int y)
{
  std::list<AObject*>::iterator			it;
  std::vector< std::pair<int, int> >		postab;
  std::vector< std::pair<int, int> >::iterator	i;

  postab.push_back(std::make_pair(0, 0));
  postab.push_back(std::make_pair(1, 0));
  postab.push_back(std::make_pair(0, 1));
  postab.push_back(std::make_pair(-1, 0));
  postab.push_back(std::make_pair(0, -1));
  for (it = terrain_.begin(); it != terrain_.end(); ++it)
    {
      for (i = postab.begin(); i != postab.end(); ++i)
	{
	  if (((*it)->getPos().x == ((x + (*i).first)))
	      && ((*it)->getPos().y == ((y + (*i).second)))
	      && dynamic_cast<Brick*>(*it))
	    {
      	      it = terrain_.erase(it);
	      break;
	    }
	}
    }
}

bool Map::checkType(char c) const
{
  if (std::string(MAP_FILE_ALLOWED).find(c) == std::string::npos)
    throw Map::Failure("checkType", "Forbidden character.");
  else if (c == MAP_FILE_BLOCK || c == MAP_FILE_BRICK || c == MAP_FILE_PLAYER)
    return true;
  return false;
}

AObject *Map::createType(char c, unsigned int x, unsigned int y, bool *player) const
{
    if (c == MAP_FILE_BLOCK)
      return new Block(Vector3d(x , y , 0), Vector3d(), Vector3d(1, 1, 0));
    else if (c == MAP_FILE_BRICK)
      return new Brick(Vector3d(x , y , 0), Vector3d(), Vector3d(1, 1, 0));
    *player = true;
    return new Player(Vector3d(x , y , 0), Vector3d(0,0,0), Vector3d(0.5, 0.5, 0));
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
  while (!infile.eof())
    {
      getline(infile, line);
      for (x = 0; x != line.length(); x++)
	if (checkType(line[x]))
	  terrain_.push_back(createType(line[x], x, y, &player));
      y++;
    }
  infile.close();
  if (!player)
    throw Map::Failure("getFromFile", "No player set on the map.");
}

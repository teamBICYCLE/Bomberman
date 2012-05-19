//
// Map.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Fri May  4 18:30:00 2012 geoffroy lafontaine
// Last update Sat May 19 11:39:55 2012 thibault carpentier
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

Map::Map(uint width, uint height, uint nbPlayers)
{
  if ((width * height) < (nbPlayers * 4))
    throw Map::Failure("Map", "too many players for this map.");

  for (uint y = 1; y < height - 1; y += 2)
    for (uint x = 1; x < width - 1; x += 2)
      terrain_.push_back(new Block(Vector3d(x, y, 0), Vector3d(0,0,0), Vector3d(1, 1, 0)));
  generateBricks(width, height, nbPlayers);
  generateBorder(width, height);
  generatePlayers(width, height, nbPlayers);
  generateMonsters(width, height, 1);
  generateGhosts(width, height, 0);
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

void				Map::generateBorder(uint width, uint height)
{
  for (int x = -1; x < static_cast<int>(width) + 1; ++x)
    {
      terrain_.push_back(new Block(Vector3d(x, -1, 0), Vector3d(0,0,0), Vector3d(1, 1, 0)));
      terrain_.push_back(new Block(Vector3d(x, height, 0), Vector3d(0,0,0), Vector3d(1, 1, 0)));
    }
  for (int y = 0; y < static_cast<int>(height); ++y)
    {
      terrain_.push_back(new Block(Vector3d(-1, y, 0), Vector3d(0,0,0), Vector3d(1, 1, 0)));
      terrain_.push_back(new Block(Vector3d(width, y, 0), Vector3d(0,0,0), Vector3d(1, 1, 0)));
    }
}

void				Map::generateBricks(uint width, uint height, uint nbPlayers)
{
  uint				nbBricks;
  std::list<AObject*>::iterator	it;
  uint				x;
  uint				y;
  bool				find = false;

  nbBricks = (width * height) - terrain_.size() - (3 * nbPlayers) - (width + height)/*(width > height ? width : height)*/;
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

void				Map::generatePlayers(uint width, uint height,
						uint nbPlayers)
{
  std::vector< std::pair<int, int> >		postab;

  postab.push_back(std::make_pair(0, 0));
  postab.push_back(std::make_pair(0, height - 1));
  postab.push_back(std::make_pair(width - 1, 0));
  postab.push_back(std::make_pair(width - 1, height - 1));
  if (nbPlayers <= 4)
    {
      for (uint i = 0; i < nbPlayers; ++i)
  	placePlayer(postab[i].first, postab[i].second);
    }
}

void				Map::placePlayer(uint x, uint y)
{
  clearPlace(x, y);
  terrain_.push_back(new Player(Vector3d(x, y, 0), Vector3d(0,0,0), Vector3d(0.6, 0.6, 0)));
}

void				Map::generateMonsters(uint width, uint height, uint nbMonsters)
{
  std::list<AObject*>::iterator	it;
  uint				x = 0;
  uint				y = 0;
  bool				find = false;
  Thinking::Brain		*b;

  b = new Thinking::Brain(width, height);
  do {
    x = rand() % width;
    y = rand() % height;
    x = (x < 2) ? x + 2 : x;
    x = (x > width - 2) ? x - 2 : x;
    y = (y < 2) ? y + 2 : y;
    y = (y > height - 2) ? y - 2 : y;
    if ((x % 2) == 0 || (y % 2) == 0)
      {
	for (it = terrain_.begin(); it != terrain_.end() && !find; ++it)
	  if ((*it)->getPos().x == x && (*it)->getPos().y == y)
	    find = true;
	if (!find)
	  {
	    placeMonster(x, y, b);
	    --nbMonsters;
	  }
	find = false;
      }
  }
  while (nbMonsters > 0);
}

void				Map::placeMonster(uint x, uint y, Thinking::Brain *b)
{
  std::list<AObject*>::iterator	it;

  for (it = terrain_.begin(); it != terrain_.end();)
    {
      if ((*it)->getPos().x == x && (*it)->getPos().y == y && dynamic_cast<Brick*>(*it))
	{
	  it = terrain_.erase(it);
	  break;
	}
      ++it;
    }
  terrain_.push_back(new Monster(Vector3d(x, y, 0), Vector3d(0,0,0), Vector3d(0.6, 0.6, 0), b));
}

void				Map::generateGhosts(uint width, uint height, uint nbGhosts)
{
  std::list<AObject*>::iterator	it;
  uint				x = 0;
  uint				y = 0;
  bool				find = false;
  Thinking::Brain		*b;

  b = new Thinking::Brain(width, height);
  do {
    x = rand() % width;
    y = rand() % height;
    x = (x < 3) ? x + 3 : x;
    x = (x > width - 3) ? x - 3 : x;
    y = (y < 3) ? y + 3 : y;
    y = (y > height - 3) ? y - 3 : y;
    if ((x % 2) == 0 || (y % 2) == 0)
      {
	for (it = terrain_.begin(); it != terrain_.end() && !find; ++it)
	  if ((*it)->getPos().x == x && (*it)->getPos().y == y)
	    find = true;
	if (!find)
	  {
	    placeGhost(x, y, b);
	    --nbGhosts;
	  }
	find = false;
      }
  }
  while (nbGhosts > 0);
}

void				Map::placeGhost(uint x, uint y, Thinking::Brain *b)
{
  std::list<AObject*>::iterator	it;

  for (it = terrain_.begin(); it != terrain_.end();)
    {
      if ((*it)->getPos().x == x && (*it)->getPos().y == y && dynamic_cast<Brick*>(*it))
	{
	  it = terrain_.erase(it);
	  break;
	}
      ++it;
    }
  terrain_.push_back(new Ghost(Vector3d(x, y, 0), Vector3d(0,0,0), Vector3d(0.6, 0.6, 0), b));
}

void				Map::clearPlace(uint x, uint y)
{
  std::list<AObject*>::iterator			it;
  std::vector< std::pair<int, int> >		postab;
  std::vector< std::pair<int, int> >::iterator	i;
  bool						found = false;

  postab.push_back(std::make_pair(0, 0));
  postab.push_back(std::make_pair(1, 0));
  postab.push_back(std::make_pair(0, 1));
  postab.push_back(std::make_pair(-1, 0));
  postab.push_back(std::make_pair(0, -1));
  for (it = terrain_.begin(); it != terrain_.end();)
    {
      found = false;
      for (i = postab.begin(); i != postab.end(); ++i)
	{
	  if (((*it)->getPos().x == ((x + (*i).first)))
	      && ((*it)->getPos().y == ((y + (*i).second)))
	      && dynamic_cast<Brick*>(*it))
	    {
      	      it = terrain_.erase(it);
	      found = true;
	      break;
	    }
	}
      if (!found)
	++it;
    }
}

void Map::addBlocks(const std::string &l, int y, std::list<AObject*> *tmp)
{
    for (uint i = 0; i != l.length(); i++)
        if (l[i] == MAP_FILE_BLOCK)
            tmp->push_back(new Block(Vector3d(i + 1, y, 0), Vector3d(), Vector3d(1, 1, 0)));
}

void Map::addBricks(const std::string &l, int y, std::list<AObject*> *tmp)
{
    for (uint i = 0; i != l.length(); i++)
        if (l[i] == MAP_FILE_BRICK)
            tmp->push_back(new Brick(Vector3d(i + 1, y, 0), Vector3d(), Vector3d(1, 1, 0)));
}

void Map::addPlayers(const std::string &l, int y, bool *player)
{
    for (uint i = 0; i != l.length(); i++)
    {
        if (l[i] == MAP_FILE_PLAYER)
        {
            terrain_.push_back(new Player(Vector3d(i + 1, y, 0), Vector3d(0,0,0), Vector3d(0.5, 0.5, 0)));
            *player = true;
        }
    }
}

void Map::addGhosts(const std::string &l, int y, std::list<AObject*> *tmp, Thinking::Brain *b)
{
    for (uint i = 0; i != l.length(); i++)
    {
        if (l[i] == MAP_FILE_GHOST)
            tmp->push_back(new Ghost(Vector3d(i + 1, y, 0), Vector3d(0,0,0), Vector3d(0.6, 0.6, 0), b));
    }
}

void Map::addMonsters(const std::string &l, int y, std::list<AObject*> *tmp, Thinking::Brain *b)
{
    for (uint i = 0; i != l.length(); i++)
    {
        if (l[i] == MAP_FILE_MONSTER)
            tmp->push_back(new Monster(Vector3d(i + 1, y, 0), Vector3d(0,0,0), Vector3d(0.6, 0.6, 0), b));
    }
}

void Map::getFromFile(const std::string& fileName)
{
  std::string       line;
  std::ifstream     infile;
  uint				y = 0;
  uint              x = 0;
  bool				player = false;
  std::list<AObject*>	tmp;
  std::list<AObject*>::iterator it;

  /* tmp */
  Thinking::Brain		*b;

  b = new Thinking::Brain(13, 13);

  infile.open(fileName.c_str());
  if (infile.fail())
    throw Map::Failure("getFromFile", "File doesn't exist.");
  while (!infile.eof())
    {
      getline(infile, line);
      Map::addBlocks(line, y + 1, &tmp);
      Map::addBricks(line, y + 1, &tmp);
      Map::addPlayers(line, y + 1, &player);
      Map::addGhosts(line, y + 1, &tmp, b);
      Map::addMonsters(line, y + 1, &tmp ,b);
      if (line.length() > x)
          x = line.length();
      y++;
    }
  for (it = tmp.begin(); it != tmp.end(); it++)
      terrain_.push_back((*it));
  Map::generateBorder((x + 2), (y + 2));
  infile.close();
  if (!player)
    throw Map::Failure("getFromFile", "No player set on the map.");
}

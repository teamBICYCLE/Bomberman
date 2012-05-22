//
// Map.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
//
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
//
// Started on  Fri May  4 18:30:00 2012 geoffroy lafontaine
// Last update Tue May 22 13:29:36 2012 geoffroy lafontaine
//

#include <algorithm>
#include <iterator>
#include <utility>
#include <iostream>
#include <fstream>
#include "FireBlock.hh"
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

Map::Map(uint width, uint height, uint nbPlayers, uint nbMonsters, uint nbGhosts)
  : width_(width), height_(height),
    nbPlayers_(nbPlayers), nbMonsters_(nbMonsters), nbGhosts_(nbGhosts)
{
  if ((width_ * height_) < (nbPlayers_ * 4))
    throw Map::Failure("Map", "too many players for this map.");

  for (uint y = 1; y < height - 1; y += 2)
    for (uint x = 1; x < width - 1; x += 2)
      terrain_.push_back(new Block(Vector3d(x, y, 0), Vector3d(0,0,0), Vector3d(1, 1, 0)));
  generateBricks();
  generateBorder();
  generatePlayers();
  generateMonsters(nbMonsters_);
  generateGhosts(nbGhosts_);
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

void				Map::generateBorder(void)
{
  for (int x = -1; x < static_cast<int>(width_) + 1; ++x)
    {
      terrain_.push_back(new Block(Vector3d(x, -1, 0), Vector3d(0,0,0), Vector3d(1, 1, 0)));
      terrain_.push_back(new Block(Vector3d(x, height_, 0), Vector3d(0,0,0), Vector3d(1, 1, 0)));
    }
  for (int y = 0; y < static_cast<int>(height_); ++y)
    {
      terrain_.push_back(new Block(Vector3d(-1, y, 0), Vector3d(0,0,0), Vector3d(1, 1, 0)));
      terrain_.push_back(new Block(Vector3d(width_, y, 0), Vector3d(0,0,0), Vector3d(1, 1, 0)));
    }
}

void				Map::generateBricks(void)
{
  uint				nbBricks;
  std::list<AObject*>::iterator	it;
  uint				x;
  uint				y;
  bool				find = false;

  nbBricks = (width_ * height_) - terrain_.size() - (3 * nbPlayers_) - (width_ + height_);
  do {
    x = rand() % width_;
    y = rand() % height_;
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

void				Map::generatePlayers(void)
{
  std::vector< std::pair<int, int> >		postab;

  postab.push_back(std::make_pair(0, 0));
  postab.push_back(std::make_pair(0, height_ - 1));
  postab.push_back(std::make_pair(width_ - 1, 0));
  postab.push_back(std::make_pair(width_ - 1, height_ - 1));
  if (nbPlayers_ <= 4)
  {
      for (uint i = 0; i < nbPlayers_; ++i)
          placePlayer(postab[i].first, postab[i].second);
  }
}

void				Map::placePlayer(uint x, uint y)
{
  clearPlace(x, y);
  terrain_.push_back(new Player(Vector3d(x, y, 0), Vector3d(0,0,0), Vector3d(0.6, 0.6, 0)));
}

void				Map::generateMonsters(uint nbMonsters)
{
  std::list<AObject*>::iterator	it;
  uint				x = 0;
  uint				y = 0;
  bool				find = false;
  Thinking::Brain		*b;

  b = new Thinking::Brain(width_, height_);
  while (nbMonsters > 0)
  {
      x = rand() % width_;
      y = rand() % height_;
      x = (x < 2) ? x + 2 : x;
      x = (x > width_ - 2) ? x - 2 : x;
      y = (y < 2) ? y + 2 : y;
      y = (y > height_ - 2) ? y - 2 : y;
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

void				Map::generateGhosts(uint nbGhosts)
{
  std::list<AObject*>::iterator	it;
  uint				x = 0;
  uint				y = 0;
  bool				find = false;
  Thinking::Brain   *b;

  b = new Thinking::Brain(width_, height_);
  while (nbGhosts > 0)
  {
    x = rand() % width_;
    y = rand() % height_;
    x = (x < 3) ? x + 3 : x;
    x = (x > width_ - 3) ? x - 3 : x;
    y = (y < 3) ? y + 3 : y;
    y = (y > height_ - 3) ? y - 3 : y;
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
}

void				Map::placeGhost(uint x, uint y, Thinking::Brain *b)
{
  std::list<AObject*>::iterator	it;

  for (it = terrain_.begin(); it != terrain_.end(); ++it)
  {
      if ((*it)->getPos().x == x && (*it)->getPos().y == y && dynamic_cast<Brick*>(*it))
      {
          it = terrain_.erase(it);
          break;
      }
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
    {
      if (l[i] == MAP_FILE_BLOCK)
	tmp->push_back(new Block(Vector3d(i, y, 0), Vector3d(), Vector3d(1, 1, 0)));
      else if (l[i] == MAP_FILE_FIREBLOCK_UP)
	tmp->push_back(new FireBlock(Vector3d(i, y, 0), Vector3d(), Vector3d(1, 1, 0), Vector3d(0, -1, 0)));
      else if (l[i] == MAP_FILE_FIREBLOCK_DOWN)
	tmp->push_back(new FireBlock(Vector3d(i, y, 0), Vector3d(), Vector3d(1, 1, 0), Vector3d(0, 1, 0)));
      else if (l[i] == MAP_FILE_FIREBLOCK_LEFT)
	tmp->push_back(new FireBlock(Vector3d(i, y, 0), Vector3d(), Vector3d(1, 1, 0), Vector3d(-1, 0, 0)));
      else if (l[i] == MAP_FILE_FIREBLOCK_RIGT)
	tmp->push_back(new FireBlock(Vector3d(i, y, 0), Vector3d(), Vector3d(1, 1, 0), Vector3d(1, 0, 0)));
    }
}

void Map::addBricks(const std::string &l, int y, std::list<AObject*> *tmp)
{
    for (uint i = 0; i != l.length(); i++)
        if (l[i] == MAP_FILE_BRICK)
            tmp->push_back(new Brick(Vector3d(i, y, 0), Vector3d(), Vector3d(1, 1, 0)));
}

void Map::addPlayers(std::list<std::string> &map)
{
    bool player = false;
    std::list<std::string>::iterator it;
    uint y = 0;

    for (it = map.begin(); it != map.end(); it++)
    {
        for (uint i = 0; i != it->length(); i++)
        {
            if ((*it)[i] == MAP_FILE_PLAYER)
            {
                terrain_.push_back(new Player(Vector3d(i, y, 0), Vector3d(0,0,0), Vector3d(0.5, 0.5, 0)));
                player = true;
            }
        }
        y++;
    }

    if (!player)
      throw Map::Failure("getFromFile", "No player set on the map.");
}

void Map::addGhosts(const std::string &l, int y, std::list<AObject*> *tmp, Thinking::Brain *b)
{
    for (uint i = 0; i != l.length(); i++)
    {
        if (l[i] == MAP_FILE_GHOST)
            tmp->push_back(new Ghost(Vector3d(i, y, 0), Vector3d(0,0,0), Vector3d(0.6, 0.6, 0), b));
    }
}

void Map::addMonsters(const std::string &l, int y, std::list<AObject*> *tmp, Thinking::Brain *b)
{
    for (uint i = 0; i != l.length(); i++)
    {
        if (l[i] == MAP_FILE_MONSTER)
            tmp->push_back(new Monster(Vector3d(i, y, 0), Vector3d(0,0,0), Vector3d(0.6, 0.6, 0), b));
    }
}

void Map::mapFileIsValid(std::list<std::string> &map) const
{
    uint max = map.front().length();
    std::list<std::string>::const_iterator it;

    for (it = map.begin(); it != map.end(); it++)
    {
        if (it->length() > max)
            throw Map::Failure("getFromFile", "Map is not valid !");
    }
}

void Map::setFromFile(std::list<std::string> &map)
{
    std::list<AObject*> tmp;
    std::list<AObject*>::iterator it;
    std::list<std::string>::iterator itm;
    uint y = 0;
    Thinking::Brain		*b;

    width_ = map.front().length();
    height_ = map.size();
    b = new Thinking::Brain(map.front().length(), map.size());
    Map::addPlayers(map);
    for (itm = map.begin(); itm != map.end(); itm++)
    {
        Map::addBlocks((*itm), y, &tmp);
        Map::addBricks((*itm), y, &tmp);
        Map::addGhosts((*itm), y, &tmp, b);
        Map::addMonsters((*itm), y, &tmp ,b);
        y++;
    }
    for (it = tmp.begin(); it != tmp.end(); it++)
        terrain_.push_back((*it));
    Map::generateBorder();
}

void                            Map::getFromFile(const std::string& fileName)
{
  std::string                   line;
  std::ifstream                 infile;
  std::list<std::string>        map;

  infile.open(fileName.c_str());
  if (infile.fail())
    throw Map::Failure("getFromFile", "File doesn't exist.");
  while (!infile.eof())
    {
      getline(infile, line);
      if (!line.empty())
        map.push_back(line);
    }
  infile.close();
  Map::mapFileIsValid(map);
  Map::setFromFile(map);
}

uint    Map::getWidth(void) const
{
    return width_;
}

uint    Map::getHeight(void) const
{
    return height_;
}

uint	Map::getNbPlayers(void) const
{
  return nbPlayers_;
}

uint	Map::getNbMonsters(void) const
{
  return nbMonsters_;
}

uint	Map::getNbGhosts(void) const
{
  return nbGhosts_;
}

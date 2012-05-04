//
// Map.cpp for bomberman in /home/lafont_g//tek2/bomberman/Bomberman
// 
// Made by geoffroy lafontaine
// Login   <lafont_g@epitech.net>
// 
// Started on  Fri May  4 18:30:00 2012 geoffroy lafontaine
// Last update Fri May  4 18:30:29 2012 geoffroy lafontaine
//

#include <iterator>
#include <iostream>
#include <fstream>
#include "Map.hh"

using namespace Bomberman;

Map::Map(unsigned int width, unsigned int height, unsigned int nbPlayers)
{
  for (unsigned int y = 1; y < height - 1; y += 2)
    {
      for (unsigned int x = 1; x < width - 1; x += 2)
        {
          terrain_.push_back(new Block(Vector3d(x,y,0), Vector3d(0,0,0), Vector3d(0,0,0)));
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
    throw int(56);
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
            terrain_.push_back(new Brick(Vector3d(x, y, 0), Vector3d(0, 0, 0), Vector3d(0, 0, 0)));
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
  terrain_.push_back(new Player(Vector3d(0,0,0), Vector3d(0,0,0), Vector3d(0,0,0)));
  if (nbPlayers > 1)
    terrain_.push_back(new Player(Vector3d(width - 1,height - 1,0), Vector3d(0,0,0), Vector3d(0,0,0)));
  if (nbPlayers > 2)
    terrain_.push_back(new Player(Vector3d(0,height - 1,0), Vector3d(0,0,0), Vector3d(0,0,0)));
  if (nbPlayers > 3)
    terrain_.push_back(new Player(Vector3d(width - 1,0,0), Vector3d(0,0,0), Vector3d(0,0,0)));
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

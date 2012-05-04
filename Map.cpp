//
// MapManager.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May  4 15:28:37 2012 lois burg
// Last update Fri May  4 18:13:47 2012 geoffroy lafontaine
//

#include <iterator>
#include "MapManager.hh"

using namespace Bomberman;

Map::Map(unsigned int width, unsigned int height, unsigned int nbPlayers)
{
  for (int y = 1; y < height - 1; y += 2)
    {
      for (int x = 1; x < width - 1; x += 2)
	{
	  terrain_.push_back(new Block(Vector3d(x,y,0), Vector3d(0,0,0), Vector3d(0,0,0)));
	}
    }
  addPlayers(width, height, nbPlayers);
  generateBricks(width, height, nbPlayers);
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
	if ((*it).getPos().x != x && (*it).getPos().y != y)
	  {
	    terrain_.push_back(new Brick(Vector3d(x,y,0), Vector3d(0,0,0), Vector3d(0,0,0)));
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

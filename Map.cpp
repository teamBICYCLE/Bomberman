//
// Map.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May  4 15:28:37 2012 lois burg
// Last update Fri May  4 16:10:48 2012 lois burg
//

<<<<<<< HEAD
#include <algorithm>
=======
#include <iostream>
#include <fstream>
>>>>>>> c21029842bfdcaf3501f9d95cd17603db71392f7
#include "Map.hh"

using namespace Bomberman;

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
        return new Block(Vector3d(x, y, 0), Vector3d(), Vector3d());
    return new Brick(Vector3d(x, y, 0), Vector3d(), Vector3d());
}

void Map::getFromFile(const std::string& fileName)
{
    std::string line;
    std::ifstream infile;
    unsigned int x;
    unsigned int y = 0;

    infile.open (fileName.c_str());
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

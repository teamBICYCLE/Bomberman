//
// DangerMap.cpp for  in /home/carpen_t/projets/c++/Bomberman
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May 25 13:57:28 2012 thibault carpentier
// Last update Thu May 31 14:10:09 2012 thibault carpentier
//


#include <algorithm>
#include "DangerMap.hh"
#include "Bomb.hh"
#include "APowerup.hh"
#include "Mine.hh"
#include "Block.hh"
#include "Brick.hh"
#include "FireBlock.hh"

using namespace Bomberman;

DangerMap::DangerMap(int x, int y)
  : danger_(y), x_(x), y_(y)
{
  for (int i = 0; i < y; ++i)
    danger_[i] = std::vector<std::pair<int, int> >(x);
}

DangerMap::~DangerMap(void)
{}

void DangerMap::resetDanger(void)
{
  std::vector<std::vector<std::pair<int, int> > >::iterator it;
  for (int x = 0; x < x_; ++x)
    for (int y = 0; y < y_; ++y)
      danger_[y][x] = std::pair<int, int>(0, danger_[y][x].second);
}

void DangerMap::resetPheromones(void)
{
  std::vector<std::vector<std::pair<int, int> > >::iterator it;
  for (int x = 0; x < x_; ++x)
    for (int y = 0; y < y_; ++y)
      {
	if (danger_[y][x].second > 0)
	  danger_[y][x].second -= 1;
	else if (danger_[y][x].second < 0)
	  danger_[y][x].second += 1;
      }
}

void DangerMap::updateCaseVison(const std::list<AObject*>::const_iterator &it)
{
  (*it)->setDanger(danger_, objs_, x_, y_);
  (*it)->setVirtualPheromones(danger_, objs_, x_, y_);
}

int  DangerMap::getDanger(int x, int y) const
{
  return (danger_[y][x].first);
}

int  DangerMap::getPheromones(int x, int y) const
{
  return (danger_[y][x].second);
}


void DangerMap::updateGameVision(const std::list<AObject*>& objs)
{
  int x, y;
  objs_ = objs;
  std::list<AObject*>::const_iterator it;

  resetDanger();
  resetPheromones();
  for (it = objs.begin(); it != objs.end(); ++it)
    {
      x = (*it)->getPos().x;
      y = (*it)->getPos().y;
      if (y >= 0 && y < y_ && x >= 0 && x < x_)
        updateCaseVison(it);
    }

 //  // //  temporaire
 // std::vector<std::vector<std::pair<int, int> > >::iterator test;
 // for (test = danger_.begin(); test != danger_.end(); ++test)
 //   {
 //     std::vector<std::pair<int, int> >::iterator toto;
 //     for (toto = (*test).begin(); toto != (*test).end(); ++toto)
 // 	std::cout
 // 	  //	  <<  (*toto).first
 // 	  << (*toto).second
 // 		  << " ";
 //     std::cout << std::endl;
 //   }
 // std::cout << std::endl;
 // std::cout << std::endl;
 // std::cout << std::endl;
 // std::cout << std::endl;
 // std::cout << std::endl;
 // std::cout << std::endl;
 // std::cout << std::endl;
}

std::list<AObject*> DangerMap::getObjs(void) const
{
  return (objs_);
}

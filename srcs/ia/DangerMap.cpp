//
// DangerMap.cpp for  in /home/carpen_t/projets/c++/Bomberman
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May 25 13:57:28 2012 thibault carpentier
// Last update Sat May 26 18:00:32 2012 thibault carpentier
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
  std::cout << x << " " << y  << std::endl;
  // dangerMeth_["VelocityPowerup"] = &DangerMap::powerupDanger;
  // dangerMeth_["MinePowerup"] = &DangerMap::powerupDanger;
  // dangerMeth_["KickPowerup"] = &DangerMap::powerupDanger;
  // dangerMeth_["AmmoPowerup"] = &DangerMap::powerupDanger;
  // dangerMeth_["RangePowerup"] = &DangerMap::powerupDanger;
  // dangerMeth_["Mine"] = &DangerMap::mineDanger;
  // dangerMeth_["Explosion"] = &DangerMap::explosionDanger;
  // dangerMeth_["Player"] = &DangerMap::playerDanger;
  // dangerMeth_["Monster"] = &DangerMap::monsterDanger;
  // dangerMeth_["Brick"] = &DangerMap::blockDanger;
  // dangerMeth_["Block"] = &DangerMap::blockDanger;
  // dangerMeth_["Bomb"] = &DangerMap::bomberDanger;
  // dangerMeth_["Fireblock"] = &DangerMap::fireBlockDanger;
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

// void DangerMap::resetPheromones(void)
// {
//   std::vector<std::vector<std::pair<int, int> > >::iterator it;
//   for (int x = 0; x < x_; ++x)
//     for (int y = 0; y < y_; ++y)
//       {
// 	if (danger_[y][x].second > 0)
// 	  danger_[y][x].second -= 1;
// 	else if (danger_[y][x].second < 0)
// 	  danger_[y][x].second += 1;
//       }
// }

void DangerMap::updateDanger(const std::list<AObject*>::const_iterator &it, int x, int y)
{

  if (dangerMeth_.find((*it)->getType()) != dangerMeth_.end())
    (this->*dangerMeth_[(*it)->getType()])(it, x, y);
}

void DangerMap::updateCaseVison(const std::list<AObject*>::const_iterator &it, int x, int y)
{
  (*it)->setDanger(danger_, objs_, x_, y_);
  danger_[y][x].second = 0;
}

int  DangerMap::getDanger(int x, int y) const
{
  return (danger_[y][x].first);
}

void DangerMap::updateGameVision(const std::list<AObject*>& objs)
{
  int x, y;
  objs_ = objs;
  std::list<AObject*>::const_iterator it;

  resetDanger();
  for (it = objs.begin(); it != objs.end(); ++it)
    {
      x = static_cast<int>((*it)->getPos().x);
      y = static_cast<int>((*it)->getPos().y);
      if (y >= 0 && y < y_ && x >= 0 && x < x_)
        updateCaseVison(it, x, y);
    }

  // // //  temporaire
  std::vector<std::vector<std::pair<int, int> > >::iterator test;
  for (test = danger_.begin(); test != danger_.end(); ++test)
    {
      std::vector<std::pair<int, int> >::iterator toto;
      for (toto = (*test).begin(); toto != (*test).end(); ++toto)
  	std::cout <<  (*toto).first << (*toto).second << " ";
      std::cout << std::endl;
    }
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
}

std::list<AObject*> DangerMap::getObjs(void) const
{
  return (objs_);
}

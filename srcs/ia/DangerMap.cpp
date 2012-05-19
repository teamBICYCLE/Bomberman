//
// DangerMap.cpp for  in /home/carpen_t/projets/c++/Bomberman
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May 18 14:31:06 2012 thibault carpentier
// Last update Sat May 19 15:55:07 2012 thibault carpentier
//

#include "DangerMap.hh"

using namespace Bomberman;

DangerMap::DangerMap(int x, int y)
  : danger_(y), x_(x), y_(y)
{
  dangerMeth_["VelocityPowerup"] = &DangerMap::powerupDanger;
  dangerMeth_["MinePowerup"] = &DangerMap::powerupDanger;
  dangerMeth_["KickPowerup"] = &DangerMap::powerupDanger;
  dangerMeth_["AmmoPowerup"] = &DangerMap::powerupDanger;
  dangerMeth_["Mine"] = &DangerMap::mineDanger;
  dangerMeth_["Explosion"] = &DangerMap::explosionDanger;
  dangerMeth_["Player"] = &DangerMap::playerDanger;
  //  dangerMeth_["Monster"] = &DangerMap::

// "Monster"
// "Explosion"
// "Brick"
// "Bomb"
// "Block"


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
      danger_[y][x] = std::pair<int, int>(0, 0);
}

int DangerMap::playerDanger(const std::list<AObject*>::const_iterator &it)
{
  (void)it;
  return (-100);
}

int DangerMap::powerupDanger(const std::list<AObject*>::const_iterator &it)
{
  (void)it;
  return (-10);
}

int DangerMap::mineDanger(const std::list<AObject*>::const_iterator &it)
{
  (void)it;
  return (100);
}

int DangerMap::explosionDanger(const std::list<AObject*>::const_iterator &it)
{
  (void)it;
  return (100);
}


int DangerMap::updateDanger(const std::list<AObject*>::const_iterator &it)
{
  if (dangerMeth_.find((*it)->getType()) != dangerMeth_.end())
    return ((this->*dangerMeth_[(*it)->getType()])(it));
  return (0);
}

void DangerMap::updateGameVision(const std::list<AObject*>& objs)
{
  objs_ = objs;
  std::list<AObject*>::const_iterator it;

  resetDanger();
  for (int x = 0; x < x_; ++x)
    for (int y = 0; y < y_; ++y)
      for (it = objs.begin(); it != objs.end(); ++it)
	if (static_cast<int>((*it)->getPos().x) == x && static_cast<int>((*it)->getPos().y) == y)
	  danger_[y][x].first += updateDanger(it);

  //  temporaire
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

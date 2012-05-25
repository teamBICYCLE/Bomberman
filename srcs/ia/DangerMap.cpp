//
// DangerMap.cpp for  in /home/carpen_t/projets/c++/Bomberman
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May 18 14:31:06 2012 thibault carpentier
// Last update Thu May 24 19:20:27 2012 Jonathan Machado
//

#include <algorithm>
#include "DangerMap.hh"
#include "Bomb.hh"
#include "APowerup.hh"
#include "Mine.hh"
#include "Block.hh"
#include "Brick.hh"

using namespace Bomberman;

DangerMap::DangerMap(int x, int y)
  : danger_(y), x_(x), y_(y)
{
  dangerMeth_["VelocityPowerup"] = &DangerMap::powerupDanger;
  dangerMeth_["MinePowerup"] = &DangerMap::powerupDanger;
  dangerMeth_["KickPowerup"] = &DangerMap::powerupDanger;
  dangerMeth_["AmmoPowerup"] = &DangerMap::powerupDanger;
  dangerMeth_["RangePowerup"] = &DangerMap::powerupDanger;
  dangerMeth_["Mine"] = &DangerMap::mineDanger;
  dangerMeth_["Explosion"] = &DangerMap::explosionDanger;
  dangerMeth_["Player"] = &DangerMap::playerDanger;
  dangerMeth_["Monster"] = &DangerMap::monsterDanger;
  dangerMeth_["Brick"] = &DangerMap::blockDanger;
  dangerMeth_["Block"] = &DangerMap::blockDanger;
  dangerMeth_["Bomb"] = &DangerMap::bomberDanger;
  for (int i = 0; i < y; ++i)
    danger_[i] = std::vector<std::pair<int, int> >(x);
}

DangerMap::~DangerMap(void)
{}

void DangerMap::setDanger(int x, int y, int danger)
{
  danger_[y][x].first = (danger > danger_[y][x].first ? danger : danger_[y][x].first);
  if (danger_[y][x].first > DANGER_MAX)
    danger_[y][x].first = DANGER_MAX;
  if (danger_[y][x].first < DANGER_MIN)
    danger_[y][x].first = DANGER_MIN;
}

void DangerMap::resetDanger(void)
{
  std::vector<std::vector<std::pair<int, int> > >::iterator it;
  for (int x = 0; x < x_; ++x)
    for (int y = 0; y < y_; ++y)
      danger_[y][x] = std::pair<int, int>(0, 0);
}

Bomb	*DangerMap::isPosValid(bool &valid, int y, int x)
{
  AObject *obj;
  std::list<AObject*>::iterator i;
  std::string type;

  if (valid == true)
    {
      for(i = objs_.begin(); i != objs_.end(); ++i)
	{
	  obj = (*i);
	  if (valid && static_cast<int>(obj->getPos().x) == x && static_cast<int>(obj->getPos().y == y))
	    {
	      if (dynamic_cast<Block*>(obj) || dynamic_cast<Brick*>(obj))
		{
		  valid = false;
		  return NULL;
		}
	      else if (dynamic_cast<Bomb*>(obj))
		return static_cast<Bomb*>(obj);
	      return NULL;
	    }
	}
    }
  return NULL;
}

void DangerMap::setRangeDanger(int range, int x, int y, int danger)
{
  Bomb		*bomb;
  bool          upInvalid = true;
  bool          downInvalid = true;
  bool          leftInvalid = true;
  bool          rightInvalid = true;

  setDanger(x, y, danger);
  for (int i = 1; i <= range; ++i)
    {
      bomb = isPosValid(rightInvalid, y, x + i);
      if (bomb != NULL && danger_[y][x].first != danger_[y][x + i].first)
	setRangeDanger(bomb->getRange(), x + i, y, danger);
      if (x + i < x_  && rightInvalid)
	setDanger(x + i, y, danger);


      bomb = isPosValid(leftInvalid, y, x - i);
      if (bomb != NULL && danger_[y][x].first != danger_[y][x - i].first)
	setRangeDanger(bomb->getRange(), x - i, y, danger);
      if (x - i >= 0 && leftInvalid)
        setDanger(x - i, y, danger);


      bomb = isPosValid(downInvalid, y + i, x);
      if (bomb != NULL && danger_[y][x].first != danger_[y + i][x].first)
      	setRangeDanger(bomb->getRange(), x, y + i, danger);
      if (y + i < y_ && downInvalid)
        setDanger(x, y + i, danger);

      bomb = isPosValid(upInvalid, y - i, x);
      if (bomb != NULL && danger_[y][x].first != danger_[y - i][x].first)
       	setRangeDanger(bomb->getRange(), x, y - i, danger);
      if (y - i >= 0 && upInvalid)
        setDanger(x, y - i, danger);

    }
}

void DangerMap::bomberDanger(const std::list<AObject*>::const_iterator &it, int x, int y)
{
  Bomb *bomb = static_cast<Bomb*>(*it);

  setRangeDanger(bomb->getRange(), x, y, DANGER_BOMB);
}

void DangerMap::blockDanger(const std::list<AObject*>::const_iterator &it, int x, int y)
{
  (void)it;
  setDanger(x, y, DANGER_BLOCK);
}

void DangerMap::monsterDanger(const std::list<AObject*>::const_iterator &it, int x, int y)
{
  (void)it;
  setDanger(x, y, DANGER_MONSTER);
}

void DangerMap::playerDanger(const std::list<AObject*>::const_iterator &it, int x, int y)
{
  (void)it;
  setDanger(x, y, DANGER_PLAYER);
}

void DangerMap::powerupDanger(const std::list<AObject*>::const_iterator &it, int x, int y)
{
  (void)it;
  setDanger(x, y, DANGER_POWERUP);
}

void DangerMap::mineDanger(const std::list<AObject*>::const_iterator &it, int x, int y)
{
  (void)it;
  setDanger(x, y, DANGER_MINE);
}

void DangerMap::explosionDanger(const std::list<AObject*>::const_iterator &it, int x, int y)
{
  (void)it;
  setDanger(x, y, DANGER_EXPLOSION);
}

void DangerMap::updateDanger(const std::list<AObject*>::const_iterator &it, int x, int y)
{
  if (dangerMeth_.find((*it)->getType()) != dangerMeth_.end())
    (this->*dangerMeth_[(*it)->getType()])(it, x, y);
}

void DangerMap::updateCaseVison(const std::list<AObject*>::const_iterator &it, int x, int y)
{
  updateDanger(it, x, y);
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

  // //  temporaire
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

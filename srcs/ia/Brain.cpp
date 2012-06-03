//
// Brain.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon May 14 13:25:13 2012 thibault carpentier
// Last update Sun Jun  3 20:34:21 2012 thibault carpentier
//

#include <algorithm>
#include "Brain.hh"
#include "Block.hh"
#include "Brick.hh"
#include "Bomb.hh"
#include "Mine.hh"
#include "Monster.hh"
#include "Ghost.hh"

using namespace Bomberman;
using namespace Thinking;
using namespace LuaVirtualMachine;

Brain::Brain(int x, int y)
    : Script(), danger_(x, y), x_(x), y_(y)
{
  initLua();
}

Brain::Brain(const Brain &other)
    : Script(), danger_(other.x_, other.y_)
{
    decision_ = other.decision_;
    initLua();
    x_ = other.x_;
    y_ = other.y_;
}

Brain::Brain()
    : Script(), danger_(0, 0), x_(0), y_(0)
{
  initLua();
}

Brain::~Brain(void)
{}

Brain *Brain::instance_ = NULL;

Brain *Brain::getBrain(int x, int y)
{
  if (!instance_)
    instance_ = new Brain(x, y);
  if (x != instance_->getX() && y != instance_->getY())
    {
      destroy();
      return (getBrain(x, y));
    }
  std::cout << instance_ << std::endl;
  return (instance_);
}

void Brain::destroy()
{
  if (instance_)
    {
      delete instance_;
      instance_ = NULL;
    }
}

void Brain::initLua(void)
{
  lua_State *state = getVM().getLua();

  lua_pushinteger(state, eDirection::UP);
  lua_setglobal(state, "UP");
  lua_pushinteger(state, eDirection::RIGHT);
  lua_setglobal(state, "RIGHT");
  lua_pushinteger(state, eDirection::DOWN);
  lua_setglobal(state, "DOWN");
  lua_pushinteger(state, eDirection::LEFT);
  lua_setglobal(state, "LEFT");
  lua_pushinteger(state, eDirection::NODIR);
  lua_setglobal(state, "NODIR");
  lua_pushinteger(state, eDirection::NODIR);
  lua_setglobal(state, "NODIR");
  lua_pushinteger(state, eEnnemyType::MONSTER);
  lua_setglobal(state, "MONSTER");
  lua_pushinteger(state, eEnnemyType::GHOST);
  lua_setglobal(state, "GHOST");
  lua_pushinteger(state, DANGER_MAX);
  lua_setglobal(state, "DANGER_MAX");
  lua_pushinteger(state, DANGER_MIN);
  lua_setglobal(state, "DANGER_MIN");
  lua_pushinteger(state, MONSTER_SPEED);
  lua_setglobal(state, "SPEED");
  meth_[registerFct("isCrossable")] = &Brain::isCrossable;
  meth_[registerFct("getDanger")] = &Brain::getDanger;
  meth_[registerFct("getPheromones")] = &Brain::getPheromones;
  meth_[registerFct("showDir")] = &Brain::showDir;
  dirs_[eDirection::UP] = &Brain::showUp;
  dirs_[eDirection::DOWN] = &Brain::showDown;
  dirs_[eDirection::LEFT] = &Brain::showLeft;
  dirs_[eDirection::RIGHT] = &Brain::showRight;
  dirs_[eDirection::NODIR] = &Brain::showNodir;
}

int Brain::scriptCalling(VirtualMachine &vm, int fctNb)
{
  if (meth_.find(fctNb) != meth_.end())
    return ((this->*meth_[fctNb])(vm));
  return (-1);
}

void Brain::getReturn(VirtualMachine &vm, const std::string &strFunc)
{
  lua_State	*state = vm.getLua();

  decision_ = eDirection::NODIR;
  if (strFunc == "thinkingMonster" || strFunc == "thinkingGhost")
    {
      if (lua_gettop(state) == 1 && lua_isnumber(state, 1))
	decision_ = static_cast<eDirection>(lua_tonumber(state, 1));
    }
  return;
}

eDirection Brain::getDecision(void) const
{
  return (decision_);
}

void Brain::updateDangerMap(std::list<AObject*> &objs)
{
  (void)objs;
}

bool Brain::isParamsPosition(VirtualMachine &vm) const
{
  lua_State *state = vm.getLua();

  if (lua_gettop(state) >= 2 && lua_isnumber(state, 1) && lua_isnumber(state, 2))
    return (true);
  return (false);
}

int Brain::getPheromones(VirtualMachine &vm)
{
  int pheromones = 0;
  int x, y;

  if (isParamsPosition(vm))
    {
      x = lua_tonumber(vm.getLua(), 1);
      y = lua_tonumber(vm.getLua(), 2);
      if (x >= 0 && x < danger_.x_ && y >= 0 && y < danger_.y_)
	pheromones = danger_.getPheromones(x, y);
    }
  lua_pushnumber(vm.getLua(), pheromones);
  return (1);
}

int Brain::getDanger(VirtualMachine &vm)
{
  int danger = 2;
  int x, y;

  if (isParamsPosition(vm))
    {
      x = lua_tonumber(vm.getLua(), 1);
      y = lua_tonumber(vm.getLua(), 2);
      if (x >= 0 && x < danger_.x_ && y >= 0 && y < danger_.y_)
	danger = danger_.getDanger(x, y);
    }
  lua_pushnumber(vm.getLua(), danger);
  return (1);
}

int Brain::getX(void) const
{
    return x_;
}

int Brain::getY(void) const
{
    return y_;
}

int Brain::showDir(VirtualMachine &vm)
{
  lua_State *state = vm.getLua();
  for (int i = 0; i <= lua_gettop(state); ++i)
    {
      if (lua_isnumber(state, i))
	if (dirs_.find(lua_tonumber(state, i)) != dirs_.end())
	  (this->*dirs_[lua_tonumber(state, i)])();

    }
  return (0);
}

int Brain::isCrossable(VirtualMachine &vm)
{
  std::list<AObject*> objs = danger_.getObjs();
  int valid = -1;
  double x, y;

  if (isParamsPosition(vm) && lua_gettop(vm.getLua()) == 3)
    {
      x = lua_tonumber(vm.getLua(), 1);
      y = lua_tonumber(vm.getLua(), 2);
      BoundingBox bb(Vector3d(x, y, 0), Vector3d(0.6, 0.6, 0), NULL);

      valid = 0;
      if (x >= 0 && x < danger_.x_ && y >= 0 && y < danger_.y_)
  	{
	  valid = 1;
	  AObject *obj = NULL;
 	  for (std::list<AObject*>::iterator it = objs.begin(); it != objs.end(); ++it)
	    {
	      obj = *it;
  	      if (valid && bb.collideWith(obj))
  		{
  		  if (((lua_tonumber(vm.getLua(), 3) == MONSTER) && dynamic_cast<Brick*>(obj))
		      || dynamic_cast<Block*>(obj) || (!dynamic_cast<Mine*>(obj) && dynamic_cast<Bomb*>(obj)))
		    {
		      valid = 0;
		      break;
		    }
  		}
  	    }
  	}
    }
  lua_pushnumber(vm.getLua(), valid);
  return (1);
}

void Brain::showUp(void)
{
  std::cout << "UP" << std::endl;
}


void Brain::showDown(void)
{
  std::cout << "DOWN" << std::endl;
}


void Brain::showLeft(void)
{
  std::cout << "LEFT" << std::endl;
}


void Brain::showRight(void)
{
  std::cout << "RIGHT" << std::endl;
}


void Brain::showNodir(void)
{
  std::cout << "NODIR" << std::endl;
}

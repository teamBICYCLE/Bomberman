//
// Player.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Tue May  8 15:59:49 2012 lois burg
//

#include <algorithm>
#include "Brick.hh"
#include "Player.hh"

using namespace	Bomberman;

Player::Player(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz, "Player"), life_(1), nbBombs_(1), speed_(0.1), bombRange_(2)
{
  actionsMap_.insert(std::make_pair(gdl::Keys::Left, &Player::turnLeft));
  actionsMap_.insert(std::make_pair(gdl::Keys::Right, &Player::turnRight));
  actionsMap_.insert(std::make_pair(gdl::Keys::Up, &Player::turnUp));
  actionsMap_.insert(std::make_pair(gdl::Keys::Down, &Player::turnDown));
  actionsMap_.insert(std::make_pair(gdl::Keys::Space, &Player::putBomb));
}

Player::~Player()
{
}

void		Player::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  Vector3d	verti(0, speed_, 0);
  Vector3d	hori(speed_, 0, 0);
  Vector3d	save(pos_);
  std::map<gdl::Keys::Key, bool>	restoreMap;
  std::list<AObject*>::iterator		objIt;
  std::map<gdl::Keys::Key, void (Player::*)(std::list<AObject*>&)>::iterator it;

  (void)clock;
  restoreMap.insert(std::make_pair(gdl::Keys::Up, false));
  restoreMap.insert(std::make_pair(gdl::Keys::Down, false));
  restoreMap.insert(std::make_pair(gdl::Keys::Left, false));
  restoreMap.insert(std::make_pair(gdl::Keys::Right, false));
  for (it = actionsMap_.begin(); it != actionsMap_.end(); ++it)
    if (keys.isKeyDown(it->first))
      (this->*(it->second))(objs);
  //arreter l'iteration si tous les elements sont a true
  // if (save != pos_)
    for (objIt = objs.begin(); objIt != objs.end(); ++objIt)
      {
	//au lieu de restaurer a save, set a la valeur de l'objet que l'on collisione
	// checkLeft(*objIt, save, restoreMap);
	// checkRight(*objIt, save, restoreMap);
	// checkUp(*objIt, save, restoreMap);
	checkDown(*objIt, save, restoreMap);
      }
  // std::cout << "Player pos: " << pos_ << std::endl;
  // std::cout << "Nb objs: " << objs.size() << std::endl;
}

void		Player::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x, pos_.y, pos_.z);
  glBegin(GL_QUADS);
  glColor3ub(0, 255, 0);
  glVertex3d(0.0d, 0.0d, 0.0d);
  glVertex3d(0.0d, sz_.y, 0.0d);
  glVertex3d(sz_.x, sz_.y, 0.0d);
  glVertex3d(sz_.x, 0.0d, 0.0d);
  glEnd();
}

void	Player::checkLeft(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap)
{
  (void)obj;
  (void)save;
  if (restoreMap[gdl::Keys::Left] == false && obj->getPos().x < pos_.x)
    {
      std::cout << "Collision LEFT" << std::endl;
      pos_.x = save.x;
      restoreMap[gdl::Keys::Left] = true;
    }
}

void	Player::checkRight(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap)
{
  (void)obj;
  (void)save;
  if (restoreMap[gdl::Keys::Right] == false && obj->getPos().x > pos_.x)
    {
      std::cout << "Collision RIGHT" << std::endl;
      pos_.x = save.x;
      restoreMap[gdl::Keys::Right] = true;
    }
}

void	Player::checkUp(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap)
{
  (void)obj;
  (void)save;
  if (restoreMap[gdl::Keys::Up] == false && obj->getPos().y < pos_.y)
    {
      std::cout << "Collision UP" << std::endl;
      pos_.y = save.y;
      restoreMap[gdl::Keys::Up] = true;
    }
}

void	Player::checkDown(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap)
{
  (void)obj;
  (void)save;
  if (restoreMap[gdl::Keys::Down] == false && obj->getPos().y > pos_.y)
    {
      if ((obj->getPos().x <= pos_.x && (obj->getPos().x * obj->getSize().x + obj->getSize().x) > pos_.x * sz_.x && obj->getPos().y * obj->getSize().y < (pos_.y * sz_.y + sz_.y)) ||
	  (obj->getPos().x >= pos_.x && obj->getPos().x * obj->getSize().x < (pos_.x * sz_.x + sz_.x) && obj->getPos().y * obj->getSize().y < (pos_.y * sz_.y + sz_.y)))
	{
	  std::cout << "Collision DOWN with block at " << obj->getPos() << std::endl;
	  pos_.y = save.y;
	  restoreMap[gdl::Keys::Down] = true;
	}
    }
}

void	Player::turnLeft(std::list<AObject*>& objs)
{
  (void)objs;
  pos_ -= Vector3d(speed_, 0, 0);
}

void	Player::turnRight(std::list<AObject*>& objs)
{
  (void)objs;
  pos_ += Vector3d(speed_, 0, 0);
}

void	Player::turnUp(std::list<AObject*>& objs)
{
  (void)objs;
  pos_ -= Vector3d(0, speed_, 0);
}

void	Player::turnDown(std::list<AObject*>& objs)
{
  (void)objs;
  pos_ += Vector3d(0, speed_, 0);
}

void	Player::putBomb(std::list<AObject*>& objs)
{
  objs.push_back(new Brick(pos_, rot_));
}

const std::string&	Player::type(void) const
{
  return (type_);
}

uint	Player::getLife(void) const
{
  return (life_);
}

uint	Player::getNbBombs(void) const
{
  return (nbBombs_);
}

double	Player::getSpeed(void) const
{
  return (speed_);
}

uint	Player::getBombRange(void) const
{
  return (bombRange_);
}

void	Player::setLife(const uint life)
{
  life_ = life;
}

void	Player::setNbBombs(const uint nbBombs)
{
  nbBombs_ = nbBombs;
}

void	Player::setSpeed(const double speed)
{
  speed_ = speed;
}

void	Player::setBombRange(const uint range)
{
  bombRange_ = range;
}

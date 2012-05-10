//
// Player.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Thu May 10 11:37:38 2012 lois burg
//

#include <algorithm>
#include "Brick.hh"
#include "Player.hh"

using namespace	Bomberman;

Player::Player(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz, "Player"), life_(1), nbBombs_(1), speed_(0.05), bombRange_(2)
{
  model_ = gdl::Model::load("Ressources/assets/marvin.fbx");
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
	checkLeft(*objIt, save, restoreMap);
	checkRight(*objIt, save, restoreMap);
	checkUp(*objIt, save, restoreMap);
	checkDown(*objIt, save, restoreMap);
      }
    // std::cout << "----------------------" << std::endl;
  // std::cout << "Player pos: " << pos_ << std::endl;
  // std::cout << "Player sz: " << sz_ << std::endl;
  // std::cout << "Nb objs: " << objs.size() << std::endl;
  this->model_.update(clock);
}

#define ZIZIDEPOULE 0.5f

void		Player::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x, pos_.y, pos_.z);
  // glScaled(0.002, 0.002, 0.002);
  // glRotated(90, 1, 0, 0);
  glColor3d(0.1f, 0.50f, 0.38f);


  glBegin(GL_QUADS);
  ////////////////////////////////////////////////////////////////////////////////
  /// Configuration de la couleur des vertices
  ///////////////////////////////////////////////////////////////////////////////
  glColor3f(0.23f, 0.50f, 0.62f);
  ////////////////////////////////////////////////////////////////////////////////
  /// Dessin des vertices
  ////////////////////////////////////////////////////////////////////////////////
  glNormal3d(0, 1, 0);
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, 0);
  /// Vertex inferieur droit
  glVertex3f(0, ZIZIDEPOULE, 0);
  /// Vertex superieur droit
  glVertex3f(0, ZIZIDEPOULE, ZIZIDEPOULE);

  glColor3f(0.32f, 0.05f, 0.26f);
  glNormal3d(1, 0, 0);
  /// Vertex superieur gauche
  glVertex3f(ZIZIDEPOULE, 0, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(ZIZIDEPOULE, 0, 0);
  /// Vertex inferieur droit
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, 0);
  /// Vertex superieur droit
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  glColor3f(0.33f, 0.21f, 0.12f);
  glNormal3d(0, -1, 0);
  /// Vertex superieur gauche
  glVertex3f(0, 0, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(0, 0, 0);
  /// Vertex inferieur droit
  glVertex3f(ZIZIDEPOULE, 0, 0);
  /// Vertex superieur droit
  glVertex3f(ZIZIDEPOULE, 0, ZIZIDEPOULE);
  glColor3f(0.88f, 0.57f, 0.10f);
  glNormal3d(-1, 0, 0);
  /// Vertex superieur gauche
  glVertex3f(0, ZIZIDEPOULE, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(0, ZIZIDEPOULE, 0);
  /// Vertex inferieur droit
  glVertex3f(0, 0, 0);
  /// Vertex superieur droit
  glVertex3f(0, 0, ZIZIDEPOULE);
  glColor3f(0.32f, 0.53f, 0.21f);
  glNormal3d(0, 0, -1);
  glVertex3f(0, 0, 0);
  glVertex3f(ZIZIDEPOULE, 0, 0);
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, 0);
  glVertex3f(0, ZIZIDEPOULE, 0);
  glColor3f(0.91f, 0.18f, 0.42f);
    glNormal3d(0, 0, 1);
  glVertex3f(0, 0, ZIZIDEPOULE);
  glVertex3f(ZIZIDEPOULE, 0, ZIZIDEPOULE);
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  glVertex3f(0, ZIZIDEPOULE, ZIZIDEPOULE);
  ////////////////////////////////////////////////////////////////////////////////
  /// Fermeture du contexte de rendu
  ////////////////////////////////////////////////////////////////////////////////
  glEnd();
  
 glPopMatrix();
 glPushMatrix();
  glTranslated(pos_.x, pos_.y, pos_.z);
 glScaled(0.0028, 0.0028, 0.0028);
 glRotated(90, 1, 0, 0);

  this->model_.draw();

}

void	Player::checkLeft(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap)
{
  (void)obj;
  (void)save;
  if (restoreMap[gdl::Keys::Left] == false && obj->getPos().x < pos_.x)
    {
      // std::cout << "Collision LEFT" << std::endl;
      if ((obj->getPos().y <= pos_.y && (obj->getPos().x + obj->getSize().x) > pos_.x && (obj->getPos().y + obj->getSize().y) > pos_.y) ||
	  (obj->getPos().y > pos_.y && (obj->getPos().x + obj->getSize().x) > pos_.x && obj->getPos().y < (pos_.y + sz_.y)))
	{
	  pos_.x = save.x;
	  restoreMap[gdl::Keys::Left] = true;
	}
    }
}

void	Player::checkRight(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap)
{
  (void)obj;
  (void)save;
  if (restoreMap[gdl::Keys::Right] == false && obj->getPos().x > pos_.x)
    {
      // std::cout << "Collision RIGHT" << std::endl;
      if ((obj->getPos().y <= pos_.y && obj->getPos().x < (pos_.x + sz_.x) && (obj->getPos().y + obj->getSize().y) > pos_.y) ||
	  (obj->getPos().y > pos_.y && obj->getPos().x < (pos_.x + sz_.x) && obj->getPos().y < (pos_.y + sz_.y)))
	{
	  pos_.x = save.x;
	  restoreMap[gdl::Keys::Right] = true;
	}
    }
}

void	Player::checkUp(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap)
{
  (void)obj;
  (void)save;
  if (restoreMap[gdl::Keys::Up] == false && obj->getPos().y < pos_.y)
    {
      // std::cout << "Collision UP" << std::endl;
      if ((obj->getPos().x <= pos_.x && (obj->getPos().x + obj->getSize().x) > pos_.x && (obj->getPos().y + obj->getSize().y) > pos_.y) ||
	  (obj->getPos().x > pos_.x && obj->getPos().x < (pos_.x + sz_.x) && (obj->getPos().y + obj->getSize().y) > pos_.y))
	{
	  pos_.y = save.y;
	  restoreMap[gdl::Keys::Up] = true;
	}
    }
}

void	Player::checkDown(AObject *obj, Vector3d& save, std::map<gdl::Keys::Key, bool>& restoreMap)
{
  (void)obj;
  (void)save;
  // std::cout << obj->getPos() << std::endl;
  if (restoreMap[gdl::Keys::Down] == false && obj->getPos().y > pos_.y)
    {
      // std::cout << "This object " << obj->getPos() << " is below me: " << pos_ << std::endl;
      if ((obj->getPos().x <= pos_.x && (obj->getPos().x + obj->getSize().x) > pos_.x && obj->getPos().y < (pos_.y + sz_.y)) ||
	  (obj->getPos().x > pos_.x && obj->getPos().x < (pos_.x + sz_.x) && obj->getPos().y < (pos_.y + sz_.y)))
	{
	  // std::cout << "Collision DOWN with block at " << obj->getPos() << std::endl;
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

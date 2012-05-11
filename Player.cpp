//
// Player.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Fri May 11 15:13:35 2012 lois burg
//

#include <algorithm>
#include "Brick.hh"
#include "Bomb.hh"
#include "Player.hh"

using namespace	Bomberman;

Player::Player(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : Character(pos, rot, sz, "Player", 1, 0.05), nbBombs_(1), bombRange_(2)
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
  std::list<AObject*>::iterator		objIt;
  std::map<gdl::Keys::Key, t_playerActionFun>::iterator it;

  for (it = actionsMap_.begin(); it != actionsMap_.end(); ++it)
    if (keys.isKeyDown(it->first))
      (this->*(it->second))(objs);
  //la detection des collisions s'arrete si le joueur a retrouver sa position initiale
  if (save != pos_)
    for (objIt = objs.begin(); objIt != objs.end() && save != pos_; ++objIt)
      {
	//au lieu de restaurer a save, set a la valeur de l'objet que l'on collisione
	if (bBox_.collideWith(*objIt))
	  {
	    if (bBox_.isAbove() || bBox_.isBelow())
	      pos_.y = save.y;
	    if (bBox_.isLeft() || bBox_.isRight())
	      pos_.x = save.x;
	  }
      }
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


  glBegin(GL_LINE_LOOP);
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
  glTranslated(pos_.x + (ZIZIDEPOULE / 2.0f) , pos_.y + (ZIZIDEPOULE / 2.0f), pos_.z);
  glColor3d(1.0f, 0.0f, 0.0f);
  glScaled(0.0035, 0.0035, 0.0023);
  glRotated(90, 1, 0, 0);
  glRotated(rot_.y, 0, 1, 0);
  this->model_.draw();
}

void	Player::turnLeft(std::list<AObject*>& objs)
{
  (void)objs;
  Character::turnLeft();
  model_.play("Take 001");
}

void	Player::turnRight(std::list<AObject*>& objs)
{
  (void)objs;
  Character::turnRight();
}

void	Player::turnUp(std::list<AObject*>& objs)
{
  (void)objs;
  Character::turnUp();
}

void	Player::turnDown(std::list<AObject*>& objs)
{
  (void)objs;
  Character::turnDown();
}

void	Player::putBomb(std::list<AObject*>& objs)
{
  Bomb	*b;

  if (nbBombs_ > 0)
    {
      if ((b = new Bomb(pos_, rot_, sz_, bombRange_, 100, *this)))
	{
	  b->adjustPos();
	  objs.push_back(b);
	  --nbBombs_;
	}
    }
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

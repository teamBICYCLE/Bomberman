//
// Player.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Wed May 16 18:54:24 2012 lois burg
//

#include <algorithm>
#include "Brick.hh"
#include "Bomb.hh"
#include "Player.hh"
#include "Monster.hh"

using namespace	Bomberman;

Player::Player(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : Character(pos, rot, sz, "Player", 1, 0.05), nbBombs_(1), bombRange_(2), bombTime_(2.0f),
    moved_(false), bombCollide_(true), wasRunning_(false)
{
  isInvincible_ = true;

  bBox_ = new BoundingBox(pos_, sz_, this);
  model_ = gdl::Model::load("Ressources/assets/marvin.fbx");
  model_.cut_animation(model_, "Take 001", 0, 35, "start");
  model_.cut_animation(model_, "Take 001", 36, 54, "run");
  model_.cut_animation(model_, "Take 001", 55, 120, "stop");
  if (id_ == 0)
    {
      actionsMap_.insert(std::make_pair(gdl::Keys::A, &Player::turnLeft));
      actionsMap_.insert(std::make_pair(gdl::Keys::D, &Player::turnRight));
      actionsMap_.insert(std::make_pair(gdl::Keys::W, &Player::turnUp));
      actionsMap_.insert(std::make_pair(gdl::Keys::S, &Player::turnDown));
      actionsMap_.insert(std::make_pair(gdl::Keys::Space, &Player::putBomb));
    }
  else
    {
      actionsMap_.insert(std::make_pair(gdl::Keys::Numpad4, &Player::turnLeft));
      actionsMap_.insert(std::make_pair(gdl::Keys::Numpad6, &Player::turnRight));
      actionsMap_.insert(std::make_pair(gdl::Keys::Numpad8, &Player::turnUp));
      actionsMap_.insert(std::make_pair(gdl::Keys::Numpad5, &Player::turnDown));
      actionsMap_.insert(std::make_pair(gdl::Keys::Numpad0, &Player::putBomb));
    }
}

Player::Player()
    : Character("Player"), nbBombs_(1), bombRange_(2),
      bombTime_(2.0f), moved_(false), bombCollide_(true), wasRunning_(false)
{
  bBox_ = new BoundingBox(pos_, sz_, this);
  model_ = gdl::Model::load("Ressources/assets/marvin.fbx");
  model_.cut_animation(model_, "Take 001", 0, 35, "start");
  model_.cut_animation(model_, "Take 001", 36, 54, "run");
  model_.cut_animation(model_, "Take 001", 55, 120, "stop");
  if (id_ == 0)
    {
      actionsMap_.insert(std::make_pair(gdl::Keys::A, &Player::turnLeft));
      actionsMap_.insert(std::make_pair(gdl::Keys::D, &Player::turnRight));
      actionsMap_.insert(std::make_pair(gdl::Keys::W, &Player::turnUp));
      actionsMap_.insert(std::make_pair(gdl::Keys::S, &Player::turnDown));
      actionsMap_.insert(std::make_pair(gdl::Keys::Space, &Player::putBomb));
    }
  else
    {
      actionsMap_.insert(std::make_pair(gdl::Keys::Numpad4, &Player::turnLeft));
      actionsMap_.insert(std::make_pair(gdl::Keys::Numpad6, &Player::turnRight));
      actionsMap_.insert(std::make_pair(gdl::Keys::Numpad8, &Player::turnUp));
      actionsMap_.insert(std::make_pair(gdl::Keys::Numpad5, &Player::turnDown));
      actionsMap_.insert(std::make_pair(gdl::Keys::Numpad0, &Player::putBomb));
    }
}

Player::Player(const Player &other)
    : Character(other.pos_, other.rot_, other.sz_, "Player", other.life_, other.speed_),
      nbBombs_(other.nbBombs_), bombRange_(other.bombRange_),
      bombTime_(other.bombTime_), moved_(other.moved_), bombCollide_(other.bombCollide_),
      wasRunning_(other.wasRunning_)
{
  bBox_ = new BoundingBox(pos_, sz_, this);
  model_ = other.model_;
  actionsMap_ = other.actionsMap_;
  id_ = other.id_;
}

Player::~Player()
{
}

void		Player::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  std::list<AObject*>::iterator		objIt;
  std::map<gdl::Keys::Key, t_playerActionFun>::iterator it;
  bool		collide;

  for (it = actionsMap_.begin(); it != actionsMap_.end(); ++it)
    if (keys.isKeyDown(it->first))
      {
	save_ = pos_;
	(this->*(it->second))(objs);
	if (save_ != pos_)
	  for (objIt = objs.begin(); objIt != objs.end() && save_ != pos_; ++objIt)
	    {
	      //au lieu de restaurer a save_, set a la valeur de l'objet que l'on collisione
	      collide = bBox_->collideWith(*objIt);
	      if (!dynamic_cast<Player*>(*objIt) && collide)
		(*objIt)->interact(this);
		// {
		//   if (dynamic_cast<Explosion*>(*objIt) || dynamic_cast<Monster*>(*objIt))
		//     destroy();
		//   else if (dynamic_cast<APowerup*>(*objIt))
		//     dynamic_cast<APowerup*>(*objIt)->activate(*this);
		//   else if (!dynamic_cast<Bomb*>(*objIt) ||
		// 	   (dynamic_cast<Bomb*>(*objIt) && &dynamic_cast<Bomb*>(*objIt)->getOwner() == this && dynamic_cast<Bomb*>(*objIt)->getOwnerCollide()))
		//     {
		//       if (bBox_->isAbove() || bBox_->isBelow())
		// 	pos_.y = save_.y;
		//       if (bBox_->isLeft() || bBox_->isRight())
		// 	pos_.x = save_.x;
		//     }
		// }
	      else if (dynamic_cast<Bomb*>(*objIt) && &dynamic_cast<Bomb*>(*objIt)->getOwner() == this &&
		       !dynamic_cast<Bomb*>(*objIt)->getOwnerCollide() && !collide)
		{
		  static_cast<Bomb*>(*objIt)->setOwnerCollide(true);
		  bombCollide_ = static_cast<Bomb*>(*objIt)->getOwnerCollide();;
		}
	    }
	std::cout << "Diff: " << pos_ - save_ << std::endl;
      }
  //la detection des collisions s'arrete si le joueur a retrouver sa position initiale
  this->moveAnimation();
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
  moved_ = true;
}

void	Player::turnRight(std::list<AObject*>& objs)
{
  (void)objs;
  Character::turnRight();
  moved_ = true;
}

void	Player::turnUp(std::list<AObject*>& objs)
{
  (void)objs;
  Character::turnUp();
  moved_ = true;
}

void	Player::turnDown(std::list<AObject*>& objs)
{
  (void)objs;
  Character::turnDown();
  moved_ = true;
}

void	Player::putBomb(std::list<AObject*>& objs)
{
  Bomb	*b;

  if (nbBombs_ > 0 && bombCollide_)
    {
      if ((b = new Bomb(pos_ + (sz_ / 2), rot_, Vector3d(1,1,1), bombRange_, bombTime_, *this)))
	{
	  bombCollide_ = b->getOwnerCollide();
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

uint	Player::getNbBombs(void) const
{
  return (nbBombs_);
}

uint	Player::getBombRange(void) const
{
  return (bombRange_);
}

float	Player::getBombTime(void) const
{
  return (bombTime_);
}

void	Player::setNbBombs(const uint nbBombs)
{
  nbBombs_ = nbBombs;
}

void	Player::setBombRange(const uint range)
{
  bombRange_ = range;
}

void	Player::setBombTime(const float time)
{
  bombTime_ = time;
}

void	Player::setBombCollide(bool b)
{
  bombCollide_ = b;
}

void    Player::moveAnimation(void)
{
  if (moved_)
  {
    if (!wasRunning_ && model_.anim_is_ended("stop"))
    {
      speedAdapter_ = 5;
      model_.stop_animation("stop");
      model_.play("start");
    }
    else if (model_.anim_is_ended("start"))
    {
      model_.stop_animation("stop");
      speedAdapter_ = 100;
      model_.play("run");
    }
    speedAdapter_ += speedAdapter_ < 100 ? 1 : 0;
    wasRunning_ = true;
  }
  else if (wasRunning_ == true)
  {
    model_.play("stop");
    wasRunning_ = false;
  }
  // reset de la propriete moved.
  moved_ = false;
}

/* Serialization */

void Player::serialize(QDataStream &out) const
{
    pos_.serialize(out);
    rot_.serialize(out);
    sz_.serialize(out);
    out << removeLater_;
    out << life_;
    out << speed_;
    out << speedAdapter_;
    out << moved_;
    out << nbBombs_;
    out << bombRange_;
    out << bombTime_;
    out << bombCollide_;
    out << isInvincible_;
    out << id_;
}

void Player::unserialize(QDataStream &in)
{
    pos_.unserialize(in);
    rot_.unserialize(in);
    sz_.unserialize(in);
    in >> removeLater_;
    in >> life_;
    in >> speed_;
    in >> speedAdapter_;
    in >> moved_;
    in >> nbBombs_;
    in >> bombRange_;
    in >> bombTime_;
    in >> bombCollide_;
    in >> isInvincible_;
    in >> id_;
}

void Player::sInit(void)
{
    qRegisterMetaTypeStreamOperators<Player>("Player");
    qMetaTypeId<Player>();
}

QDataStream &operator<<(QDataStream &out, const Player &v)
{
    v.serialize(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Player &v)
{
    v.unserialize(in);
    return in;
}

/* TMP */

void Player::aff(void) const
{
    std::cout << "=== START PLAYER ===" << std::endl;
    std::cout << "nbBombs : " << nbBombs_ << std::endl;
    std::cout << "bombRange : " << bombRange_ << std::endl;
    std::cout << "bombTime : " << bombTime_ << std::endl;
    std::cout << "moved : " << moved_ << std::endl;
    std::cout << "bombCollide : " << bombCollide_ << std::endl;
    std::cout << "life : " << life_ << std::endl;
    std::cout << "speed : " << speed_ << std::endl;
    std::cout << "speed adapt : " << speedAdapter_ << std::endl;
    std::cout << "moved : " << moved_ << std::endl;
    std::cout << "pos : " << pos_ << std::endl;
    std::cout << "rot : " << rot_ << std::endl;
    std::cout << "size : " << sz_ << std::endl;
    std::cout << "type : " << type_ << std::endl;
    std::cout << "=== END PLAYER ===" << std::endl;
}

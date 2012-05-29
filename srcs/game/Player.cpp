//
// Player.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Tue May 29 16:00:10 2012 Jonathan Machado
//

#include <algorithm>
#include "Brick.hh"
#include "Bomb.hh"
#include "Mine.hh"
#include "Player.hh"
#include "Monster.hh"
#include "ModelHandler.hh"
#include "SaveHandler.hh"

using namespace	Bomberman;

bool allowLoading_ = true;

Player::Player(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : Character(pos, rot, sz, "Player", 1, 0.05), nbBombs_(1), nbMines_(0), bombRange_(2),
    bombTime_(2.0f), moved_(false), bombCollide_(true), wasRunning_(false), score_(0), kickAbility_(false),
    model_(ModelHandler::get().getModel("bombman")), isNetworkControlled_(false)
{
  //isInvincible_ = true;
  //kickAbility_ = true;
  //nbBombs_ = 5;
  //nbMines_ = 10;

  std::cout << "id : " << id_ << std::endl;
  bBox_ = new BoundingBox(pos_, sz_, this);

  collideMap_.insert(std::make_pair(conf_.get(K_LEFT, id_), &BoundingBox::collideLeft));
  collideMap_.insert(std::make_pair(conf_.get(K_RIGHT, id_), &BoundingBox::collideRight));
  collideMap_.insert(std::make_pair(conf_.get(K_UP, id_), &BoundingBox::collideUp));
  collideMap_.insert(std::make_pair(conf_.get(K_DOWN, id_), &BoundingBox::collideDown));

  actionsMap_.insert(std::make_pair(conf_.get(K_LEFT, id_), &Player::turnLeft));
  actionsMap_.insert(std::make_pair(conf_.get(K_RIGHT, id_), &Player::turnRight));
  actionsMap_.insert(std::make_pair(conf_.get(K_UP, id_), &Player::turnUp));
  actionsMap_.insert(std::make_pair(conf_.get(K_DOWN, id_), &Player::turnDown));
  actionsMap_.insert(std::make_pair(conf_.get(K_PUT_BOMB, id_), &Player::putBomb));
  actionsMap_.insert(std::make_pair(conf_.get(K_PUT_MINE, id_), &Player::putMine));
  actionsMap_.insert(std::make_pair(conf_.get(K_SAVE, id_), &Player::saveGame));
  actionsMap_.insert(std::make_pair(conf_.get(K_LOAD, id_), &Player::loadGame));

  networkMap_.insert(std::make_pair(conf_.get(K_LEFT, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_RIGHT, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_UP, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_DOWN, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_PUT_BOMB, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_PUT_MINE, id_), false));
}

Player::Player()
  : Character("Player"), nbBombs_(1), nbMines_(0), bombRange_(2),
    bombTime_(2.0f), moved_(false), bombCollide_(true), wasRunning_(false),
    score_(0), kickAbility_(false), model_(ModelHandler::get().getModel("bombman")), isNetworkControlled_(false)
{
  bBox_ = new BoundingBox(pos_, sz_, this);

  collideMap_.insert(std::make_pair(conf_.get(K_LEFT, id_), &BoundingBox::collideLeft));
  collideMap_.insert(std::make_pair(conf_.get(K_RIGHT, id_), &BoundingBox::collideRight));
  collideMap_.insert(std::make_pair(conf_.get(K_UP, id_), &BoundingBox::collideUp));
  collideMap_.insert(std::make_pair(conf_.get(K_DOWN, id_), &BoundingBox::collideDown));

  actionsMap_.insert(std::make_pair(conf_.get(K_LEFT, id_), &Player::turnLeft));
  actionsMap_.insert(std::make_pair(conf_.get(K_RIGHT, id_), &Player::turnRight));
  actionsMap_.insert(std::make_pair(conf_.get(K_UP, id_), &Player::turnUp));
  actionsMap_.insert(std::make_pair(conf_.get(K_DOWN, id_), &Player::turnDown));
  actionsMap_.insert(std::make_pair(conf_.get(K_PUT_BOMB, id_), &Player::putBomb));
  actionsMap_.insert(std::make_pair(conf_.get(K_PUT_MINE, id_), &Player::putMine));
  actionsMap_.insert(std::make_pair(conf_.get(K_SAVE, id_), &Player::saveGame));
  actionsMap_.insert(std::make_pair(conf_.get(K_LOAD, id_), &Player::loadGame));

  networkMap_.insert(std::make_pair(conf_.get(K_LEFT, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_RIGHT, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_UP, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_DOWN, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_PUT_BOMB, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_PUT_MINE, id_), false));
}

Player::Player(const Player &other)
    : Character(other.pos_, other.rot_, other.sz_, "Player", other.life_, other.speed_),
      nbBombs_(other.nbBombs_), nbMines_(other.nbMines_), bombRange_(other.bombRange_),
      bombTime_(other.bombTime_), moved_(other.moved_),
      bombCollide_(other.bombCollide_), wasRunning_(other.wasRunning_), score_(other.score_),
      kickAbility_(other.kickAbility_), model_(other.model_), isNetworkControlled_(other.isNetworkControlled_)
{
  isInvincible_ = other.isInvincible_;
  bBox_ = new BoundingBox(pos_, sz_, this);
  actionsMap_ = other.actionsMap_;
  collideMap_ = other.collideMap_;
  networkMap_ = other.networkMap_;
  id_ = other.id_;
}

Player::~Player()
{
}

void		Player::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  bool		collide;
  std::list<AObject*>::iterator		objIt;
  std::map<gdl::Keys::Key, t_playerActionFun>::iterator it;

  for (it = actionsMap_.begin(); life_ && it != actionsMap_.end(); ++it)
    if (keys.isKeyDown(it->first) || (isNetworkControlled_ && networkMap_[it->first]))
      {
        save_ = pos_;
        (this->*(it->second))(objs);
        if (save_ != pos_)
          for (objIt = objs.begin(); objIt != objs.end() && save_ != pos_; ++objIt)
            {
              //au lieu de restaurer a save_, set a la valeur de l'objet que l'on collisione
              collide = bBox_->collideWith(*objIt);
              bBox_->resetColliding();
              (bBox_->*collideMap_[it->first])((*objIt)->getPos(), (*objIt)->getSize());
              if (!dynamic_cast<Player*>(*objIt) && collide)
                (*objIt)->interact(this, objs);
              else if (dynamic_cast<Bomb*>(*objIt) && &static_cast<Bomb*>(*objIt)->getOwner() == this &&
                       !static_cast<Bomb*>(*objIt)->getOwnerCollide() && !collide)
                {
                  static_cast<Bomb*>(*objIt)->setOwnerCollide(true);
                  bombCollide_ = static_cast<Bomb*>(*objIt)->getOwnerCollide();;
                }
              bBox_->resetColliding();
            }
      }
  //la detection des collisions s'arrete si le joueur a retrouver sa position initiale
  this->moveAnimation();
  this->model_.update(clock);
}

void		Player::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x + (0.5f / 2.0f) , pos_.y + (0.5f / 2.0f), pos_.z);
  glScaled(0.0035, 0.0035, 0.0023);
  glRotated(90, 1, 0, 0);
  glRotated(rot_.y, 0, 1, 0);
  this->model_.draw();
  glColor3d(1.0f, 1.0f, 1.0f);
}

void	Player::interact(Character *ch, std::list<AObject*>& objs)
{
  (void)objs;
  if (dynamic_cast<Monster*>(ch))
    takeDamage(static_cast<Monster*>(ch)->getDamage());
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
      if ((b = new Bomb(pos_ + (sz_ / 2), rot_, Vector3d(1, 1, 1), bombRange_, bombTime_, *this)))
      {
          bombCollide_ = b->getOwnerCollide();
          b->adjustPos();
          objs.push_back(b);
          --nbBombs_;
        }
    }
}

void	Player::putMine(std::list<AObject*>& objs)
{
  Mine	*m;

  if (nbMines_ > 0 && bombCollide_)
    {
      if ((m = new Mine(pos_ + (sz_ / 2), rot_, Vector3d(1, 1, 1), *this)))
	{
	  bombCollide_ = m->getOwnerCollide();
	  m->adjustPos();
	  objs.push_back(m);
	  --nbMines_;
	}
    }
}

void	Player::saveGame(std::list<AObject*>& objs)
{
    SaveHandler s;

    s.save(objs);
    allowLoading_ = true;
}

void	Player::loadGame(std::list<AObject*>& objs)
{
    if (allowLoading_ == true)
    {
        SaveHandler s;
        std::list<AObject*>::iterator it;
        std::list<AObject*> newList;

        for (it = objs.begin(); it != objs.end(); it++)
            (*it)->removeLater_ = true;

        newList = *(s.load(s.getSavedFiles().front().second));

        objs.insert(objs.end(), newList.begin(), newList.end());
        std::cout << "end" << std::endl;
        allowLoading_ = false;
    }
}

uint	Player::getNbBombs(void) const
{
  return (nbBombs_);
}

int	Player::getNbMines(void) const
{
  return (nbMines_);
}

uint	Player::getBombRange(void) const
{
  return (bombRange_);
}

float	Player::getBombTime(void) const
{
  return (bombTime_);
}

int	Player::getScoreValue(void) const
{
  return (5);
}

int	Player::getScore(void) const
{
  return (score_);
}

bool	Player::getKickAbility(void) const
{
  return (kickAbility_);
}

bool	Player::isNetworkControlled(void) const
{
  return (isNetworkControlled_);
}

void	Player::setNbBombs(const uint nb)
{
  nbBombs_ = nb;
}

void	Player::setNbMines(const int nb)
{
  nbMines_ = nb;
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

void	Player::addScore(int val)
{
  score_ += val;
  std::cout << "Score: " << score_ << std::endl;
}

void	Player::setKickAbility(bool b)
{
  kickAbility_ = b;
}

void	Player::setNetworkControlled(bool b)
{
  isNetworkControlled_ = b;
}

void    Player::moveAnimation(void)
{
  if (moved_)
  {
    if (!wasRunning_ && model_.getModel().anim_is_ended("stop"))
    {
      speedAdapter_ = 5;
      model_.getModel().stop_animation("stop");
      model_.getModel().play("start");
    }
    else if (model_.getModel().anim_is_ended("start"))
    {
      model_.getModel().stop_animation("stop");
      speedAdapter_ = 100;
      model_.getModel().play("run");
    }
    speedAdapter_ += speedAdapter_ < 100 ? 1 : 0;
    wasRunning_ = true;
  }
  else if (wasRunning_ == true)
  {
    model_.getModel().play("stop");
    wasRunning_ = false;
  }
  // reset de la propriete moved.
  moved_ = false;
}

Online::Packet	Player::pack(gdl::Input& keys)
{
  Online::Packet	p;

  p.type = Online::PlayerPkt;
  p.id = id_;
  p.x = pos_.x;
  p.y = pos_.y;
  p.z = pos_.z;
  p.up = keys.isKeyDown(conf_.get(K_UP, id_));
  p.down = keys.isKeyDown(conf_.get(K_DOWN, id_));
  p.left = keys.isKeyDown(conf_.get(K_LEFT, id_));
  p.right = keys.isKeyDown(conf_.get(K_RIGHT, id_));
  p.bomb = keys.isKeyDown(conf_.get(K_PUT_BOMB, id_));
  p.mine = keys.isKeyDown(conf_.get(K_PUT_MINE, id_));
  return (p);
}

void	Player::applyPacket(const Online::Packet& p, gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  // pos_.x = p.x;
  // pos_.y = p.y;
  // pos_.z = p.z;
  networkMap_[conf_.get(K_UP, id_)] = p.up;
  networkMap_[conf_.get(K_DOWN, id_)] = p.down;
  networkMap_[conf_.get(K_LEFT, id_)] = p.left;
  networkMap_[conf_.get(K_RIGHT, id_)] = p.right;
  networkMap_[conf_.get(K_PUT_BOMB, id_)] = p.bomb;
  networkMap_[conf_.get(K_PUT_MINE, id_)] = p.mine;
  update(clock, keys, objs);
  resetNetKeys();
}

void	Player::setNetLeftPressed(bool b)
{
  networkMap_[conf_.get(K_LEFT, id_)] = b;
}

void	Player::setNetRightPressed(bool b)
{
  networkMap_[conf_.get(K_RIGHT, id_)] = b;
}

void	Player::setNetUpPressed(bool b)
{
  networkMap_[conf_.get(K_UP, id_)] = b;
}

void	Player::setNetDownPressed(bool b)
{
  networkMap_[conf_.get(K_DOWN, id_)] = b;
}

void	Player::setNetBombPressed(bool b)
{
  networkMap_[conf_.get(K_PUT_BOMB, id_)] = b;
}

void	Player::setNetMinePressed(bool b)
{
  networkMap_[conf_.get(K_PUT_MINE, id_)] = b;
}

void	Player::resetNetKeys(void)
{
  setNetLeftPressed(false);
  setNetRightPressed(false);
  setNetUpPressed(false);
  setNetDownPressed(false);
  setNetBombPressed(false);
  setNetMinePressed(false);
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
    out << isInvincible_;
    out << id_;

    out << nbBombs_;
    out << nbMines_;
    out << bombRange_;
    out << bombTime_;
    out << bombCollide_;

    out << wasRunning_;
    out << score_;
    out << kickAbility_;
    out << isNetworkControlled_;
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
    in >> isInvincible_;
    in >> id_;

    in >> nbBombs_;
    in >> nbMines_;
    in >> bombRange_;
    in >> bombTime_;
    in >> bombCollide_;

    in >> wasRunning_;
    in >> score_;
    in >> kickAbility_;
    in >> isNetworkControlled_;
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

void    Player::toQvariant(QSettings &w) const
{
    w.setValue("Player", qVariantFromValue(*this));
}

void	Player::setDanger(std::vector<std::vector<std::pair<int, int> > > &map,
			  std::list<AObject*>objs,
			  int x, int y) const
{
  (void)objs;
  (void)x;
  (void)y;
  setDangerMap(getPos().x, getPos().y, DANGER_PLAYER, map);
}

void	Player::setVirtualPheromones(std::vector<std::vector<std::pair<int, int> > > &map,
				     std::list<AObject*>objs,
				     int x, int y) const
{
  (void)objs;
  map[pos_.y][pos_.x].second = PHEROMONE_PLAYER;
  if (pos_.y < y - 1)
      map[pos_.y + 1][pos_.x].second = PHEROMONE_PLAYER - 1;
  if (pos_.x < x && pos_.y < y - 1)
    map[pos_.y + 1][pos_.x + 1].second = PHEROMONE_PLAYER - 1;
  if (pos_.x < x - 1)
    map[pos_.y][pos_.x + 1].second = PHEROMONE_PLAYER - 1;
  if (pos_.y > 0)
      map[pos_.y - 1][pos_.x].second = PHEROMONE_PLAYER - 1;
  if (pos_.x > 0 && pos_.y > 0)
    map[pos_.y - 1][pos_.x - 1].second = PHEROMONE_PLAYER - 1;
  if (pos_.x > 0)
    map[pos_.y][pos_.x - 1].second = PHEROMONE_PLAYER - 1;
  if (pos_.x > 0 && pos_.y < y - 1)
    map[pos_.y + 1][pos_.x - 1].second = PHEROMONE_PLAYER - 1;
}

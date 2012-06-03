//
// Player.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Sun Jun  3 09:46:40 2012 thibault carpentier
//

#include <algorithm>
#include <cstdlib>
#include "Brick.hh"
#include "Bomb.hh"
#include "Mine.hh"
#include "Player.hh"
#include "Monster.hh"
#include "ModelHandler.hh"
#include "SaveHandler.hh"
#include "Sounds.hh"

using namespace	Bomberman;

Player::Player(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : Character(pos, rot, sz, "Player", 1, 0.05), nbBombs_(1), nbMines_(0), bombRange_(2),
    bombTime_(3.0f), moved_(false), bombCollide_(true), wasRunning_(false), score_(0), kickAbility_(false),
    model_(ModelHandler::get().getModel("bombman")), hud_(ModelHandler::get().getModel("hud")),
    isNetworkControlled_(false)
{
  srand(((id_ + 5) * 111) - 8);
  color_ = Vector3d(static_cast<float>(rand() % 101) / 100
                    , static_cast<float>(rand() % 101) / 100,
                    static_cast<float>(rand() % 101) / 100);
  //std::cout << color_.x << std::endl;
  isInvincible_ = true;
  // kickAbility_ = true;
  // nbBombs_ = 5;
  // nbMines_ = 10000;

  std::cout << "id : " << id_ << std::endl;
  bBox_ = new BoundingBox(pos_, sz_, this);

  scoreTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  scoreTxt_.setSize(24);

  bombTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  bombTxt_.setSize(14);
  mineTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  mineTxt_.setSize(14);
  speedTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  speedTxt_.setSize(14);
  rangeTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  rangeTxt_.setSize(14);
  kickTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  kickTxt_.setSize(14);
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
    score_(0), kickAbility_(false), model_(ModelHandler::get().getModel("bombman")),
    hud_(ModelHandler::get().getModel("hud")), isNetworkControlled_(false)
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

  networkMap_.insert(std::make_pair(conf_.get(K_LEFT, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_RIGHT, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_UP, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_DOWN, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_PUT_BOMB, id_), false));
  networkMap_.insert(std::make_pair(conf_.get(K_PUT_MINE, id_), false));

  scoreTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  scoreTxt_.setSize(24);

  bombTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  bombTxt_.setSize(14);
  mineTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  mineTxt_.setSize(14);
  speedTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  speedTxt_.setSize(14);
  rangeTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  rangeTxt_.setSize(14);
  kickTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  kickTxt_.setSize(14);
}

Player::Player(const Player &other)
    : Character(other.pos_, other.rot_, other.sz_, "Player", other.life_, other.speed_),
      nbBombs_(other.nbBombs_), nbMines_(other.nbMines_), bombRange_(other.bombRange_),
      bombTime_(other.bombTime_), moved_(other.moved_),
      bombCollide_(other.bombCollide_), wasRunning_(other.wasRunning_), score_(other.score_),
      kickAbility_(other.kickAbility_), model_(other.model_), hud_(other.hud_), isNetworkControlled_(other.isNetworkControlled_),
      color_(other.color_)
{
  isInvincible_ = other.isInvincible_;
  bBox_ = new BoundingBox(pos_, sz_, this);
  actionsMap_ = other.actionsMap_;
  collideMap_ = other.collideMap_;
  networkMap_ = other.networkMap_;
  id_ = other.id_;

  scoreTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  scoreTxt_.setSize(24);

  bombTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  bombTxt_.setSize(14);
  mineTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  mineTxt_.setSize(14);
  speedTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  speedTxt_.setSize(14);
  rangeTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  rangeTxt_.setSize(14);
  kickTxt_.setFont("Ressources/Fonts/Dimbo.ttf");
  kickTxt_.setSize(14);
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
              if ((*objIt)->getType() != "Player" && collide)
                (*objIt)->interact(this, objs);
              else if ((*objIt)->getType() == "Bomb" && &static_cast<Bomb*>(*objIt)->getOwner() == this &&
                       !static_cast<Bomb*>(*objIt)->getOwnerCollide() && !collide)
                {
                  static_cast<Bomb*>(*objIt)->setOwnerCollide(true);
                  bombCollide_ = static_cast<Bomb*>(*objIt)->getOwnerCollide();;
                }
              bBox_->resetColliding();
            }
      }
  //la detection des collisions s'arrete si le joueur a retrouver sa position initiale
  this->model_.getModel().set_anim_speed("run", 1 + this->speed_);
  this->model_.getModel().set_anim_speed("start", 1 + this->speed_);
  this->model_.getModel().set_anim_speed("stop", 1 + this->speed_);
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
  //glColor3d(color_.x, color_.y, color_.z);
  this->model_.getModel().set_default_model_color(gdl::Color(255 * color_.x, 255 * color_.y, 255 * color_.z));
  this->model_.draw();
  glColor3d(1.0f, 1.0f, 1.0f);
}

void Player::drawHud()
{
  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);
  glMatrixMode(GL_PROJECTION);
  //glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, 1600, 0, 900);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (id_ % 2 == 0)
    glTranslated(0, 693, 0);
  if (id_ > 1)
    glTranslated(1350, 0, 0);
  glDisable(GL_TEXTURE_2D);
  glColor3d(color_.x, color_.y, color_.z);
  glBegin(GL_POLYGON);
  glVertex2d(32, 207 - 23);
  glVertex2d(45, 207 - 25);
  glVertex2d(56, 207 - 38);
  glVertex2d(67, 207 - 56);
  glVertex2d(32, 207 - 82);
  glVertex2d(20, 207 - 79);
  glVertex2d(7, 207 - 68);
  glVertex2d(3, 207 - 56);
  glVertex2d(5, 207 - 41);
  glVertex2d(14, 207 - 28);
  glVertex2d(24, 207 - 23);
  glEnd();
  glEnable(GL_TEXTURE_2D);
  glScaled(1, 1, 1);
  hud_.draw();
  //glPopMatrix();

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
}

void Player::drawHudText()
{
  std::stringstream	ss;
  int                   offsetx = 0, offsety = 0;

  if (id_ % 2 == 1)
    offsety = 693;
  if (id_ > 1)
    offsetx = 1350;
  ss << score_;
  scoreTxt_.setText(ss.str());
  scoreTxt_.setPosition(offsetx + 45, offsety + 165);
  scoreTxt_.draw();

  ss.str("");
  ss.clear();
  ss << nbBombs_;
  bombTxt_.setSize(14);
  bombTxt_.setText(ss.str());
  bombTxt_.setPosition(offsetx + 146, offsety + 28);
  bombTxt_.draw();

  ss.str("");
  ss.clear();
  ss << nbMines_;
  mineTxt_.setSize(14);
  mineTxt_.setText(ss.str());
  mineTxt_.setPosition(offsetx + 204, offsety + 64);
  mineTxt_.draw();

  ss.str("");
  ss.clear();
  ss << (speed_ * 20) * 12 << " mph";
  speedTxt_.setSize(14);
  speedTxt_.setText(ss.str());
  speedTxt_.setPosition(offsetx + 197, offsety + 104);
  speedTxt_.draw();

  ss.str("");
  ss.clear();
  ss << "+" << bombRange_;
  rangeTxt_.setSize(14);
  rangeTxt_.setText(ss.str());
  rangeTxt_.setPosition(offsetx + 183, offsety + 143);
  rangeTxt_.draw();

  ss.str("");
  ss.clear();
  ss << (kickAbility_ ? "Yes" : "No");
  kickTxt_.setSize(14);
  kickTxt_.setText(ss.str());
  kickTxt_.setPosition(offsetx + 150, offsety + 183);
  kickTxt_.draw();
}

void	Player::interact(Character *ch, std::list<AObject*>& objs)
{
  (void)objs;
  if (ch->getType() == "Monster")
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
  return (50);
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
      Sounds::instance().playEffect("run", 0.1);
    }
    else if (model_.getModel().anim_is_ended("start"))
    {
      model_.getModel().stop_animation("stop");
      speedAdapter_ = 100;
      model_.getModel().play("run");
      Sounds::instance().playEffect("run", 0.1);
    }
    speedAdapter_ += speedAdapter_ < 100 ? 1 : 0;
    wasRunning_ = true;
  }
  else if (wasRunning_ == true)
  {
    model_.getModel().play("stop");
    Sounds::instance().stopEffect("run");
    wasRunning_ = false;
  }
  // reset de la propriete moved.
  moved_ = false;
}

Online::Packet	Player::pack(gdl::Input& keys)
{
  Online::Packet	p;

  p.id = id_;
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
  networkMap_[conf_.get(K_UP, id_)] = p.up;
  networkMap_[conf_.get(K_DOWN, id_)] = p.down;
  networkMap_[conf_.get(K_LEFT, id_)] = p.left;
  networkMap_[conf_.get(K_RIGHT, id_)] = p.right;
  networkMap_[conf_.get(K_PUT_BOMB, id_)] = p.bomb;
  networkMap_[conf_.get(K_PUT_MINE, id_)] = p.mine;
  update(clock, keys, objs);
  resetNetKeys();
}

void	Player::resetNetKeys(void)
{
  networkMap_[conf_.get(K_UP, id_)] = false;
  networkMap_[conf_.get(K_DOWN, id_)] = false;
  networkMap_[conf_.get(K_LEFT, id_)] = false;
  networkMap_[conf_.get(K_RIGHT, id_)] = false;
  networkMap_[conf_.get(K_PUT_BOMB, id_)] = false;
  networkMap_[conf_.get(K_PUT_MINE, id_)] = false;
}

/* Serialization */

void Player::serialize(QDataStream &out) const
{
    pos_.serialize(out);
    rot_.serialize(out);
    sz_.serialize(out);
    color_.serialize(out);
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
    color_.unserialize(in);
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
  if (pos_.y < y - 1)
    map[pos_.y + 1][pos_.x].second = PHEROMONE_PLAYER - 10;
  if (pos_.x < x - 1 && pos_.y < y - 1)
    map[pos_.y + 1][pos_.x + 1].second = PHEROMONE_PLAYER - 20;
  if (pos_.x < x - 1)
    map[pos_.y][pos_.x + 1].second = PHEROMONE_PLAYER - 10;
  if (pos_.y > 0)
    map[pos_.y - 1][pos_.x].second = PHEROMONE_PLAYER - 10;
  if (pos_.x > 0 && pos_.y > 0)
    map[pos_.y - 1][pos_.x - 1].second = PHEROMONE_PLAYER - 20;
  if (pos_.x > 0)
    map[pos_.y][pos_.x - 1].second = PHEROMONE_PLAYER - 10;
  if (pos_.x > 0 && pos_.y < y - 1)
    map[pos_.y + 1][pos_.x - 1].second = PHEROMONE_PLAYER - 20;
  if (pos_.x < x - 1 && pos_.y > 0)
    map[pos_.y - 1][pos_.x + 1].second = PHEROMONE_PLAYER - 20;
  map[pos_.y][pos_.x].second = PHEROMONE_PLAYER;
}

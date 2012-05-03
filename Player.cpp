//
// Player.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Thu May  3 16:49:00 2012 lois burg
//

#include "Player.hh"

using namespace	Bomberman;

Player::Player(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz,"Player"), life_(1), nbBombs_(1), speed_(1), bombRange_(2)
{
}

Player::~Player()
{
}

void		Player::update(gdl::GameClock& clock, gdl::Input& keys)
{
  (void)clock;
  (void)keys;
  std::cout << "Player update" << std::endl;
  if (keys.isKeyDown(gdl::Keys::Up))
    pos_ -= Vector3d(0, 1, 0);
  if (keys.isKeyDown(gdl::Keys::Down))
    pos_ += Vector3d(0, 1, 0);
  if (keys.isKeyDown(gdl::Keys::Left))
    pos_ -= Vector3d(1, 0, 0);
  if (keys.isKeyDown(gdl::Keys::Right))
    pos_ += Vector3d(1, 0, 0);
}

void		Player::draw(void)
{
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

int	Player::getSpeed(void) const
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

void	Player::setSpeed(const int speed)
{
  speed_ = speed;
}

void	Player::setBombRange(const uint range)
{
  bombRange_ = range;
}

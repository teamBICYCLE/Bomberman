//
// Brick.cpp for Brick in /home/sylvia_r//Desktop/projet/tek2/Bomberman
//
// Made by romain sylvian
// Login   <sylvia_r@epitech.net>
//
// Started on  Thu May  3 15:17:56 2012 romain sylvian
// Last update Fri May  4 10:53:07 2012 lois burg
//

#include "Brick.hh"

using namespace	Bomberman;


Brick::Brick(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
    : AObject(pos, rot, sz,"Brick")
{
    PowerupFactory *factory = PowerupFactory::getInstance();

    loot_ = factory->create();
    if (loot_ != NULL)
    {
        loot_->setPos(pos);
        loot_->setRot(rot);
        loot_->setSize(sz);
        std::cout << "Loot find ! pos brick : " << loot_->getPos() << std::endl;
    }
}

Brick::~Brick()
{
    if (loot_ != NULL)
    {
        std::cout << "Brick" << pos_ << " | Loot" << loot_->getPos() << std::endl;
    }
}

void		Brick::update(gdl::GameClock& clock, gdl::Input& keys)
{
  (void)clock;
  (void)keys;
}

void		Brick::draw(void)
{

}

const std::string&	Brick::type(void) const
{
  return (type_);
}

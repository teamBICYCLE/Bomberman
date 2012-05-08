//
// Brick.cpp for Brick in /home/sylvia_r//Desktop/projet/tek2/Bomberman
//
// Made by romain sylvian
// Login   <sylvia_r@epitech.net>
//
// Started on  Thu May  3 15:17:56 2012 romain sylvian
// Last update Tue May  8 15:32:28 2012 geoffroy lafontaine
//

#include "Brick.hh"

using namespace	Bomberman;

#include <GL/gl.h>

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
    }
}

Brick::~Brick()
{

}

void		Brick::update(gdl::GameClock& clock, gdl::Input& keys)
{
  (void)clock;
  (void)keys;
}

void		Brick::draw(void)
{
  std::cout << "Drawing brick" << std::endl;
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x, pos_.y, pos_.z);
  glBegin(GL_QUADS);
  glColor3ub(255, 0, 0);
  glVertex3d(0.0d, 0.0d, 0.0d);
  glVertex3d(0.0d, sz_.y, 0.0d);
  glVertex3d(sz_.x, sz_.y, 0.0d);
  glVertex3d(sz_.x, 0.0d, 0.0d);
  glEnd();
}

const std::string&	Brick::type(void) const
{
  return (type_);
}

void Brick::loot(std::vector<AObject *> &objs)
{
    if (loot_ != NULL)
    {
        std::cout << "Loot add to Vector !" << std::endl;
        objs.push_back(loot_);
    }
}

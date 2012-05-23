//
// Brick.cpp for Brick in /home/sylvia_r//Desktop/projet/tek2/Bomberman
//
// Made by romain sylvian
// Login   <sylvia_r@epitech.net>
//
// Started on  Thu May  3 15:17:56 2012 romain sylvian
// Last update Sun May 20 17:49:45 2012 lois burg
//

#include <GL/gl.h>
#include "Brick.hh"
#include "ModelHandler.hh"

using namespace	Bomberman;

Brick::Brick(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz, "Brick"), model_(ModelHandler::get().getModel("cube"))
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

Brick::Brick(const Brick &other)
  : AObject(other.pos_, other.rot_, other.sz_, "Brick"), model_(other.model_)
{
    PowerupFactory *factory = PowerupFactory::getInstance();

    loot_ = factory->create();
    if (loot_ != NULL)
    {
        loot_->setPos(other.pos_);
        loot_->setRot(other.rot_);
        loot_->setSize(other.sz_);
    }
}

Brick::Brick()
    : AObject(Vector3d(), Vector3d(), Vector3d(), "Brick"), model_(ModelHandler::get().getModel("cube"))
{
}

Brick::~Brick()
{

}

void		Brick::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
  model_.update(clock);
}

#define ZIZIDEPOULE 1.0f

void		Brick::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  glColor3f(0.35f, 0.23f, 0.54f);
  model_.draw();
  glColor3f(1, 1, 1);
}

void Brick::loot(std::list<AObject *> &objs)
{
    if (loot_ != NULL)
    {
        std::cout << "Loot add to Vector !" << std::endl;
        objs.push_back(loot_);
    }
}

void	Brick::destroy(std::list<AObject*>& objs)
{
  loot(objs);
  AObject::destroy();
}

void	Brick::interact(Explosion *e, std::list<AObject*>& objs)
{
  (void)e;
  destroy(objs);
}

/* Serialization */

void Brick::serialize(QDataStream &out) const
{
    pos_.serialize(out);
    rot_.serialize(out);
    sz_.serialize(out);
    out << removeLater_;
}

void Brick::unserialize(QDataStream &in)
{
    pos_.unserialize(in);
    rot_.unserialize(in);
    sz_.unserialize(in);
    in >> removeLater_;
}

void Brick::sInit(void)
{
    qRegisterMetaTypeStreamOperators<Brick>("Brick");
    qMetaTypeId<Brick>();
}

QDataStream &operator<<(QDataStream &out, const Brick &v)
{
    v.serialize(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Brick &v)
{
    v.unserialize(in);
    return in;
}

void    Brick::toQvariant(QSettings &w)
{
    w.setValue("Brick", qVariantFromValue(*this));
}

/* TMP */
void Brick::aff(void) const
{
    std::cout << "=== START BRICK ===" << std::endl;
    std::cout << "Pos : " << pos_.x << " " << pos_.y << " " << pos_.z << std::endl;
    std::cout << "Rot : " << rot_.x << " " << rot_.y << " " << rot_.z << std::endl;
    std::cout << "Size : " << sz_.x << " " << sz_.y << " " << sz_.z << std::endl;
    std::cout << "=== END BLOCK ===" << std::endl;
}


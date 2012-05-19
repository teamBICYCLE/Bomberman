//
// Explosion.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri May 11 11:45:40 2012 lois burg
// Last update Thu May 17 17:39:22 2012 lois burg
//

#include "Explosion.hh"

using namespace	Bomberman;

Explosion::Explosion(const Vector3d& pos, const Vector3d& sz, uint damage)
  : AObject(pos, Vector3d(), sz, "Explosion"), damage_(damage), bBox_(pos_, sz_, this), timeOnScreen_(1.0f), timeOfCreation_(-1)
{
  model_ = gdl::Model::load("Ressources/Assets/bomb.fbx");
}

Explosion::Explosion(const Explosion& other)
  : AObject(other.getPos(), other.getRot(), other.getSize(), other.getType()), damage_(other.getDamage()), bBox_(pos_, sz_, this), timeOnScreen_(1.0f), timeOfCreation_(-1)
{
}

Explosion::Explosion()
    : AObject(Vector3d(), Vector3d(), Vector3d(), "Explosion"), damage_(0),
    bBox_(Vector3d(), Vector3d(), this), timeOnScreen_(1.0f), timeOfCreation_(-1)
{
}

Explosion::~Explosion()
{
}

void		Explosion::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)keys;
  (void)objs;
  if (timeOfCreation_ == -1)
    timeOfCreation_ = clock.getTotalGameTime();
  if (clock.getTotalGameTime() - timeOfCreation_ >= timeOnScreen_)
    destroy();
}

void		Explosion::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  glBegin(GL_QUADS);
  glColor3ub(198, 12, 0);
  glVertex3f(1.0F, 1.0F, 1.0F);
  glVertex3f(1.0F, 1.0F, 0);
  glVertex3f(0, 1.0F, 0);
  glVertex3f(0, 1.0F, 1.0F);
  glVertex3f(1.0F, 0, 1.0F);
  glVertex3f(1.0F, 0, 0);
  glVertex3f(1.0F, 1.0F, 0);
  glVertex3f(1.0F, 1.0F, 1.0F);
  glVertex3f(0, 0, 1.0F);
  glVertex3f(0, 0, 0);
  glVertex3f(1.0F, 0, 0);
  glVertex3f(1.0F, 0, 1.0F);
  glVertex3f(0, 1.0F, 1.0F);
  glVertex3f(0, 1.0F, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 1.0F);
  glVertex3f(0, 0, 0);
  glVertex3f(1.0F, 0, 0);
  glVertex3f(1.0F, 1.0F, 0);
  glVertex3f(0, 1.0F, 0);
  glVertex3f(0, 0, 1.0F);
  glVertex3f(1.0F, 0, 1.0F);
  glVertex3f(1.0F, 1.0F, 1.0F);
  glVertex3f(0, 1.0F, 1.0F);
  glEnd();
}

uint	Explosion::getDamage(void) const
{
  return (damage_);
}

void	Explosion::interact(Character *ch, std::list<AObject*>& objs)
{
  (void)objs;
  ch->takeDamage(damage_);
}

/* Serialization */

BoundingBox&	Explosion::getBBox(void)
{
  return (bBox_);
}

void Explosion::serialize(QDataStream &out) const
{
    pos_.serialize(out);
    rot_.serialize(out);
    sz_.serialize(out);
    out << removeLater_;
    out << damage_;
    out << timeOnScreen_;
    out << timeOfCreation_;
}

void Explosion::unserialize(QDataStream &in)
{
    pos_.unserialize(in);
    rot_.unserialize(in);
    sz_.unserialize(in);
    in >> removeLater_;
    in >> damage_;
    in >> timeOnScreen_;
    in >> timeOfCreation_;
}

void Explosion::sInit(void)
{
    qRegisterMetaTypeStreamOperators<Explosion>("Explosion");
    qMetaTypeId<Explosion>();
}

QDataStream &operator<<(QDataStream &out, const Explosion &v)
{
    v.serialize(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Explosion &v)
{
    v.unserialize(in);
    return in;
}

/* TMP */

void Explosion::aff(void) const
{
    std::cout << "=== START Explosion ===" << std::endl;
    std::cout << "Pos : " << pos_.x << " " << pos_.y << " " << pos_.z << std::endl;
    std::cout << "Rot : " << rot_.x << " " << rot_.y << " " << rot_.z << std::endl;
    std::cout << "Size : " << sz_.x << " " << sz_.y << " " << sz_.z << std::endl;
    std::cout << "Damage : " << damage_ << std::endl;
    std::cout << "timeonscreen : " << timeOnScreen_ << std::endl;
    std::cout << "timeofcreation : " << timeOfCreation_ << std::endl;
    std::cout << "=== END Explosion ===" << std::endl;
}

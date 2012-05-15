//
// Brick.cpp for Brick in /home/sylvia_r//Desktop/projet/tek2/Bomberman
//
// Made by romain sylvian
// Login   <sylvia_r@epitech.net>
//
// Started on  Thu May  3 15:17:56 2012 romain sylvian
// Last update Sun May 13 14:34:21 2012 lois burg
//

#include "Brick.hh"

using namespace	Bomberman;

#include <GL/gl.h>

Brick::Brick(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz, "Brick")
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
    : AObject(other.pos_, other.rot_, other.sz_, "Brick")
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
    : AObject(Vector3d(), Vector3d(), Vector3d(), "Brick")
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
}

#define ZIZIDEPOULE 1.0f

void		Brick::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
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


//  glBegin(GL_QUADS);
//  glColor3ub(255, 0, 0);
//  glVertex3d(0.0d, 0.0d, 0.0d);
//  glVertex3d(0.0d, sz_.y, 0.0d);
//  glVertex3d(sz_.x, sz_.y, 0.0d);
//  glVertex3d(sz_.x, 0.0d, 0.0d);
//  glEnd();
}

const std::string&	Brick::type(void) const
{
  return (type_);
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

Brick &Brick::operator=(const Brick &v)
{
    pos_ = v.pos_;
    rot_ = v.rot_;
    sz_ = v.sz_;
    model_ = v.model_;
    removeLater_ = v.removeLater_;
    return *this;
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


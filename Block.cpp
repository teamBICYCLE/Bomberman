//
// Block.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Thu May 17 11:49:59 2012 lois burg
//

#include "Block.hh"

#include <GL/gl.h>
#include <GDL/Image.hpp>

using namespace	Bomberman;

Block::Block(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz, "Block")
{
}

Block::Block(const Block &other)
    : AObject(other.pos_, other.rot_, other.sz_, "Block")
{
}

Block::Block()
    : AObject(Vector3d(), Vector3d(), Vector3d(), "Block")
{
}

Block::~Block()
{
}

void		Block::update(gdl::GameClock& clock, gdl::Input& keys, std::list<AObject*>& objs)
{
  (void)clock;
  (void)keys;
  (void)objs;
}

#define ZIZIDEPOULE 1.0f

void		Block::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x * sz_.x, pos_.y * sz_.y, pos_.z * sz_.z);
  glBegin(GL_QUADS);
  ////////////////////////////////////////////////////////////////////////////////
  /// Configuration de la couleur des vertices
  ////////////////////////////////////////////////////////////////////////////////
  glColor3f(0.72f, 0.52f, 0.32f);
  ////////////////////////////////////////////////////////////////////////////////
  /// Dessin des vertices
  ////////////////////////////////////////////////////////////////////////////////
  /// Vertex superieur gauche
glNormal3d(0, 1, 0);
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, 0);
  /// Vertex inferieur droit
  glVertex3f(0, ZIZIDEPOULE, 0);
  /// Vertex superieur droit
  glVertex3f(0, ZIZIDEPOULE, ZIZIDEPOULE);
  glColor3f(0.85f, 0.98f, 0.65f);
  glNormal3d(1, 0, 0);
  /// Vertex superieur gauche
  glVertex3f(ZIZIDEPOULE, 0, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(ZIZIDEPOULE, 0, 0);
  /// Vertex inferieur droit
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, 0);
  /// Vertex superieur droit
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  glColor3f(0.31f, 0.64f, 0.84f);
  glNormal3d(0, -1, 0);
  /// Vertex superieur gauche
  glVertex3f(0, 0, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(0, 0, 0);
  /// Vertex inferieur droit
  glVertex3f(ZIZIDEPOULE, 0, 0);
  /// Vertex superieur droit
  glVertex3f(ZIZIDEPOULE, 0, ZIZIDEPOULE);
  glColor3f(0.18f, 0.78f, 0.68f);
  glNormal3d(-1, 0, 0);
  /// Vertex superieur gauche
  glVertex3f(0, ZIZIDEPOULE, ZIZIDEPOULE);
  glVertex3f(0, ZIZIDEPOULE, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, ZIZIDEPOULE);
  glColor3f(0.13f, 0.65f, 0.78f);
  glNormal3d(0, 0, -1);
  glVertex3f(0, 0, 0);
  glVertex3f(ZIZIDEPOULE, 0, 0);
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, 0);
  glVertex3f(0, ZIZIDEPOULE, 0);
    glColor3f(0.07f, 0.65f, 0.46f);
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
//  glColor3ub(255, 255, 255);
//  glVertex3d(0.0d, 0.0d, 0.0d);
//  glVertex3d(0.0d, sz_.y, 0.0d);
//  glVertex3d(sz_.x, sz_.y, 0.0d);
//  glVertex3d(sz_.x, 0.0d, 0.0d);
//  glEnd();
}

void	Block::destroy(void)
{
  //indestructible block
}

/* Serialization */

void Block::serialize(QDataStream &out) const
{
    pos_.serialize(out);
    rot_.serialize(out);
    sz_.serialize(out);
    out << removeLater_;
}

void Block::unserialize(QDataStream &in)
{
    pos_.unserialize(in);
    rot_.unserialize(in);
    sz_.unserialize(in);
    in >> removeLater_;
}

void Block::sInit(void)
{
    qRegisterMetaTypeStreamOperators<Block>("Block");
    qMetaTypeId<Block>();
}

QDataStream &operator<<(QDataStream &out, const Block &v)
{
    v.serialize(out);
    return out;
}

QDataStream &operator>>(QDataStream &in, Block &v)
{
    v.unserialize(in);
    return in;
}

/* TMP */
void Block::aff(void) const
{
    std::cout << "=== START BLOCK ===" << std::endl;
    std::cout << "Pos : " << pos_.x << " " << pos_.y << " " << pos_.z << std::endl;
    std::cout << "Rot : " << rot_.x << " " << rot_.y << " " << rot_.z << std::endl;
    std::cout << "Size : " << sz_.x << " " << sz_.y << " " << sz_.z << std::endl;
    std::cout << "=== END BLOCK ===" << std::endl;
}

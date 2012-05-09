//
// Block.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu May  3 12:08:17 2012 lois burg
// Last update Tue May  8 16:03:57 2012 geoffroy lafontaine
//

#include "Block.hh"

#include <GL/gl.h>
#include <GDL/Image.hpp>

using namespace	Bomberman;

Block::Block(const Vector3d& pos, const Vector3d& rot, const Vector3d& sz)
  : AObject(pos, rot, sz,"Block")
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

#define ZIZIDEPOULE 0.5f

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
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex inferieur droit
  glVertex3f(-ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex superieur droit
  glVertex3f(-ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  glColor3f(0.85f, 0.98f, 0.65f);
  glNormal3d(1, 0, 0);
  /// Vertex superieur gauche
  glVertex3f(ZIZIDEPOULE, -ZIZIDEPOULE, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex inferieur droit
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex superieur droit
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  glColor3f(0.31f, 0.64f, 0.84f);
  glNormal3d(0, -1, 0);
  /// Vertex superieur gauche
  glVertex3f(-ZIZIDEPOULE, -ZIZIDEPOULE, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(-ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex inferieur droit
  glVertex3f(ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex superieur droit
  glVertex3f(ZIZIDEPOULE, -ZIZIDEPOULE, ZIZIDEPOULE);
  glColor3f(0.18f, 0.78f, 0.68f);
  glNormal3d(-1, 0, 0);
  /// Vertex superieur gauche
  glVertex3f(-ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  glVertex3f(-ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
  glVertex3f(-ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  glVertex3f(-ZIZIDEPOULE, -ZIZIDEPOULE, ZIZIDEPOULE);
  glColor3f(0.13f, 0.65f, 0.78f);
  glNormal3d(0, 0, -1);
  glVertex3f(-ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  glVertex3f(ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
  glVertex3f(-ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
    glColor3f(0.07f, 0.65f, 0.46f);
  glNormal3d(0, 0, 1);
  glVertex3f(-ZIZIDEPOULE, -ZIZIDEPOULE, ZIZIDEPOULE);
  glVertex3f(ZIZIDEPOULE, -ZIZIDEPOULE, ZIZIDEPOULE);
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  glVertex3f(-ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
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

const std::string&	Block::type(void) const
{
  return (type_);
}

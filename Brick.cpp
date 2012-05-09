//
// Brick.cpp for Brick in /home/sylvia_r//Desktop/projet/tek2/Bomberman
//
// Made by romain sylvian
// Login   <sylvia_r@epitech.net>
//
// Started on  Thu May  3 15:17:56 2012 romain sylvian
// Last update Fri May  4 18:25:12 2012 lois burg
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

#define ZIZIDEPOULE 0.5f

void		Brick::draw(void)
{
  glPopMatrix();
  glPushMatrix();
  glTranslated(pos_.x, pos_.y, pos_.z);

  ////////////////////////////////////////////////////////////////////////////////
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
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex inferieur droit
  glVertex3f(-ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex superieur droit
  glVertex3f(-ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);

  glColor3f(0.32f, 0.05f, 0.26f);
  glNormal3d(1, 0, 0);
  /// Vertex superieur gauche
  glVertex3f(ZIZIDEPOULE, -ZIZIDEPOULE, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex inferieur droit
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex superieur droit
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  glColor3f(0.33f, 0.21f, 0.12f);
  glNormal3d(0, -1, 0);
  /// Vertex superieur gauche
  glVertex3f(-ZIZIDEPOULE, -ZIZIDEPOULE, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(-ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex inferieur droit
  glVertex3f(ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex superieur droit
  glVertex3f(ZIZIDEPOULE, -ZIZIDEPOULE, ZIZIDEPOULE);
  glColor3f(0.88f, 0.57f, 0.10f);
  glNormal3d(-1, 0, 0);
  /// Vertex superieur gauche
  glVertex3f(-ZIZIDEPOULE, ZIZIDEPOULE, ZIZIDEPOULE);
  /// Vertex inferieur gauche
  glVertex3f(-ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex inferieur droit
  glVertex3f(-ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  /// Vertex superieur droit
  glVertex3f(-ZIZIDEPOULE, -ZIZIDEPOULE, ZIZIDEPOULE);
  glColor3f(0.32f, 0.53f, 0.21f);
  glNormal3d(0, 0, -1);
  glVertex3f(-ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  glVertex3f(ZIZIDEPOULE, -ZIZIDEPOULE, -ZIZIDEPOULE);
  glVertex3f(ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
  glVertex3f(-ZIZIDEPOULE, ZIZIDEPOULE, -ZIZIDEPOULE);
  glColor3f(0.91f, 0.18f, 0.42f);
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

void Brick::loot(std::vector<AObject *> &objs)
{
    if (loot_ != NULL)
    {
        std::cout << "Loot add to Vector !" << std::endl;
        objs.push_back(loot_);
    }
}

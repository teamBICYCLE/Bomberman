/**************************************************************************
** IntroState.cpp: Created on 2 May 2012 by duplom_t
** for class : IntroState
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/


#include "IntroState.hh"
#include <iostream>

#include <GDL/Game.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Carrousel/CarrouselHandler.hh"
#include "Carrousel/LoadContent.hh"
#include "Carrousel/QuickGame.hh"
#include "Carrousel/CustomGame.hh"
#include "Carrousel/AdventureGame.hh"
#include "Carrousel/LeaderBoards.hh"
#include "Sounds.hh"

// Mouvement velo : 1 second -> 4 seconds
// ring. 4 second
// fade to black 5.5s -> 6.5

// 2d image.
// Sound object
// text object

using namespace	Bomberman;

IntroState::IntroState()
  : text_("teambicycle-production", 570, 300, FadingTexture::FadeIn, true, 0.1, 0.04)
{
}

IntroState::~IntroState()
{
}

bool  IntroState::init(void)
{
  this->bicycle_ = gdl::Image::load("./Ressources/Images/Intro/bicycle_noalpha.png");
  x_ = -700.5;
  alpha_ = 0.96f;
  sndPlayed_ = false;
  delay_ = 0;
  return true;
}

void  IntroState::cleanUp()
{
}

void  IntroState::update(StatesManager * sMg, double delta)
{
  (void)delta;
   if (x_ < 560.5)
     x_+= 10;
   else if (!sndPlayed_)
     {
       Sounds::instance().playEffect("ringer");
       sndPlayed_ = true;
     }
   else
     delay_ += 1;
   if (sndPlayed_)
     text_.update(sMg->getGameClock());
   if ((sndPlayed_ && delay_ > 500) || sMg->getInput().isKeyDown(gdl::Keys::Space)
       || sMg->getInput().isKeyDown(gdl::Keys::Escape))
     {
       CarrouselHandler *carrouselHandler = new CarrouselHandler("mainbg", "menu");

       carrouselHandler->createMainMenu();
       sMg->changeState(carrouselHandler);
     }
}

void  IntroState::draw(StatesManager * sMg)
{
  (void)sMg;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND) ;
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;

  glClearColor(alpha_, alpha_, alpha_, 1.0f);
  glClearDepth(1.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 1600, 0, 900);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glPushMatrix();
  glTranslatef(x_, 560.5, 0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_SRC_ALPHA);
  this->bicycle_.bind();
  glBegin(GL_QUADS);
  glTexCoord2i(0, 0);
  glVertex2d(0, 140.0f);
  glTexCoord2i(0, 1);
  glVertex2d(0.0f, -140.0f);
  glTexCoord2i(1, 1);
  glVertex2d(480, -140.0f);
  glTexCoord2i(1, 0);
  glVertex2d(480, 140.0f);
  glEnd();
  glPopMatrix();
  if (sndPlayed_)
    text_.draw();
}

void  IntroState::pause()
{
}

void  IntroState::resume()
{
}

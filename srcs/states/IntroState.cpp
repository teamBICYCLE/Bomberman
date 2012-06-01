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

bool  IntroState::init(void)
{
  this->bicycle_ = gdl::Image::load("./Ressources/Images/Intro/bicycle_noalpha.png");
  x_ = -1700;
  alpha_ = 0.96f;
  sndPlayed_ = false;
  delay_ = 0;
  return true;
}

void  IntroState::cleanUp()
{
  std::cout << "clean up Intro" << std::endl;
}

void  IntroState::update(StatesManager * sMg)
{
   if (x_ < -240)
     x_+= 10;
   else if (!sndPlayed_)
     {
       Sounds::instance().playEffect("ringer");
       sndPlayed_ = true;
     }
   else
     delay_ += 1;
   if (sndPlayed_ && delay_ > 500)
     {
       CarrouselHandler *carrouselHandler = new CarrouselHandler("mainbg");

       carrouselHandler->createMainMenu();
       sMg->changeState(carrouselHandler);
     }
}

void  IntroState::draw(StatesManager * sMg)
{
  (void)sMg;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glClearColor(alpha_, alpha_, alpha_, 1.0f);
  glClearDepth(1.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-800, 800, -450, 450);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glTranslatef(x_, 0, 0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_SRC_ALPHA);
  this->bicycle_.bind();
  glBegin(GL_QUADS);
  //glColor3f(1.0f, 0.50f, 0.75f);
  glTexCoord2i(0, 0);
  glVertex2d(0, 140.0f);
  glTexCoord2i(0, 1);
  glVertex2d(0.0f, -140.0f);
  glTexCoord2i(1, 1);
  glVertex2d(480, -140.0f);
  glTexCoord2i(1, 0);
  glVertex2d(480, 140.0f);
  glEnd();
}

void  IntroState::pause()
{
  std::cout << "pause Intro" << std::endl;
}

void  IntroState::resume()
{
  std::cout << "resume Intro" << std::endl;
}

/**************************************************************************
** CarrouselHandler.cpp: Created on 25 May 2012 by duplom_t
** for class : CarrouselHandler
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "CarrouselHandler.hh"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "PlayState.hh"
#include "AdventureState.hh"
#include "ServerState.hh"
#include "ClientState.hh"

CarrouselHandler::CarrouselHandler()
  : activ_(0), leftPressed_(false), rightPressed_(false), escPressed_(false),
    arrowsFocusLeft_(true), arrowsFocusRight_(true)
{
}

CarrouselHandler::~CarrouselHandler()
{
}

void CarrouselHandler::pushPage(APage * page)
{
  pages_.push_back(page);
}

bool CarrouselHandler::init()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  return true;
}


void CarrouselHandler::cleanUp()
{
}

#include "ServerState.hh"

void CarrouselHandler::update(StatesManager * sMg)
{
  // a degager
  if (sMg->getInput().isKeyDown(gdl::Keys::H))
    sMg->pushState(new Bomberman::Online::ServerState(2), true);
  else if (sMg->getInput().isKeyDown(gdl::Keys::C))
    sMg->pushState(new Bomberman::Online::ClientState("localhost"), true);
  else if (sMg->getInput().isKeyDown(gdl::Keys::P))
    sMg->pushState(new Bomberman::PlayState(), true);
  // ce branchement a ete autorise par le hasard (J'ai pris la face
  // ou y'a le deux)
  if (arrowsFocusLeft_)
    {
      if (sMg->getInput().isKeyDown(gdl::Keys::Left) && !leftPressed_)
        --(*this);
    }
  if (arrowsFocusRight_)
    {
      if (sMg->getInput().isKeyDown(gdl::Keys::Right) && !rightPressed_)
        ++(*this);
    }
  if (sMg->getInput().isKeyDown(gdl::Keys::Escape) && !escPressed_)
    sMg->popState();

  leftPressed_ = sMg->getInput().isKeyDown(gdl::Keys::Left);
  rightPressed_ = sMg->getInput().isKeyDown(gdl::Keys::Right);
  escPressed_ = sMg->getInput().isKeyDown(gdl::Keys::Escape);

  pages_[activ_]->update(sMg->getInput(), sMg->getGameClock(), sMg, this);
}

void CarrouselHandler::draw(StatesManager * sMg)
{
  (void)sMg;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_BLEND) ;
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 1600, 0, 900);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  drawPreviousPreview();
  drawNextPreview();

  pages_[activ_]->draw();
}

void CarrouselHandler::pause()
{
}

void CarrouselHandler::resume()
{
}

void CarrouselHandler::setArrowFocus(bool val)
{
  arrowsFocusLeft_ = val;
  arrowsFocusRight_ = val;
}

void CarrouselHandler::setArrowFocusLeft(bool val)
{
  arrowsFocusLeft_ = val;
}

void CarrouselHandler::setArrowFocusRight(bool val)
{
  arrowsFocusRight_ = val;
}

bool CarrouselHandler::getArrowFocusLeft() const
{
  return arrowsFocusLeft_;
}

bool CarrouselHandler::getArrowFocusRight() const
{
  return arrowsFocusRight_;
}

void CarrouselHandler::drawPreviousPreview()
{
  int prev = activ_ - 1 < 0 ? pages_.size() - 1 : activ_ - 1;

  pages_[prev]->drawLeft();
}

void CarrouselHandler::drawNextPreview()
{
  int next = activ_ + 1 >= static_cast<int>(pages_.size()) ? 0 : activ_ + 1;

  pages_[next]->drawRight();
}


CarrouselHandler &CarrouselHandler::operator ++()
{
  activ_ = activ_ + 1 >= static_cast<int>(pages_.size()) ? 0 : activ_ + 1;

  return *this;
}

CarrouselHandler &CarrouselHandler::operator --()
{
  activ_ = activ_ - 1 < 0 ? pages_.size() - 1 : activ_ - 1;

  return *this;
}



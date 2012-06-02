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
#include "Sounds.hh"
#include "Carrousel/LoadContent.hh"
#include "Carrousel/QuickGame.hh"
#include "Carrousel/CustomGame.hh"
#include "Carrousel/HostGame.hh"
#include "Carrousel/JoinGame.hh"
#include "Carrousel/AdventureGame.hh"
#include "Carrousel/LeaderBoards.hh"
#include "Carrousel/CarrouselHandler.hh"
#include "Carrousel/ItemList.hh"
#include "Carrousel/KeyBindSlide.hh"

CarrouselHandler::CarrouselHandler(const std::string & bg)
  : activ_(0), leftPressed_(false), rightPressed_(false), escPressed_(true),
    arrowsFocusLeft_(true), arrowsFocusRight_(true),
    bg_(Bomberman::ModelHandler::get().getModel(bg)), imgBg_(true), offset_(0)
{
  overlay_ = gdl::Image::load("Ressources/Images/Menu/cloud.png");
}

CarrouselHandler::CarrouselHandler(GLvoid * data)
  : activ_(0), leftPressed_(false), rightPressed_(false), escPressed_(true),
    arrowsFocusLeft_(true), arrowsFocusRight_(true),
    bg_(Bomberman::ModelHandler::get().getModel("mainbg")),
    data_(data), imgBg_(false), offset_(0)
{
  std::cout << "ch created" << std::endl;
  overlay_ = gdl::Image::load("Ressources/Images/Menu/cloud.png");
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
  Sounds::instance().playMusic("menu");
  return true;
}


void CarrouselHandler::cleanUp()
{
}

void CarrouselHandler::update(StatesManager * sMg)
{
  // a degager
  // if (sMg->getInput().isKeyDown(gdl::Keys::H))
  //   sMg->pushState(new Bomberman::Online::ServerState(2), true);
  // else if (sMg->getInput().isKeyDown(gdl::Keys::C))
  //   sMg->pushState(new Bomberman::Online::ClientState("localhost"), true);
  // else
    if (sMg->getInput().isKeyDown(gdl::Keys::P))
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
  glDepthMask(GL_FALSE);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 1600, 0, 900);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (this->imgBg_)
    {
      bg_.draw();
      overlay_.bind();
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
  else
    {
      glDisable(GL_TEXTURE_2D);
      glRasterPos2d(0, 0);
      glDrawPixels(1600, 900, GL_RGB, GL_UNSIGNED_BYTE, data_);
      glColor4f(0, 0, 0, 0.6f);
    }
  glBegin(GL_QUADS);
  glTexCoord2d(0 - offset_, 2); glVertex2d(0, 0);
  glTexCoord2d(2.3333 - offset_, 2); glVertex2d(1600, 0);
  glTexCoord2d(2.3333 - offset_, 0);glVertex2d(1600, 900);
  glTexCoord2d(0 - offset_, 0); glVertex2d(0, 900);
  glEnd();
  glEnable(GL_TEXTURE_2D);
  offset_ += 0.001;
  if (offset_ >= 1.002)
    offset_ = 0;
  drawPreviousPreview();
  drawNextPreview();
  pages_[activ_]->draw();
}

void CarrouselHandler::pause()
{
  Sounds::instance().pauseMusic();
}

void CarrouselHandler::resume()
{
  Sounds::instance().resumeMusic();
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

void CarrouselHandler::createMainMenu()
{
  pushPage(new APage(new QuickGame(), "bg-quickgame", "arrow-quickgame-left", "arrow-quickgame-right"));
  pushPage(new APage(new CustomGame(), "bg-customgame", "arrow-customgame-left", "arrow-customgame-right"));
  pushPage(new APage(new AdventureGame(), "bg-adventure", "arrow-adventure-left", "arrow-adventure-right"));
  pushPage(new APage(new HostGame(), "bg-hostgame", "arrow-host-left", "arrow-host-right"));
  pushPage(new APage(new JoinGame(), "bg-joingame", "arrow-join-left", "arrow-join-right"));
  // pushPage(new APage(new ItemList(), "bg", "right", "left"));
  pushPage(new APage(new LoadContent(), "bg-load", "arrow-load-left", "arrow-load-right"));
  pushPage(new APage(new LeaderBoards(), "bg-leaderboards", "arrow-leaderboard-left", "arrow-leaderboard-right"));
  pushPage(new APage(new KeyBindSlide(), "bg-keybind", "arrow-keybind-left", "arrow-keybind-right"));
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



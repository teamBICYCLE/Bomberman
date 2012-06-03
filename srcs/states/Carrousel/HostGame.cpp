//
// HostGame.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Sun Jun  3 19:43:27 2012 lois burg
//

#include <utility>
#include "ServerState.hh"
#include "HostGame.hh"
#include "CarrouselHandler.hh"
#include "Online.hh"

using namespace	Bomberman;

HostGame::HostGame()
  : returnHit_(false), upHit_(false), downHit_(false), leftHit_(false), rightHit_(false),
    mapWidth_(13), mapHeight_(13), nbPlayers_(4), currentSelection_(0), editing_(false),
    waitingClients_(false), curClient_(0), text_(new gdl::Text()), dotTimer_(1.0f), lastTime_(-1),
    nbDots_(0)
{
  paramMap_.insert(std::make_pair(gdl::Keys::Up, &HostGame::upArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Down, &HostGame::downArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Left, &HostGame::leftArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Right, &HostGame::rightArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Return, &HostGame::returnArrow));

  modifyMap_.insert(std::make_pair(HostGame::MapWidth, &HostGame::modifyMapWidth));
  modifyMap_.insert(std::make_pair(HostGame::MapHeight, &HostGame::modifyMapHeight));
  modifyMap_.insert(std::make_pair(HostGame::NbPlayers, &HostGame::modifyNbPlayers));

  text_->setFont("Ressources/Fonts/Dimbo.ttf");
  text_->setSize(36);
}

HostGame::~HostGame()
{
}

void	HostGame::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler *cH)
{
  float	now = gClock.getTotalGameTime();

  if (lastTime_ == -1)
    lastTime_ = now;
  if (now - lastTime_ >= dotTimer_)
    {
      nbDots_ = ((nbDots_ == 3) ? (0) : (nbDots_ + 1));
      lastTime_ = now;
    }
  if (!waitingClients_)
    {
      for (std::map<gdl::Keys::Key, t_paramFunc>::iterator it = paramMap_.begin(); it != paramMap_.end(); ++it)
	if (input.isKeyDown(it->first))
	  (this->*(it->second))(sMg);
      upHit_ = input.isKeyDown(gdl::Keys::Up);
      downHit_ = input.isKeyDown(gdl::Keys::Down);
      leftHit_ = input.isKeyDown(gdl::Keys::Left);
      rightHit_ = input.isKeyDown(gdl::Keys::Right);
      returnHit_ = input.isKeyDown(gdl::Keys::Return);
      cH->setArrowFocus(!editing_);
    }
  else if (serv_)
    {
      if (curClient_ == nbPlayers_ - 1)
	{
	  waitingClients_ = false;
	  curClient_ = 0;
	  sMg->pushState(new Online::ServerState(mapWidth_, mapHeight_, nbPlayers_, serv_, clients_));
	}
      else
	{
	  resetSelect();
	  select_.watch();
	  if (select_.canRead(serv_->getSockDesc()))
	    {
	      try {
		clients_[curClient_] = serv_->accept();
		curClient_++;
	      } catch (SocketException& e) {
		std::cerr << "Network error while accepting client: " << e.what() << std::endl;
	      }
	    }
	}
      cH->setArrowFocus(!waitingClients_);
    }
}

void	HostGame::draw(void)
{
  drawButton();
  if (!waitingClients_)
    drawArrow();
  glPushMatrix();
  drawIntAt(mapWidth_, 925, 290);
  drawIntAt(mapHeight_, 925, 360);
  drawIntAt(nbPlayers_, 925, 430);
  glPopMatrix();
}

void	HostGame::drawButton(void) const
{
  flatTexture	*button;
  flatTexture	*dot = NULL;

  if (!waitingClients_)
    button = new flatTexture(ModelHandler::get().getModel("create-button"));
  else
    {
      button = new flatTexture(ModelHandler::get().getModel("waiting-button"));
      dot = new flatTexture(ModelHandler::get().getModel("dot"));
    }
  glPushMatrix();
  glTranslated(850, 290, 0);
  button->draw();
  if (dot)
    {
      glTranslated(120, 25, 0);
      for (int i = 0; i < nbDots_; ++i)
	{
	  glTranslated(10, 0, 0);
	  dot->draw();
	}
    }
  glPopMatrix();
  delete button;
  delete dot;
}

void	HostGame::drawArrow(void) const
{
  flatTexture	*arrow;
  int		vAlign;
  int		hAlign = 850;

  if (currentSelection_ == HostGame::NbParams)
    {
      vAlign = currentSelection_ * 100;
      hAlign = 815;
      arrow = new flatTexture(ModelHandler::get().getModel("create-button-overlay"));
    }
  else
    {
      vAlign = currentSelection_ * 70;
      if (editing_)
	arrow = new flatTexture(ModelHandler::get().getModel("custom_arrows_overlay"));
      else
	arrow = new flatTexture(ModelHandler::get().getModel("custom_arrows"));
    }
  glPushMatrix();
  glTranslated(hAlign, (570 - vAlign), 0);
  arrow->draw();
  glPopMatrix();
  delete arrow;
}

void	HostGame::drawIntAt(int val, int x, int y)
{
  std::stringstream	ss;

  ss << val;
  text_->setText(ss.str());
  text_->setPosition(x, y);
  text_->draw();
}

void	HostGame::upArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!upHit_ && !editing_)
    currentSelection_ = ((currentSelection_ == 0) ? (HostGame::NbParams) : (currentSelection_ - 1));
}

void	HostGame::downArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!downHit_ && !editing_)
    currentSelection_ = ((currentSelection_ == HostGame::NbParams) ? (0) : (currentSelection_ + 1));
}

void	HostGame::leftArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!leftHit_ && editing_)
    ((this->*(modifyMap_[static_cast<ParamIdx>(currentSelection_)]))(-1));
}

void	HostGame::rightArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!rightHit_ && editing_)
    ((this->*(modifyMap_[static_cast<ParamIdx>(currentSelection_)]))(1));
}

void	HostGame::returnArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!returnHit_)
    {
      if (currentSelection_ == HostGame::NbParams && !waitingClients_)
	{
	  waitingClients_ = true;
	  clients_.resize(nbPlayers_ - 1);
	  createServSock();
	}
      else
	editing_ = !editing_;
    }
}

void	HostGame::modifyMapWidth(int val)
{
  mapWidth_ += val;
  if (mapWidth_ < 13)
    mapWidth_ = 13;
}

void	HostGame::modifyMapHeight(int val)
{
  mapHeight_ += val;
  if (mapHeight_ < 13)
    mapHeight_ = 13;
}

void	HostGame::modifyNbPlayers(int val)
{
  nbPlayers_ += val;
  if (nbPlayers_ < 2)
    nbPlayers_ = 2;
  else if (nbPlayers_ > 4)
    nbPlayers_ = 4;
}

void	HostGame::createServSock(void)
{
  try {
    serv_ = new TCPServerSocket(Online::ServPort, nbPlayers_ - 1);
  } catch (SocketException& e) {
    std::cerr << "Connection error: " << e.what() << std::endl;
    serv_ = NULL;
  }
}

void	HostGame::resetSelect(void)
{
  select_.reset();
  select_.setNonBlock();
  select_.addRead(serv_->getSockDesc());
}

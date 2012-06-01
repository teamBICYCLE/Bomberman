//
// JoinGame.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Fri Jun  1 14:41:00 2012 lois burg
//

#include <utility>
#include "JoinGame.hh"
#include "Map.hh"
#include "ClientState.hh"
#include "Character.hh"
#include "CarrouselHandler.hh"

using namespace	Bomberman;

JoinGame::JoinGame()
  : returnHit_(false), upHit_(false), downHit_(false),
    currentSelection_(0), editing_(false), editText_(640, 566)
{
  paramMap_.insert(std::make_pair(gdl::Keys::Up, &JoinGame::upArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Down, &JoinGame::downArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Return, &JoinGame::returnArrow));
}

JoinGame::~JoinGame()
{
}

void	JoinGame::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler *cH)
{
  (void)gClock;
  if (editing_)
    editText_.update(input);
  for (std::map<gdl::Keys::Key, t_paramFunc>::iterator it = paramMap_.begin(); it != paramMap_.end(); ++it)
    if (input.isKeyDown(it->first))
      (this->*(it->second))(sMg);
  upHit_ = input.isKeyDown(gdl::Keys::Up);
  downHit_ = input.isKeyDown(gdl::Keys::Down);
  returnHit_ = input.isKeyDown(gdl::Keys::Return);
  cH->setArrowFocus(!editing_);
}

void	JoinGame::draw(void)
{
  drawArrow();
  editText_.draw();
}

void	JoinGame::drawArrow(void) const
{
  flatTexture	*arrow = NULL;
  int		vAlign = 0;
  int		hAlign = 625;

  if (currentSelection_ == JoinGame::NbParams)
    {
      vAlign = currentSelection_ * 140;
      hAlign = 815;
      arrow = new flatTexture(ModelHandler::get().getModel("join-button-overlay"));
    }
  else if (!editing_)
    arrow = new flatTexture(ModelHandler::get().getModel("join-overlay"));
  glPushMatrix();
  glTranslated(hAlign, (565 - vAlign), 0);
  if (arrow)
    arrow->draw();
  glPopMatrix();
  delete arrow;
}

void	JoinGame::upArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!upHit_ && !editing_)
    currentSelection_ = ((currentSelection_ == 0) ? (JoinGame::NbParams) : (currentSelection_ - 1));
}

void	JoinGame::downArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!downHit_ && !editing_)
    currentSelection_ = ((currentSelection_ == JoinGame::NbParams) ? (0) : (currentSelection_ + 1));
}

void	JoinGame::returnArrow(StatesManager *sMg)
{
  if (!returnHit_)
    {
      if (currentSelection_ == JoinGame::NbParams)
	sMg->pushState(new Online::ClientState(editText_.getData()));
      else
	editing_ = !editing_;
    }
}

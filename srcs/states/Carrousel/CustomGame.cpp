//
// CustomGame.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Thu May 31 19:17:37 2012 lois burg
//

#include <utility>
#include "CustomGame.hh"
#include "Map.hh"
#include "PlayState.hh"
#include "Character.hh"
#include "CarrouselHandler.hh"

using namespace	Bomberman;

CustomGame::CustomGame()
  : returnHit_(false), upHit_(false), downHit_(false), leftHit_(false), rightHit_(false),
    mapWidth_(13), mapHeight_(13), nbPlayers_(1), nbMonsters_(3), nbGhosts_(1),
    currentSelection_(0), editing_(false), text_(new gdl::Text())
{
  paramMap_.insert(std::make_pair(gdl::Keys::Up, &CustomGame::upArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Down, &CustomGame::downArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Left, &CustomGame::leftArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Right, &CustomGame::rightArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Return, &CustomGame::returnArrow));

  modifyMap_.insert(std::make_pair(CustomGame::MapWidth, &CustomGame::modifyMapWidth));
  modifyMap_.insert(std::make_pair(CustomGame::MapHeight, &CustomGame::modifyMapHeight));
  modifyMap_.insert(std::make_pair(CustomGame::NbPlayers, &CustomGame::modifyNbPlayers));
  modifyMap_.insert(std::make_pair(CustomGame::NbMonsters, &CustomGame::modifyNbMonsters));
  modifyMap_.insert(std::make_pair(CustomGame::NbGhosts, &CustomGame::modifyNbGhosts));

  text_->setFont("Ressources/Fonts/Dimbo.ttf");
  text_->setSize(36);
}

CustomGame::~CustomGame()
{
}

void	CustomGame::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler *cH)
{
  (void)cH;
  (void)gClock;
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

void	CustomGame::draw(void)
{
  drawArrow();
  glPushMatrix();
  drawIntAt(mapWidth_, 925, 290);
  drawIntAt(mapHeight_, 925, 360);
  drawIntAt(nbPlayers_, 925, 430);
  drawIntAt(nbMonsters_, 925, 500);
  drawIntAt(nbGhosts_, 925, 565);
  glPopMatrix();
}

void	CustomGame::drawArrow(void) const
{
  flatTexture	*arrow;
  int		vAlign;
  int		hAlign = 850;

  if (currentSelection_ == CustomGame::NbParams)
    {
      vAlign = currentSelection_ * 85;
      hAlign = 815;
      arrow = new flatTexture(ModelHandler::get().getModel("go-overlay"));
    }
  else
    {
      if (editing_)
	arrow = new flatTexture(ModelHandler::get().getModel("custom_arrows_overlay"));
      else
	arrow = new flatTexture(ModelHandler::get().getModel("custom_arrows"));
      vAlign = currentSelection_ * 70;
    }
  glPushMatrix();
  glTranslated(hAlign, (570 - vAlign), 0);
  arrow->draw();
  glPopMatrix();
  delete arrow;
}

void	CustomGame::drawIntAt(int val, int x, int y)
{
  std::stringstream	ss;

  ss << val;
  text_->setText(ss.str());
  text_->setPosition(x, y);
  text_->draw();
}

void	CustomGame::upArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!upHit_ && !editing_)
    currentSelection_ = ((currentSelection_ == 0) ? (CustomGame::NbParams) : (currentSelection_ - 1));
}

void	CustomGame::downArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!downHit_ && !editing_)
    currentSelection_ = ((currentSelection_ == CustomGame::NbParams) ? (0) : (currentSelection_ + 1));
}

void	CustomGame::leftArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!leftHit_ && editing_)
    ((this->*(modifyMap_[static_cast<ParamIdx>(currentSelection_)]))(-1));
}

void	CustomGame::rightArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!rightHit_ && editing_)
    ((this->*(modifyMap_[static_cast<ParamIdx>(currentSelection_)]))(1));
}

void	CustomGame::returnArrow(StatesManager *sMg)
{
  if (!returnHit_)
    {
      if (currentSelection_ == CustomGame::NbParams)
	{
	  try {
	    Character::CharacterId = 0;
	    Map	map(mapWidth_, mapHeight_, nbPlayers_, nbMonsters_, nbGhosts_);

	    sMg->pushState(new PlayState(&map.getTerrain()), false);
	  } catch (Map::Failure& e) {
	    std::cerr << e.what() << std::endl;
	  }
	}
      else
	editing_ = !editing_;
    }
}

void	CustomGame::modifyMapWidth(int val)
{
  mapWidth_ += val;
  if (mapWidth_ < 13)
    mapWidth_ = 13;
}

void	CustomGame::modifyMapHeight(int val)
{
  mapHeight_ += val;
  if (mapHeight_ < 13)
    mapHeight_ = 13;
}

void	CustomGame::modifyNbPlayers(int val)
{
  nbPlayers_ += val;
  if (nbPlayers_ < 1)
    nbPlayers_ = 1;
  else if (nbPlayers_ > 2)
    nbPlayers_ = 2;
}

void	CustomGame::modifyNbMonsters(int val)
{
  nbMonsters_ += val;
  if (nbMonsters_ < 0)
    nbMonsters_ = 0;
}

void	CustomGame::modifyNbGhosts(int val)
{
  nbGhosts_ += val;
  if (nbGhosts_ < 0)
    nbGhosts_ = 0;
}

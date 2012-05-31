//
// CustomGame.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Thu May 31 15:31:05 2012 lois burg
//

#include <utility>
#include "CustomGame.hh"
#include "Map.hh"
#include "PlayState.hh"
#include "Character.hh"
#include "CarrouselHandler.hh"

using namespace	Bomberman;

CustomGame::CustomGame()
  : returnHit_(false), upHit_(false), downHit_(false), mapWidth_(13),
    mapHeight_(13), nbPlayers_(1), nbMonsters_(3), nbGhosts_(1),
    currentSelection_(0), editing_(false), text_(new gdl::Text())
{
  paramMap_.insert(std::make_pair(gdl::Keys::Up, &CustomGame::upArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Down, &CustomGame::downArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Return, &CustomGame::returnArrow));

  modifyMap_.insert(std::make_pair(CustomGame::MapWidth, &CustomGame::modifyMapWidth));
  modifyMap_.insert(std::make_pair(CustomGame::MapHeight, &CustomGame::modifyMapHeight));
  modifyMap_.insert(std::make_pair(CustomGame::NbPlayers, &CustomGame::modifyNbPlayers));
  modifyMap_.insert(std::make_pair(CustomGame::NbMonsters, &CustomGame::modifyNbMonsters));
  modifyMap_.insert(std::make_pair(CustomGame::NbGhosts, &CustomGame::modifyNbGhosts));

  text_->setFont("Ressources/Fonts/Dimbo.ttf");
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
  returnHit_ = input.isKeyDown(gdl::Keys::Return);
}

void	CustomGame::draw(void)
{
  drawArrow();
  glPushMatrix();
  drawIntAt(mapWidth_, 800, 0);
  drawIntAt(mapHeight_, 800, 100);
  drawIntAt(nbPlayers_, 800, 200);
  drawIntAt(nbMonsters_, 800, 300);
  drawIntAt(nbGhosts_, 800, 400);
  glPopMatrix();
}

void	CustomGame::drawArrow(void) const
{
  flatTexture	arrow(ModelHandler::get().getModel("overlay-load"));
  int		align = currentSelection_ * 187;

  glPushMatrix();
  glTranslated(400, (540 - align), 0);
  arrow.draw();
  glPopMatrix();
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
  if (!upHit_)
    {
      if (editing_)
	((this->*(modifyMap_[static_cast<ParamIdx>(currentSelection_)]))(1));
      else
	{
	  currentSelection_ = ((currentSelection_ == 0) ? (CustomGame::NbParams) : (currentSelection_ - 1));
	  std::cout << "UP: " << currentSelection_ << std::endl;
	}
    }
}

void	CustomGame::downArrow(StatesManager *sMg)
{
  (void)sMg;
  if (!downHit_)
    {
      if (editing_)
	((this->*(modifyMap_[static_cast<ParamIdx>(currentSelection_)]))(-1));
      else
	{
	  currentSelection_ = ((currentSelection_ == CustomGame::NbParams) ? (0) : (currentSelection_ + 1));
	  std::cout << "DOWN: " << currentSelection_ << std::endl;
	}
    }
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
	{
	  editing_ = !editing_;
	  std::cout << "EDITING: " << std::boolalpha << editing_ << std::noboolalpha << std::endl;
	}
    }
}

void	CustomGame::modifyMapWidth(int val)
{
  mapWidth_ += val;
  if (mapWidth_ < 0)
    mapWidth_ = 0;
  std::cout << "Map Width: " << mapWidth_ << std::endl;
}

void	CustomGame::modifyMapHeight(int val)
{
  mapHeight_ += val;
  if (mapHeight_ < 0)
    mapHeight_ = 0;
  std::cout << "Map Height: " << mapHeight_ << std::endl;
}

void	CustomGame::modifyNbPlayers(int val)
{
  nbPlayers_ += val;
  if (nbPlayers_ < 1)
    nbPlayers_ = 1;
  else if (nbPlayers_ > 2)
    nbPlayers_ = 2;
  std::cout << "Nb Players: " << nbPlayers_ << std::endl;
}

void	CustomGame::modifyNbMonsters(int val)
{
  nbMonsters_ += val;
  if (nbMonsters_ < 0)
    nbMonsters_ = 0;
  std::cout << "Nb Monsters: " << nbMonsters_ << std::endl;
}

void	CustomGame::modifyNbGhosts(int val)
{
  nbGhosts_ += val;
  if (nbGhosts_ < 0)
    nbGhosts_ = 0;
  std::cout << "Nb Ghosts: " << nbGhosts_ << std::endl;
}

//
// SoundConfig.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 16:03:03 2012 lois burg
// Last update Sat Jun  2 13:02:16 2012 lois burg
//

#include <utility>
#include "Sounds.hh"
#include "ModelHandler.hh"
#include "flatTexture.hh"
#include "SoundConfig.hh"
#include "CarrouselHandler.hh"

using namespace	Bomberman;

SoundConfig::SoundConfig()
  : returnHit_(false), upHit_(false), downHit_(false),
    musicEnabled_(true), effectsEnabled_(true), currentSelection_(0)
{
  paramMap_.insert(std::make_pair(gdl::Keys::Up, &SoundConfig::upArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Down, &SoundConfig::downArrow));
  paramMap_.insert(std::make_pair(gdl::Keys::Return, &SoundConfig::returnArrow));

  modifyMap_.insert(std::make_pair(SoundConfig::Music, &SoundConfig::toggleMusic));
  modifyMap_.insert(std::make_pair(SoundConfig::Effects, &SoundConfig::toggleEffects));
}

SoundConfig::~SoundConfig()
{
}

void	SoundConfig::update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler *cH)
{
  (void)gClock;
  (void)sMg;
  (void)cH;
  for (std::map<gdl::Keys::Key, t_paramFunc>::iterator it = paramMap_.begin(); it != paramMap_.end(); ++it)
    if (input.isKeyDown(it->first))
      (this->*(it->second))();
  upHit_ = input.isKeyDown(gdl::Keys::Up);
  downHit_ = input.isKeyDown(gdl::Keys::Down);
  returnHit_ = input.isKeyDown(gdl::Keys::Return);
}

void	SoundConfig::draw(void)
{
  drawArrow();
  glPushMatrix();
  drawOnOff(895, 535, effectsEnabled_);
  drawOnOff(895, 465, musicEnabled_);
  glPopMatrix();
}

void	SoundConfig::drawArrow(void) const
{
  flatTexture	arrow(ModelHandler::get().getModel("arrow-sound"));;
  int		vAlign = currentSelection_ * 70;
  int		hAlign = 850;

  glPushMatrix();
  glTranslated(hAlign, (535 - vAlign), 0);
  arrow.draw();
  glPopMatrix();
}

void	SoundConfig::drawOnOff(int x, int y, bool b) const
{
  flatTexture	*onOff;

  if (b)
    onOff = new flatTexture(ModelHandler::get().getModel("on"));
  else
    onOff = new flatTexture(ModelHandler::get().getModel("off"));
  glPushMatrix();
  glTranslated(x, y, 0);
  onOff->draw();
  glPopMatrix();
  delete onOff;
}

void	SoundConfig::upArrow(void)
{
  if (!upHit_)
    currentSelection_ = ((currentSelection_ == 0) ? (SoundConfig::NbParams - 1) : (currentSelection_ - 1));
}

void	SoundConfig::downArrow(void)
{
  if (!downHit_)
    currentSelection_ = ((currentSelection_ == SoundConfig::NbParams - 1) ? (0) : (currentSelection_ + 1));
}

void	SoundConfig::returnArrow(void)
{
  if (!returnHit_)
    (this->*(modifyMap_[static_cast<ParamIdx>(currentSelection_)]))();
}

void	SoundConfig::toggleMusic(void)
{
  musicEnabled_ = !musicEnabled_;
  Sounds::instance().setPlayMusic(musicEnabled_);
}

void	SoundConfig::toggleEffects(void)
{
  effectsEnabled_ = !effectsEnabled_;
  Sounds::instance().setPlayEffect(effectsEnabled_);
}

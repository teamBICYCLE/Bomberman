//
// FadingTexture.cpp for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri Jun  1 16:59:59 2012 lois burg
// Last update Fri Jun  1 19:20:28 2012 lois burg
//

#include <GL/gl.h>
#include "ModelHandler.hh"
#include "FadingTexture.hh"

using namespace	Bomberman;

FadingTexture::FadingTexture(const std::string& texture, int x, int y, FadingTexture::FirstAnim a, bool noFadeOut, float fadeTimer, float fadeValue)
  : texture_(ModelHandler::get().getModel(texture)), x_(x), y_(y),
    alpha_(1.0f), fadeTimer_(fadeTimer), fadeValue_(fadeValue),
    lastTime_(-1), fadeOutEnded_(false), noFadeOut_(noFadeOut)
{
  if (a == FadingTexture::FadeIn)
    alpha_ = 0;
}

FadingTexture::~FadingTexture()
{
}

void	FadingTexture::update(gdl::GameClock& clock)
{
  float	now = clock.getTotalGameTime();

  if (lastTime_ == -1)
    lastTime_ = now;
  if (now - lastTime_ >= fadeTimer_)
    {
      fadeOut();
      fadeIn();
      lastTime_ = now;
    }
}

void	FadingTexture::draw(void)
{
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glColor4f(1.0f, 1.0f, 1.0f, alpha_);
  glPushMatrix();
  glTranslated(x_, y_, 0);
  texture_.draw();
  glPopMatrix();
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void	FadingTexture::fadeOut(void)
{
  if (!fadeOutEnded_ && !noFadeOut_)
    alpha_ -= fadeValue_;
  if (alpha_ <= 0)
    fadeOutEnded_ = true;
}

void	FadingTexture::fadeIn(void)
{
  if (fadeOutEnded_)
    alpha_ += fadeValue_;
  if (alpha_ >= 1)
    fadeOutEnded_ = false;
}

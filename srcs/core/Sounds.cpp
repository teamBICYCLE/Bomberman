/**************************************************************************
** Sounds.cpp: Created on 1 Jun 2012 by duplom_t
** for class : Sounds
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "Sounds.hh"

#include <iostream>
#include <utility>
#include "unavalaibleRessource.hh"

Sounds::Sounds()
  : playEffects_(true), playMusic_(true)
{
  FMOD_System_Create(&system_);
  FMOD_System_Init(system_, maxchannel_, FMOD_INIT_NORMAL, NULL);
  preload();
}

Sounds::~Sounds()
{
  std::for_each(effects_.begin(), effects_.end(),
                [](std::pair<std::string, std::pair<FMOD_SOUND*, FMOD_CHANNEL*> >obj) -> void {
                FMOD_Sound_Release(obj.second.first);
});
std::for_each(musics_.begin(), musics_.end(),
              [](std::pair<std::string, std::pair<FMOD_SOUND*, FMOD_CHANNEL*> >obj) -> void {
              FMOD_Sound_Release(obj.second.first);
});
FMOD_System_Close(system_);
FMOD_System_Release(system_);
}

void Sounds::preload()
{
  loadEffect("ringer", "Ressources/Sounds/Intro/bike_bell.ogg");
  loadMusic("menu", "Ressources/Sounds/Menu/music.mp3");
  loadMusic("test", "Ressources/Sounds/Menu/test.mp3");
  loadEffect("button", "Ressources/Sounds/Menu/button.wav");
  loadEffect("pressed", "Ressources/Sounds/Menu/pressed.wav");
  loadEffect("released", "Ressources/Sounds/Menu/released.wav");
  loadEffect("drop", "Ressources/Sounds/Play/fart.wav");
  loadEffect("boom", "Ressources/Sounds/Play/explosion.wav");
  loadEffect("run", "Ressources/Sounds/Play/run.wav", true);
  loadEffect("stop", "Ressources/Sounds/Play/tirescreech.wav");
  loadEffect("fight", "Ressources/Sounds/Play/fight.wav");
  loadEffect("1sec", "Ressources/Sounds/Play/1sec.wav");
  loadEffect("2sec", "Ressources/Sounds/Play/2sec.wav");
  loadEffect("3sec", "Ressources/Sounds/Play/3sec.wav");
  loadEffect("flame", "Ressources/Sounds/Play/flame.mp3");
  loadEffect("fxon", "Ressources/Sounds/Menu/fxon.wav");
  loadEffect("cheers", "Ressources/Sounds/Play/cheers.wav");
  loadEffect("boo", "Ressources/Sounds/Play/boo.wav");
}

void Sounds::loadEffect(const std::string &name, const std::string &path, bool loop)
{
  FMOD_SOUND    *snd;
  FMOD_CHANNEL  *chn = NULL;

  if (FMOD_System_CreateSound(system_, path.c_str(), FMOD_CREATESAMPLE | FMOD_LOOP_NORMAL, NULL, &snd)
      != FMOD_OK)
    throw new unavalaibleRessource(path);
  effects_[name] = std::make_pair(snd, chn);
  if (loop)
    FMOD_Sound_SetLoopCount(snd, -1);
  else
    FMOD_Sound_SetLoopCount(snd, 0);
}

bool Sounds::isEffectPlaying(const std::string &name)
{
  FMOD_BOOL *isPlaying = NULL;

  if (!effects_[name].second)
    return false;
  FMOD_Channel_IsPlaying(effects_[name].second, isPlaying);
  return isPlaying;
}

void Sounds::playEffect(const std::string &name, float volume)
{
  FMOD_CHANNEL   *chan = NULL;
  int             lp;

  lp = 0;
  std::for_each(effects_.begin(), effects_.end(),
                [&](std::pair<std::string, std::pair<FMOD_SOUND*, FMOD_CHANNEL*> >obj) -> void {
                FMOD_BOOL   isPlaying;
      if (obj.second.second)
  {
      FMOD_Channel_IsPlaying(obj.second.second, &isPlaying);
      if (!isPlaying || !playEffects_)
        {
          FMOD_Channel_Stop(obj.second.second);
          obj.second.second = NULL;
        }
  }
  });
  FMOD_System_Update(system_);
  if (effects_[name].second)
    FMOD_Channel_GetLoopCount(effects_[name].second, &lp);
  if (playEffects_ && lp != -1)
    {
      FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, effects_[name].first, 0, &chan);
      effects_[name].second = chan;
      FMOD_Channel_SetVolume(chan, volume);
    }
}

void Sounds::stopEffect(const std::string &name)
{
  if (effects_[name].second)
    {
      FMOD_Channel_Stop(effects_[name].second);
      effects_[name].second = NULL;
    }
}

bool Sounds::getPlayEffect() const
{
  return playEffects_;
}

void Sounds::setPlayEffect(bool value)
{
  playEffects_ = value;
}

Sounds &Sounds::instance()
{
  static Sounds self;

  return self;
}

void Sounds::loadMusic(const std::string &name, const std::string &path)
{
  FMOD_SOUND    *snd;

  if (FMOD_System_CreateSound(system_, path.c_str(),
                              FMOD_SOFTWARE | FMOD_2D
                              | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL,
                              0, &snd)
      != FMOD_OK)
    throw new unavalaibleRessource(path);
  FMOD_Sound_SetLoopCount(snd, -1);
  musics_[name].first = snd;
}

void Sounds::playMusic(const std::string &name)
{
  FMOD_CHANNEL  *chan;

  if (playMusic_ && !musics_[name].second)
    {
      FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, musics_[name].first, 0,
                            &chan);
      musics_[name].second = chan;
    }
}

void Sounds::pauseMusic(const std::string &name)
{
  if (musics_[name].second)
    {
      FMOD_Channel_SetPaused(musics_[name].second, 1);
    }
}

void Sounds::resumeMusic(const std::string &name)
{
  if (musics_[name].second)
    {
      FMOD_Channel_SetPaused(musics_[name].second, 0);
    }
}

void Sounds::stopMusic(const std::string &name)
{
  if (musics_[name].second)
    {
      FMOD_Channel_Stop(musics_[name].second);
      musics_[name].second = NULL;
    }
}

bool Sounds::getPlayMusic() const
{
  return playMusic_;
}

void Sounds::setPlayMusic(bool value)
{
  std::for_each(musics_.begin(), musics_.end(),
                [value](std::pair<std::string, std::pair<FMOD_SOUND *, FMOD_CHANNEL *> > obj) -> void {
                if (obj.second.second)
                FMOD_Channel_SetVolume(obj.second.second, value ? 1 : 0);
});
  playMusic_ = value;
}

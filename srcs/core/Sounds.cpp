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

Sounds::Sounds()
  : playEffects_(true), playMusic_(true), currentMusic_(NULL)
{
  FMOD_System_Create(&system_);
  FMOD_System_Init(system_, maxchannel_, FMOD_INIT_NORMAL, NULL);
  preload();
  std::cout << "sounds init" << std::endl;
}

Sounds::~Sounds()
{
  std::for_each(effects_.begin(), effects_.end(),
                [](std::pair<std::string, std::pair<FMOD_SOUND*, FMOD_CHANNEL*> >obj) -> void {
                FMOD_Sound_Release(obj.second.first);
});
std::for_each(musics_.begin(), musics_.end(),
              [](std::pair<std::string, FMOD_SOUND *>obj) -> void {
              FMOD_Sound_Release(obj.second);
});
FMOD_System_Close(system_);
FMOD_System_Release(system_);
}

void Sounds::preload()
{
  loadEffect("ringer", "Ressources/Sounds/Intro/bike_bell.ogg");
  loadMusic("menu", "Ressources/Sounds/Menu/music.mp3");
  loadMusic("test", "Ressources/Sounds/Menu/test.mp3");
  loadEffect("drop", "Ressources/Sounds/Play/fart.wav");
  loadEffect("boom", "Ressources/Sounds/Play/explosion.wav");
  loadEffect("boom", "Ressources/Sounds/Play/explosion.wav");
  loadEffect("run", "Ressources/Sounds/Play/run.wav", true);
  loadEffect("stop", "Ressources/Sounds/Play/tirescreech.wav");
  loadEffect("fight", "Ressources/Sounds/Play/fight.wav");
}

void Sounds::loadEffect(const std::string &name, const std::string &path, bool loop)
{
  FMOD_SOUND    *snd;
  FMOD_CHANNEL  *chn = NULL;

  if (FMOD_System_CreateSound(system_, path.c_str(), FMOD_CREATESAMPLE| FMOD_LOOP_NORMAL, NULL, &snd)
      != FMOD_OK)
    throw std::exception();
  effects_[name] = std::make_pair(snd, chn);
  if (loop)
    FMOD_Sound_SetLoopCount(snd, -1);
  else
    FMOD_Sound_SetLoopCount(snd, 0);

}

// TODO : Detect end of sample when not lopping

bool Sounds::isEffectPlaying(const std::string &name)
{
  int l = 0;
  FMOD_Channel_GetLoopCount(effects_[name].second, &l);
  if (effects_[name].second && l == -1)
    return true;
  else
    return false;
}

void Sounds::playEffect(const std::string &name, float volume)
{
  FMOD_CHANNEL   *chan = NULL;

  if (playEffects_ && !isEffectPlaying(name))
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
    throw std::exception();
  FMOD_Sound_SetLoopCount(snd, -1);
  musics_[name] = snd;
}

void Sounds::playMusic(const std::string &name)
{
  if (playMusic_)
    {
      if (currentMusic_ != NULL)
        FMOD_Channel_Stop(currentMusic_);
      FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, musics_[name], 0,
                            &currentMusic_);
    }
}

void Sounds::pauseMusic()
{
  if (currentMusic_)
    {
      FMOD_Channel_SetPaused(currentMusic_, 1);
    }
}

void Sounds::resumeMusic()
{
  if (currentMusic_)
    {
      FMOD_Channel_SetPaused(currentMusic_, 0);
    }
}

bool Sounds::getPlayMusic() const
{
  return playMusic_;
}

void Sounds::setPlayMusic(bool value)
{
  if (value == false && currentMusic_ != NULL)
    {
      FMOD_Channel_Stop(currentMusic_);
      std::cout << "wth?" << std::endl;
    }
  playMusic_ = value;
}

/**************************************************************************
** Sounds.hh: Created on 1 Jun 2012 by duplom_t
** for class : Sounds
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef   SOUNDS_HH
# define  SOUNDS_HH

# include <fmodex/fmod.h>
# include <algorithm>
# include <map>
# include <exception>

class Sounds
{
public:
  ~Sounds();

  void                  preload();

  void                  loadEffect(const std::string & name,
                                   const std::string & path,
                                   bool loop = false);
  bool                  isEffectPlaying(const std::string & name);
  void                  playEffect(const std::string & name, float volume = 1);
  void                  stopEffect(const std::string & name);
  bool                  getPlayEffect() const;
  void                  setPlayMusic(bool value);

  void                  loadMusic(const std::string & name,
                                  const std::string & path);
  void                  playMusic(const std::string & name);
  void                  pauseMusic(const std::string &name);
  void                  resumeMusic(const std::string &name);
  void                  stopMusic(const std::string & name);
  bool                  getPlayMusic() const;
  void                  setPlayEffect(bool value);

  static Sounds         & instance();

private:
  FMOD_SYSTEM                           *system_;

  std::map<std::string,
  std::pair<FMOD_SOUND *, FMOD_CHANNEL *> >   effects_;
  bool                                  playEffects_;

  std::map<std::string,
  std::pair<FMOD_SOUND *, FMOD_CHANNEL *> >   musics_;
  bool                                        playMusic_;

private:
  static constexpr int  maxchannel_ = 1024;
  Sounds();
};

#endif // SOUNDS_HH

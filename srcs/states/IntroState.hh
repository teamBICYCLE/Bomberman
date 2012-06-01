/**************************************************************************
** IntroState.hh: Created on 2 May 2012 by duplom_t
** for class : IntroState
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef INTROSTATE_HH
# define INTROSTATE_HH

# include <GDL/Image.hpp>
# include <SFML/Audio.hpp>
# include "AGameState.hh"
# include "Carrousel/FadingTexture.hh"

namespace	Bomberman
{
  class IntroState : public AGameState
  {
  public:
    IntroState();
    virtual ~IntroState();

  public:
    virtual bool init(void);
    virtual void cleanUp();

    virtual void update(StatesManager *);
    virtual void draw(StatesManager *);
    virtual void pause();
    virtual void resume();

  private:
    int               x_;
    float             alpha_;
    gdl::Image        bicycle_;
    bool              sndPlayed_;
    int               delay_;
    FadingTexture     text_;
  };
}

#endif // INTROSTATE_HH

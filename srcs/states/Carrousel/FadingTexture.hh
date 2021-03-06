//
// FadingTexture.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Fri Jun  1 16:56:15 2012 lois burg
// Last update Fri Jun  1 19:18:30 2012 lois burg
//

#ifndef		__FADINGTEXTURE_HH__
# define	__FADINGTEXTURE_HH__

# include	<GDL/GameClock.hpp>
# include	"flatTexture.hh"

namespace	Bomberman
{
  class	FadingTexture
  {
  public:
    enum FirstAnim
      {
	FadeIn = 0,
	FadeOut
      };

  public:
    FadingTexture(const std::string& texture, int x, int y, FirstAnim a = FadeOut, bool noFadeOut = false, float fadeTimer = 0.1, float fadeValue = 0.1);
    ~FadingTexture();

  public:
    void	update(gdl::GameClock& input);
    void	draw(void);

  private:
    void	fadeOut(void);
    void	fadeIn(void);

  private:
    flatTexture	texture_;
    int		x_;
    int		y_;
    float	alpha_;
    float	fadeTimer_;
    float	fadeValue_;
    float	lastTime_;
    bool	fadeOutEnded_;
    bool	noFadeOut_;
  };
}

#endif /* !__FADINGTEXTURE_HH__*/

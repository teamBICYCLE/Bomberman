//
// SoundConfig.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May 30 15:57:15 2012 lois burg
// Last update Sat Jun  2 12:57:37 2012 lois burg
//

#ifndef		__SOUNDCONFIG_HH__
# define	__SOUNDCONFIG_HH__

# include	<map>
# include	"AContent.hh"

namespace	Bomberman
{
  class	SoundConfig : public AContent
  {
  private:
    typedef void (SoundConfig::*t_paramFunc)(void);
    typedef void (SoundConfig::*t_modifyParam)(void);
    enum ParamIdx
      {
	Effects = 0,
	Music
      };
    static const int	NbParams = 2;

  public:
    SoundConfig();
    virtual ~SoundConfig();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    void		drawArrow(void) const;
    void		drawOnOff(int x, int y, bool b) const;

  private:
    void		upArrow(void);
    void		downArrow(void);
    void		returnArrow(void);

  private:
    void		toggleMusic(void);
    void		toggleEffects(void);

  private:
    std::map<gdl::Keys::Key, t_paramFunc> paramMap_;
    std::map<ParamIdx, t_modifyParam>	  modifyMap_;
    bool	returnHit_;
    bool        upHit_;
    bool        downHit_;
    bool	musicEnabled_;
    bool	effectsEnabled_;
    int		currentSelection_;
  };
}

#endif /* !__SOUNDCONFIG_HH__*/

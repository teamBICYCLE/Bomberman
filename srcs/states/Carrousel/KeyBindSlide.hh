#ifndef     KEYBINDSLIDE_HH
# define    KEYBINDSLIDE_HH

# include   <GL/gl.h>
# include   <GDL/GameClock.hpp>
# include   <GDL/Input.hpp>
# include   <GDL/Text.hpp>
# include   <map>
# include	"AContent.hh"
# include   "CarrouselHandler.hh"
# include   "Keyboard.hh"
# include   "KeysConfig.hh"

# define    MAX_SIZE    12

namespace	Bomberman
{
  class	KeyBindSlide : public AContent
  {
  public:
    KeyBindSlide();
    virtual ~KeyBindSlide();

  public:
    virtual void	update(gdl::Input& input, gdl::GameClock& gClock, StatesManager *sMg, CarrouselHandler * cH);
    virtual void	draw(void);

  private:
    void    drawOverlay(void) const;
    void    down(void);
    void    up(void);
    void    tab(void);
    void    setEditingMode(void);
    void    drawKeys(int id) const;
    void    setNewKey(const std::string &str);

  private:
    gdl::Text   *text_;
    int         current_;
    int         player_;
    bool        up_;
    bool        down_;
    bool        tab_;
    bool        return_;
    bool        letbool_;
    bool        editingMode_;
    std::map<gdl::Keys::Key, void(KeyBindSlide::*)(void)> paramMap_;
    std::map<eKeys, std::string> player1_;
    std::map<eKeys, std::string> player2_;
    KeysConfig *config_;
    std::map<const std::string, gdl::Keys::Key> ref_;
  };
}

#endif // KEYBINDSLIDE_HH

/*
** BEER-WARE LICENSE :
** KeysConfig.hh for KeysConfig class (5/16/2012)
** <sylvia_r@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#ifndef     __KEYSCONFIG_HH__
# define    __KEYSCONFIG_HH__

# define KEYS_FILE          "./Ressources/Config/player"
# define KEYS_FILE_EXT      ".conf"
# define UP_CFG             "[UP]"
# define DOWN_CFG           "[DOWN]"
# define LEFT_CFG           "[LEFT]"
# define RIGHT_CFG          "[RIGHT]"
# define BOMB_CFG           "[PUT_BOMB]"
# define MINE_CFG           "[PUT_MINE]"

# include <map>
# include <QString>
# include <QStringList>
# include <fstream>
# include <sstream>
# include "AObject.hh"

namespace Bomberman
{
  class	Player;

  enum eKeys
    {
      K_UP = 0,
      K_RIGHT,
      K_DOWN,
      K_LEFT,
      K_PUT_BOMB,
      K_PUT_MINE,
      K_SAVE
    };

  typedef std::map<eKeys, gdl::Keys::Key> keysMap;

  class KeysConfig
  {

  public:
    KeysConfig();
    ~KeysConfig();

  public:
    gdl::Keys::Key &get(eKeys, int);
    gdl::Keys::Key &searchKey(eKeys k, int id);

  private:
    void getFileData(int id);

  private:
    bool fileIsValid(int) const;
    bool checkFormat(const std::string &, int) const;
    const std::string clean(const std::string &str) const;
    bool checkArg(const std::string &str) const;

  private:
    keysMap defaultPlayer1_;
    keysMap defaultPlayer2_;
    std::map<const std::string, gdl::Keys::Key> ref_;
    std::map<eKeys, const std::string> config_;
    std::vector< std::list<std::string> > fileData_;

    void aff(void);
  };
}

#endif // KEYSCONFIG_HH

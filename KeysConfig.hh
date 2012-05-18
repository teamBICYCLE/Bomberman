/*
** BEER-WARE LICENSE :
** KeysConfig.hh for KeysConfig class (5/16/2012)
** <sylvia_r@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#ifndef     __KEYSCONFIG_HH__
# define    __KEYSCONFIG_HH__

# define KEYS_FILE    "config/keys.conf"

# include <map>
# include "AObject.hh"
# include "Player.hh"

using namespace Bomberman;

enum eKeys
{
    K_UP = 0,
    K_RIGHT,
    K_DOWN,
    K_LEFT,
    K_PUT_BOMB,
    K_PUT_MINE
};

typedef std::map<eKeys, gdl::Keys::Key> keysMap;

class KeysConfig
{

public:
    KeysConfig();
    ~KeysConfig();

public:
    gdl::Keys::Key &get(eKeys, int);

private:
    keysMap defaultPlayer1_;
    keysMap defaultPlayer2_;
};

#endif // KEYSCONFIG_HH

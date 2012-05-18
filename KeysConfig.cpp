/*
** BEER-WARE LICENSE :
** KeysConfig.cpp for KeysConfig class (5/16/2012)
** <sylvia_r@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#include "KeysConfig.hh"

KeysConfig::KeysConfig()
{
    defaultPlayer1_.insert(std::make_pair(K_LEFT, gdl::Keys::A));
    defaultPlayer1_.insert(std::make_pair(K_RIGHT, gdl::Keys::D));
    defaultPlayer1_.insert(std::make_pair(K_UP, gdl::Keys::W));
    defaultPlayer1_.insert(std::make_pair(K_DOWN, gdl::Keys::S));
    defaultPlayer1_.insert(std::make_pair(K_PUT_BOMB, gdl::Keys::Space));
    defaultPlayer1_.insert(std::make_pair(K_PUT_MINE, gdl::Keys::LShift));

    defaultPlayer2_.insert(std::make_pair(K_LEFT, gdl::Keys::Numpad4));
    defaultPlayer2_.insert(std::make_pair(K_RIGHT, gdl::Keys::Numpad6));
    defaultPlayer2_.insert(std::make_pair(K_UP, gdl::Keys::Numpad8));
    defaultPlayer2_.insert(std::make_pair(K_DOWN, gdl::Keys::Numpad5));
    defaultPlayer2_.insert(std::make_pair(K_PUT_BOMB, gdl::Keys::Numpad0));
    defaultPlayer2_.insert(std::make_pair(K_PUT_MINE, gdl::Keys::Add));
}

KeysConfig::~KeysConfig()
{
}

gdl::Keys::Key &KeysConfig::get(eKeys k, int id)
{
    if (id == 0)
        return defaultPlayer1_[k];
    return defaultPlayer2_[k];
}

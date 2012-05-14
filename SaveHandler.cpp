/*
** BEER-WARE LICENSE :
** saveHandler.cpp for saveHandler class (5/12/2012)
** <sylvia_r@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#include <QFile>
#include <QSettings>
#include "Block.hh"
#include "Brick.hh"
#include "Player.hh"
#include "Bomb.hh"
#include "Monster.hh"
#include "Explosion.hh"
#include "SaveHandler.hpp"

using namespace Bomberman;

SaveHandler::SaveHandler()
{

}

SaveHandler::~SaveHandler()
{

}

void SaveHandler::save(void) const
{
    QFile::remove(SAVE_FILE);
    Block::sInit();
    Brick::sInit();
    Player::sInit();
    Bomb::sInit();
    Monster::sInit();
    Explosion::sInit();
}

void SaveHandler::load(void) const
{
//    QSettings save(SAVE_FILE, QSettings::IniFormat);
//    if (save.)
}

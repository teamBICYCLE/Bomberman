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
#include "SaveHandler.hh"

using namespace Bomberman;

SaveHandler::SaveHandler()
{

}

SaveHandler::~SaveHandler()
{

}

/* verifier le remove_later */
/* faire un set speed pour bomb */

void SaveHandler::save(void) const
{
    QFile::remove(SAVE_FILE);
    Block::sInit();
    Brick::sInit();
    Player::sInit();
    Bomb::sInit();
    Monster::sInit();
    Explosion::sInit();

    //Player *p = new Player(Vector3d(1, 1, 0), Vector3d(0, 0, 0), Vector3d(0.5, 0.5, 0));

    //(void)p;
    Brick a = Brick(Vector3d(1,1,1), Vector3d(1,2,1), Vector3d(1,3,1));
//    QSettings w(SAVE_FILE, QSettings::IniFormat);
//    w.setValue(QString(a.getType().c_str()), qVariantFromValue(a));
//    w.sync();

//    a.aff();
    std::cout << "eeeee" << std::endl;
}

void SaveHandler::load(void) const
{
//    Bomb a;

//    if (!QFile::exists(SAVE_FILE))
//        std::cerr << "Unable to load save file : file doesn't exist" << std::endl; // Faire un throw
//    QSettings s(SAVE_FILE, QSettings::IniFormat);

//    a = s.value("Bomb", qVariantFromValue(Bomb())).value<Bomb>();
//    std::cout << "aaaaaaaaa" << std::endl;
//    a.aff();
}

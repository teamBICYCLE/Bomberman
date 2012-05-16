/*
** BEER-WARE LICENSE :
** saveHandler.cpp for saveHandler class (5/12/2012)
** <sylvia_r@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#include <QFile>
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

void SaveHandler::writeObject(AObject *obj, QSettings &w) const
{
    if (!obj->removeLater_)
    {
        if (obj->getType() == "Block")
            w.setValue(QString(obj->getType().c_str()), qVariantFromValue(*(dynamic_cast<Block *>(obj))));
        else if (obj->getType() == "Brick")
            w.setValue(QString(obj->getType().c_str()), qVariantFromValue(*(dynamic_cast<Brick *>(obj))));
        else if (obj->getType() == "Player")
            w.setValue(QString(obj->getType().c_str()), qVariantFromValue(*(dynamic_cast<Player *>(obj))));
        else if (obj->getType() == "Bomb")
            w.setValue(QString(obj->getType().c_str()), qVariantFromValue(*(dynamic_cast<Bomb *>(obj))));
        else if (obj->getType() == "Monster")
            w.setValue(QString(obj->getType().c_str()), qVariantFromValue(*(dynamic_cast<Monster *>(obj))));
        else if (obj->getType() == "Explosion")
            w.setValue(QString(obj->getType().c_str()), qVariantFromValue(*(dynamic_cast<Explosion *>(obj))));
        else
            std::cout << "This object is not serializable !" << std::endl;
    }
}

void SaveHandler::save(std::list<AObject*> &objs) const
{
    std::list<AObject*>::const_iterator it;

    QFile::remove(SAVE_FILE);
    Block::sInit();
    Brick::sInit();
    Player::sInit();
    Bomb::sInit();
    Monster::sInit();
    Explosion::sInit();

    QSettings w(SAVE_FILE, QSettings::IniFormat);

    w.beginWriteArray("vector");
    int i = 0;
    for (it = objs.begin(); it != objs.end(); it++)
    {
        w.setArrayIndex(i);
        SaveHandler::writeObject((*it), w);
        i++;
    }
    w.endArray();
    w.sync();
    std::cout << "---> Serialization done ! <---" << std::endl;
}

void SaveHandler::load(std::list<AObject*> &res) const
{
    if (!QFile::exists(SAVE_FILE))
        std::cerr << "Unable to load save file : file doesn't exist" << std::endl; // Faire un throw
    QSettings s(SAVE_FILE, QSettings::IniFormat);
    res.clear();

    int size = s.beginReadArray("vector");
    for (int i = 0; i < size; ++i)
    {
        s.setArrayIndex(i);
        if (s.contains("Block"))
            res.push_back(new Block(s.value("Block", qVariantFromValue(Block())).value<Block>()));
        else if (s.contains("Brick"))
            res.push_back(new Brick(s.value("Brick", qVariantFromValue(Brick())).value<Brick>()));
        else if (s.contains("Player"))
            res.push_back(new Player(s.value("Player", qVariantFromValue(Player())).value<Player>()));
        else if (s.contains("Bomb"))
            res.push_back(new Bomb(s.value("Bomb", qVariantFromValue(Bomb())).value<Bomb>()));
        else if (s.contains("Monster"))
            res.push_back(new Monster(s.value("Monster", qVariantFromValue(Monster())).value<Monster>()));
        else if (s.contains("Explosion"))
            res.push_back(new Explosion(s.value("Explosion", qVariantFromValue(Explosion())).value<Explosion>()));
    }
}

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
#include "Ghost.hh"
#include "Explosion.hh"
#include "FireBlock.hh"
#include "SaveHandler.hh"
#include "Mine.hh"

using namespace Bomberman;

SaveHandler::SaveHandler()
{

}

SaveHandler::~SaveHandler()
{

}

void SaveHandler::writeObject(AObject *obj, QSettings &w) const
{
    obj->toQvariant(w);
}

const std::string   SaveHandler::newFileName(void) const
{
    time_t t;
    std::stringstream strm;

    t = time(NULL);
    strm << t;
    return strm.str();
}

void SaveHandler::initAllObjects(void) const
{
    Block::sInit();
    Brick::sInit();
    Player::sInit();
    Bomb::sInit();
    Mine::sInit();
    Monster::sInit();
    Ghost::sInit();
    Explosion::sInit();
    FireBlock::sInit();
}

void SaveHandler::save(std::list<AObject*> &objs) const
{
    std::list<AObject*>::const_iterator it;
    std::string name_file(SAVE_PATH);

    name_file.append(SaveHandler::newFileName());
    name_file.append(SAVE_EXT);

    if (!QFile::exists(name_file.c_str()))
    {
        SaveHandler::initAllObjects();

        QSettings w(name_file.c_str(), QSettings::IniFormat);
        Character::CharacterId = 0;

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
        std::cout << "---> Save done ! <---" << std::endl;
    }
}

const std::list< std::pair<std::string, std::string> > SaveHandler::getSavedFiles(void) const
{
    unsigned char isFile = 0x8;
    DIR *pdir;
    struct dirent *entry;
    std::list<std::pair<std::string, std::string>> save_list;
    std::list<int> intlist;
    char buff[20];
    time_t time;
    std::stringstream strm;
    std::string realPath;

    pdir = opendir(SAVE_PATH);
    while((entry = readdir(pdir)))
    {
        std::string name(entry->d_name);
        if (entry->d_type == isFile &&
                name.substr(name.find_last_of('.'), name.length()) == SAVE_EXT)
            intlist.push_back(atoi(name.substr(0, name.find_last_of('.')).c_str()));
    }

    intlist.sort();
    intlist.reverse();

    for (std::list<int>::iterator it = intlist.begin(); it != intlist.end(); it++)
    {
        realPath = SAVE_PATH;
        strm.str("");
        time = (*it);
        strftime(buff, 20, "%d/%m %H:%M", localtime(&time));
        strm << (*it);
        save_list.push_back(std::make_pair(buff, realPath.append(strm.str()).append(SAVE_EXT)));
    }
    return save_list;
}

std::list<AObject*> *SaveHandler::load(const std::string &file) const
{
    if (!QFile::exists(file.c_str()))
        std::cerr << "Unable to load save file : file doesn't exist" << std::endl; // Faire un throw

    QSettings s(file.c_str(), QSettings::IniFormat);
    SaveHandler::initAllObjects();
    int lastId = Character::CharacterId;
    std::list<AObject*> *res = new std::list<AObject *>;

    Character::CharacterId = 0;

    int size = s.beginReadArray("vector");

    for (int i = 0; i < size; ++i)
    {
        s.setArrayIndex(i);
        if (s.contains("Block"))
            res->push_back(new Block(s.value("Block", qVariantFromValue(Block())).value<Block>()));
        else if (s.contains("Brick"))
            res->push_back(new Brick(s.value("Brick", qVariantFromValue(Brick())).value<Brick>()));
        else if (s.contains("Player"))
            res->push_back(new Player(s.value("Player", qVariantFromValue(Player())).value<Player>()));
        else if (s.contains("Bomb"))
            res->push_back(new Bomb(s.value("Bomb", qVariantFromValue(Bomb())).value<Bomb>()));
        else if (s.contains("Mine"))
            res->push_back(new Mine(s.value("Mine", qVariantFromValue(Mine())).value<Mine>()));
        else if (s.contains("Monster"))
            res->push_back(new Monster(s.value("Monster", qVariantFromValue(Monster())).value<Monster>()));
        else if (s.contains("Ghost"))
            res->push_back(new Ghost(s.value("Ghost", qVariantFromValue(Ghost())).value<Ghost>()));
        else if (s.contains("Explosion"))
            res->push_back(new Explosion(s.value("Explosion", qVariantFromValue(Explosion())).value<Explosion>()));
        else if (s.contains("FireBlock"))
            res->push_back(new FireBlock(s.value("FireBlock", qVariantFromValue(FireBlock())).value<FireBlock>()));
    }
    s.endArray();
    Character::CharacterId = lastId;
    return res;
}

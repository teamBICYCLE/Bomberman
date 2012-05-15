/*
** BEER-WARE LICENSE :
** saveHandler.hpp for saveHandler class (5/12/2012)
** <sylvia_r@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#ifndef     SAVEHANDLER_HPP
# define    SAVEHANDLER_HPP

# define    SAVE_FILE   "saves/save.bbm"
# include   <list>
# include   <QSettings>
# include   "AObject.hh"

using namespace Bomberman;

class SaveHandler
{

public:
    SaveHandler();
    ~SaveHandler();


public:
    void save(std::list<AObject *> &) const;
    void load(void) const;

private:
    void writeObject(AObject *obj, QSettings &w) const;

};

#endif // SAVEHANDLER_HPP

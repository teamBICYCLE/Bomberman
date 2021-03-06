/*
** BEER-WARE LICENSE :
** saveHandler.hpp for saveHandler class (5/12/2012)
** <sylvia_r@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#ifndef     SAVEHANDLER_HPP
# define    SAVEHANDLER_HPP

# include   <list>
# include   <QSettings>
# include   <string>
# include   <sstream>
# include   <list>
# include   <dirent.h>
# include   <sys/types.h>
# include   <time.h>
# include   <ctime>
# include   <QImage>
# include   <QColor>
# include   "AObject.hh"

# define    SAVE_PATH   "Ressources/Saves/"
# define    SAVE_EXT    ".bbm"
# define    SCREEN_PATH "Ressources/Screenshots"
# define    SCREEN_EXT  ".png"

using namespace Bomberman;

class SaveHandler
{

public:
    SaveHandler();
    ~SaveHandler();

public:
    void save(std::list<AObject *> &, GLvoid *) const;
    std::list<AObject *> *load(const std::string &file);
    const std::list< std::pair<std::string, std::string> > getSavedFiles(void) const;
    const std::string getScreenshot(const std::string &file) const;

private:
    const std::string newFileName(void) const;
    void writeObject(AObject *obj, QSettings &w) const;
    void initAllObjects(void) const;
    void createScreen(const std::string &name, GLvoid *) const;

private:
    void loadBlock(std::list<AObject*> *res, QSettings &);
    void loadBrick(std::list<AObject*> *res, QSettings &);
    void loadPlayer(std::list<AObject*> *res, QSettings &);
    void loadBomb(std::list<AObject*> *res, QSettings &);
    void loadMine(std::list<AObject*> *res, QSettings &);
    void loadMonster(std::list<AObject*> *res, QSettings &);
    void loadGhost(std::list<AObject*> *res, QSettings &);
    void loadExplosion(std::list<AObject*> *res, QSettings &);
    void loadFireBlock(std::list<AObject*> *res, QSettings &);
};

#endif // SAVEHANDLER_HPP

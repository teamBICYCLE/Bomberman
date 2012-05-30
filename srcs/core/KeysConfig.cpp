/*
** BEER-WARE LICENSE :
** KeysConfig.cpp for KeysConfig class (5/16/2012)
** <sylvia_r@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#include "Player.hh"
#include "KeysConfig.hh"

using namespace Bomberman;

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

    /* letter */
    ref_.insert(std::make_pair("A", gdl::Keys::A));
    ref_.insert(std::make_pair("B", gdl::Keys::B));
    ref_.insert(std::make_pair("C", gdl::Keys::C));
    ref_.insert(std::make_pair("D", gdl::Keys::D));
    ref_.insert(std::make_pair("E", gdl::Keys::E));
    ref_.insert(std::make_pair("F", gdl::Keys::F));
    ref_.insert(std::make_pair("G", gdl::Keys::G));
    ref_.insert(std::make_pair("H", gdl::Keys::H));
    ref_.insert(std::make_pair("I", gdl::Keys::I));
    ref_.insert(std::make_pair("J", gdl::Keys::J));
    ref_.insert(std::make_pair("K", gdl::Keys::K));
    ref_.insert(std::make_pair("L", gdl::Keys::L));
    ref_.insert(std::make_pair("M", gdl::Keys::M));
    ref_.insert(std::make_pair("N", gdl::Keys::N));
    ref_.insert(std::make_pair("O", gdl::Keys::O));
    ref_.insert(std::make_pair("P", gdl::Keys::P));
    ref_.insert(std::make_pair("Q", gdl::Keys::Q));
    ref_.insert(std::make_pair("R", gdl::Keys::R));
    ref_.insert(std::make_pair("S", gdl::Keys::S));
    ref_.insert(std::make_pair("T", gdl::Keys::T));
    ref_.insert(std::make_pair("U", gdl::Keys::U));
    ref_.insert(std::make_pair("V", gdl::Keys::V));
    ref_.insert(std::make_pair("W", gdl::Keys::W));
    ref_.insert(std::make_pair("X", gdl::Keys::X));
    ref_.insert(std::make_pair("Y", gdl::Keys::Y));
    ref_.insert(std::make_pair("Z", gdl::Keys::Z));
    /* numpad */
    ref_.insert(std::make_pair("0", gdl::Keys::Numpad0));
    ref_.insert(std::make_pair("1", gdl::Keys::Numpad1));
    ref_.insert(std::make_pair("2", gdl::Keys::Numpad2));
    ref_.insert(std::make_pair("3", gdl::Keys::Numpad3));
    ref_.insert(std::make_pair("4", gdl::Keys::Numpad4));
    ref_.insert(std::make_pair("5", gdl::Keys::Numpad5));
    ref_.insert(std::make_pair("6", gdl::Keys::Numpad6));
    ref_.insert(std::make_pair("7", gdl::Keys::Numpad7));
    ref_.insert(std::make_pair("8", gdl::Keys::Numpad8));
    ref_.insert(std::make_pair("9", gdl::Keys::Numpad9));
    /* special */
    ref_.insert(std::make_pair("ARROW_UP", gdl::Keys::Up));
    ref_.insert(std::make_pair("ARROW_DOWN", gdl::Keys::Down));
    ref_.insert(std::make_pair("ARROW_LEFT", gdl::Keys::Left));
    ref_.insert(std::make_pair("ARROW_RIGHT", gdl::Keys::Right));
    ref_.insert(std::make_pair("SPACE", gdl::Keys::Space));
    ref_.insert(std::make_pair("LEFT_SHIFT", gdl::Keys::LShift));
    ref_.insert(std::make_pair("RIGHT_SHIFT", gdl::Keys::RShift));
    ref_.insert(std::make_pair("ENTER", gdl::Keys::Return));
    ref_.insert(std::make_pair("RETURN", gdl::Keys::Return));
    ref_.insert(std::make_pair("LEFT_CTRL", gdl::Keys::LControl));
    ref_.insert(std::make_pair("RIGHT_CTRL", gdl::Keys::RControl));
    ref_.insert(std::make_pair("+", gdl::Keys::Add));
    ref_.insert(std::make_pair("-", gdl::Keys::Subtract));
    ref_.insert(std::make_pair("LEFT_ALT", gdl::Keys::LAlt));
    ref_.insert(std::make_pair("RIGHT_ALT", gdl::Keys::RAlt));

    config_.insert(std::make_pair(K_UP, UP_CFG));
    config_.insert(std::make_pair(K_DOWN, DOWN_CFG));
    config_.insert(std::make_pair(K_LEFT, LEFT_CFG));
    config_.insert(std::make_pair(K_RIGHT, RIGHT_CFG));
    config_.insert(std::make_pair(K_PUT_BOMB, BOMB_CFG));
    config_.insert(std::make_pair(K_PUT_MINE, MINE_CFG));

    KeysConfig::getFileData(0);
    KeysConfig::getFileData(1);
}

KeysConfig::~KeysConfig()
{
}

void KeysConfig::getFileData(int id)
{
    std::string line;
    std::ifstream infile;
    std::list<std::string> res;
    std::string file(KEYS_FILE);
    std::stringstream st;
    st << (id + 1);

    file.append(st.str()).append(KEYS_FILE_EXT);
    infile.open(file);
    if (!infile.fail())
    {
        while (!infile.eof())
        {
            getline(infile, line);
            res.push_back(line);
        }
    }
    infile.close();
    fileData_.push_back(res);
}

bool KeysConfig::fileIsValid(int id) const
{
  if (id == 0 && fileData_[id].size() > 0)
    return true;

  if (id == 1 && fileData_[id].size() > 0)
    return true;

  return false;
}

bool KeysConfig::checkFormat(const std::string &str, int n) const
{
    if (str[n] == ' ' || str[n] == '\t' || str[n] == '=')
        return true;
    return false;
}

const std::string KeysConfig::clean(const std::string &str) const
{
  std::string ret("");

    for (uint i = 0;  i != str.length(); i++)
        if (str[i] != ' ' && str[i] != '\t')
	  ret.append(str.substr(i, 1));
    return ret;
}

bool KeysConfig::checkArg(const std::string &str) const
{
    std::map<const std::string, gdl::Keys::Key>::const_iterator end = ref_.end();
    if (ref_.find(KeysConfig::clean(str)) != end)
        return true;
    std::cerr << "Keys Configuration : Undefined reference to : " << str << std::endl;
    return false;
}

gdl::Keys::Key &KeysConfig::searchKey(eKeys k, int id)
{
    const std::string search = config_[k];
    std::list<std::string>::iterator it;
    std::list<std::string> now;

    now = fileData_[id];
    for (it = now.begin(); it != now.end(); it++)
    {
        if ((*it).find(search.c_str(), 0, search.length()) != std::string::npos
                && checkFormat((*it), search.length())
                && checkArg(it->substr(it->find('=') + 1)))
            return ref_[KeysConfig::clean(it->substr(it->find('=') + 1))];
    }
    if (id == 0)
        return defaultPlayer1_[k];
    return defaultPlayer2_[k];
}

gdl::Keys::Key &KeysConfig::get(eKeys k, int id)
{
    if (KeysConfig::fileIsValid(id))
        return searchKey(k, id);
    if (id == 0)
        return defaultPlayer1_[k];
    return defaultPlayer2_[k];
}

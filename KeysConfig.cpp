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

    defaultPlayer2_.insert(std::make_pair(K_LEFT, gdl::Keys::Numpad4));
    defaultPlayer2_.insert(std::make_pair(K_RIGHT, gdl::Keys::Numpad6));
    defaultPlayer2_.insert(std::make_pair(K_UP, gdl::Keys::Numpad8));
    defaultPlayer2_.insert(std::make_pair(K_DOWN, gdl::Keys::Numpad5));
    defaultPlayer2_.insert(std::make_pair(K_PUT_BOMB, gdl::Keys::Numpad0));

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

    KeysConfig::getFileData();
}

KeysConfig::~KeysConfig()
{
}

void KeysConfig::getFileData(void)
{
    std::string line;
    std::ifstream infile;
    std::string res("");

    infile.open(KEYS_FILE);
    if (infile.fail())
    {
        // faire un throw
        std::cerr << "File : error !" << std::endl;
    }
    while (!infile.eof())
    {
        getline(infile, line);
        res.append(line);
    }
    infile.close();

    fileData_ = QString(res.c_str()).split("\n", QString::SkipEmptyParts);
}

bool KeysConfig::fileIsValid(int id) const
{
    (void)id;
    return true;
}

gdl::Keys::Key &KeysConfig::get(eKeys k, int id)
{
//    if (KeysConfig::fileIsValid(id + 1))
//    {

//    }
    if (id == 0)
        return defaultPlayer1_[k];
    return defaultPlayer2_[k];
}

//
// LoadScript.cpp for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May 11 13:40:26 2012 thibault carpentier
// Last update Sat May 12 13:48:33 2012 thibault carpentier
//

#include <iostream>
#include "LoadScript.hh"

using namespace Bomberman;
using namespace LuaVirtualMachine;

LoadScript::LoadScript(std::string luaConfFile) :
  fileName_(std::string(NOSCRIPT)), debugFlag_(0)
{
  std::ifstream luaConf(luaConfFile.c_str(), std::ifstream::in);
  parseFile(luaConf);
}

void LoadScript::loadConf(std::vector<std::string> &tokenizer)
{
  std::vector<std::string>::iterator it;

  for (it = tokenizer.begin(); it != tokenizer.end(); ++it)
    {
      if (!(*it).compare(0, std::string(CFG_FILE).length(), CFG_FILE))
	fileName_ = (*it).substr((*it).find(":", 0) + 1, (*it).length());
      else if (!(*it).compare(0, std::string(DEBUG_FLG).length(), DEBUG_FLG))
	std::cout << "LOOOOOOOOOOOOOOOOL" << std::endl;
    }

}

void LoadScript::parseFile(std::ifstream &luaConf)
{
  std::string line;
  std::vector<std::string> tokenizer;

  if (luaConf.fail())
    return;			// throw une exeption ici !
  while (!luaConf.eof())
    {
      getline(luaConf, line);
      clean(tokenizer, " \t\n", line);

      // if (line.compare(line, FILE_LOADER, std::string.lenght(FILE_LOADER)))
      	// std::cout << line << std::endl;
    }
  if (tokenizer.size() != 2)
    return;// lancer exeption
  loadConf(tokenizer);
  luaConf.close();
}

void LoadScript::clean(std::vector<std::string> &tokenizer, const std::string &delim, std::string str) const
{
  unsigned int j = 0;

  // tokenizer.clear();
  for (unsigned int i = 0; i < str.length(); i++)
    {
      if (delim.find(str.substr(i, 1)) != std::string::npos)
        {
          str.erase(i, 1);
          if (!str.substr(j, (i - j)).empty())
            tokenizer.push_back(str.substr(j, (i - j)));
          j = i;
          i--;
        }
    }
  if (!str.substr(j, (str.length() - j)).empty())
    tokenizer.push_back(str.substr(j, (str.length() - j)));
}

std::string &LoadScript::getScriptFile(void)
{
  return (fileName_);
}

int LoadScript::getScriptDebug(void)
{
  return (debugFlag_);
}

LoadScript::~LoadScript(void)
{}

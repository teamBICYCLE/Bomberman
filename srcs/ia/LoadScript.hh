//
// LoadScript.hh for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Fri May 11 13:40:22 2012 thibault carpentier
// Last update Sat May 12 13:46:23 2012 thibault carpentier
//

#ifndef _LOADSCRIPT_H_
# define _LOADSCRIPT_H_

# include <fstream>
# include <vector>

# define DEFAULT_FILE "lua.conf"
# define NOSCRIPT "Error, no script selected in " DEFAULT_FILE
# define CFG_FILE "[FILE]:"
# define DEBUG_FLG "[DEBUG]:"

namespace Bomberman
{
  namespace LuaVirtualMachine
  {
    class LoadScript
    {
    private:
      LoadScript(LoadScript const &);
      LoadScript& operator=(LoadScript const &);

      void parseFile(std::ifstream &luaConf);
      void clean(std::vector<std::string> &tokenizer, const std::string &delim, std::string str) const;
      void loadConf(std::vector<std::string> &tokenizer);

      std::string fileName_;
      int	      debugFlag_;
    public:
      LoadScript(std::string file = DEFAULT_FILE);
      std::string &getScriptFile(void);
      int getScriptDebug(void);
      ~LoadScript(void);
    };
  }
}

#endif /*!_LOADSCRIPT_H_*/

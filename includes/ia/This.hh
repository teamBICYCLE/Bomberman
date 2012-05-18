//
// This.hh for  in /home/jonathan/Projets/iabomber
//
// Made by Jonathan Machado
// Login   <jonathan.machado@epitech.net>
//
// Started on  Sat May  5 16:36:02 2012 Jonathan Machado
// Last update Sat May 12 13:39:07 2012 thibault carpentier
//

#ifndef __THIS_H__
# define __THIS_H__
# include "luainc.hh"
# include "VirtualMachine.hh"

namespace Bomberman
{
  namespace LuaVirtualMachine
  {
    class This
    {
    public:
      This(VirtualMachine &, int);
      ~This(void);

    private:
      This(This const&);
      This &operator=(This const&);

      VirtualMachine &vm_;
      int oldRef_;
    };
  }
}
#endif /* __THIS_H__ */

//
// Brain.hh for  in /home/carpen_t/projets/c++/iabomber
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Mon May 14 13:25:11 2012 thibault carpentier
// Last update Fri May 18 17:56:28 2012 Jonathan Machado
//

/* Documentation tag for Doxygen
 */

/*! \mainpage Classe API Lua-C++ Documentation
 *
 * \section intro_sec Introduction
 *
 * This documentation will help non-developpers or developpers to implements new Artificial Intelligence
 * on the Bomberman.
 *
 * \section install_sec Installation
 *
 * \subsection tools_subsec Tools required:
 *   GDL available here with the folowing command :
 *  "scp -r ssh.epitech.net:/u/all/gamelab/public/libgdl_gl-2012.3.tgz .". <br/>
 *  Untar "tar -xvf libgdl_gl-2012.3.tgz" and copy the library in /usr/lib and the headers files in /usr/includes. <br/>
 *  Type "make" in the console to compile the program. <br/>
 *
 * \subsection running Running the program
 * Once the compilation is done, simply type ./Bomberman in the console to lauch the game !
 *
 *
 * \section copyright Copyright and License
 *
 *  Copyright 2012, all rights reserved, TeamBicycle.
 *
 * <BR><BR>
 *
 */

/**
 * \file Brain.hh
 * \brief Classe API Lua-C++, contain all functions callable with the lua-script.
 * \author TeamBicycle.
 * \version 1.0
 * \date 14 May 2012
 *
 * This Class is the Emulated Object in the lua file, it create every method callable in the lua script.
 *
 */

#ifndef _BRAIN_H_
# define _BRAIN_H_

# include <map>
# include <string>
# include <iostream>
# include <list>
# include "VirtualMachine.hh"
# include "Script.hh"
# include "Character.hh"
# include  "DangerMap.hh"

using namespace Bomberman;
using namespace LuaVirtualMachine;

/*! \namespace Bomberman
 *  \brief main project namespace
 * Bomberman is the main project namespace.
 *
 */
namespace Bomberman
{
/*! \namespace Thinking
 *  \brief IA namespace
 * Thinking is the Artificial Intelligence NameSpace.
 *
 */
  namespace Thinking
  {
    /*! \class Brain
     * \brief Brain class encapsulate calls from lua and organise Scripting calls.
     *
     *  The Brain class is a encapsulation of Api Methods, and herit from Script to organise Scipting calls.
     */
    class Brain : public Script
    {
    typedef int (Bomberman::Thinking::Brain::*fctMeth)(VirtualMachine &);

   public:
      /*!
       *  \brief Constructor.
       *
       *  Constructor of Brain Class, initialise the Api Methods to makes them callabe by the lua.
       *  Pushing direction in globals : UP RIGHT DOWN LEFT NODIR.
       *
       */
      Brain(int, int);
      /*!
       *  \brief Destructor.
       *
       *  Destructor of Brain Class.
       *
       */
      ~Brain(void);

      /*!
       *  \brief Method redirecting calls.
       *
       *  Method called by Lua each time that an C++ function is called,
       *  redirecting calls to the real method called.
       *
       *  \param vm : The Virtual Machine where the script is emulated.
       *  \param fctNb : The id of the called Method on the stack.
       *  \return (int) -1 if the method does not exist and the number
       *  of return value of the Method called on succes
       *
       */
      int scriptCalling(VirtualMachine &vm, int fctNb);
      /*!
       *  \brief Method hanling returns from functions called in lua.
       *
       *  Method called by Lua each time a Lua function is called from the C++, to use Lua
       *  return values.
       *
       *  \param vm : The Virtual Machine where the script is emulated.
       *  \param strFunc : The name of the returning function.
       *  \return (void)
       *
       */
      void getReturn(VirtualMachine &vm, const std::string &strFunc);
      /*!
       *  \brief returning the movement decided by the Script.
       *
       *  Return the final decision of the thinking fonction
       *  \return (eDirection) (direction enum)
       *
       */
      eDirection getDecision(void) const;

      /*!
       *  \brief The test Method.
       *
       *  This is the TESSSST !
       *  A BIG TEST !
       *
       *  \param vm : (Automatically added by lua) The Virtual Machine where the script is emulated.
       *  \return (int) The number of value pushed on the lua-stack.
       *
       */
      int test(VirtualMachine &vm);

    private:
      /*!
       *  \brief Unused Constructor.
       *
       *  Unused Constructor of Brain Class.
       *
       *  \param Unused.
       */
      Brain(Brain const &);
      /*!
       *  \brief Unused Constructor.
       *
       *  Unused Constructor of Brain Class.
       *
       *  \param Unused.
       */
      Brain& operator=(Brain const &);

      eDirection decision_; /*!< Final Decision of the IA, seted to NODIR by default*/

      std::map<int, fctMeth> meth_; /*!< Method and id associeted storage. Please remember to add new method on the constructor with : meth_[registerFct("exemple")] = &Brain::example;*/
      DangerMap danger_;
    };
  }
}

#endif /*!_BRAIN_H_*/

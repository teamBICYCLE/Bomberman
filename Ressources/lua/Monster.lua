#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)
-- debug hooker is the function setHook(HOOKTYPE, count)
-- HOOKTYPE are : MASKCOUT, MASKRET MASKCALL MASKLINE

dofile("Ressources/lua/INCLUDE_usefullFct.lua")
function this.thinking(this, x, y)
-- setHook(MASKCALL, 1)
   -- if (this:getDanger(x, y) > 0 or this:getDanger(x, y + 0.6) > 0 or
   --  this:getDanger(x + 0.6, y) > 0 or this:getDanger(x + 0.6, y + 0.6) > 0)
   -- then
   --    return (getLessDangerousDirection(this, x, y, MONSTER))
   -- else
      return (trackPlayer(this, x, y, MONSTER))
--   end
 --      if (getLessDangerousDirection(this, x, y, MONSTER) == NODIR) then
 --       	 return (getLessDangerousDirection(this, x, y))
 --      else

   --    end
   -- else
   --    return (NODIR)		--chercher le joueur ?
   -- end
end

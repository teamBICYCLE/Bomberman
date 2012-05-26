#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)
-- debug hooker is the function setHook(HOOKTYPE, count)
-- HOOKTYPE are : MASKCOUT, MASKRET MASKCALL MASKLINE

dofile("Ressources/lua/INCLUDE_usefullFct.lua")

function this.thinking(this, x, y)
   if (getZoneDanger(this, x, y) > 0 or getZoneDanger(this, x, y + 0.6) > 0 or
 getZoneDanger(this, x + 0.6, y) > 0 or getZoneDanger(this, x + 0.6, y + 0.6) > 0) then
      if (getLessDangerousDirection(this, x, y, MONSTER) == NODIR) then
       	 return (getLessDangerousDirection(this, x + 1, y))
      else
   	 return (getLessDangerousDirection(this, x, y, MONSTER))
      end
   else
      return (NODIR)		--chercher le joueur ?
   end
end

#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)
-- debug hooker is the function setHook(HOOKTYPE, count)
-- HOOKTYPE are : MASKCOUT, MASKRET MASKCALL MASKLINE

dofile("Ressources/lua/INCLUDE_usefullFct.lua")
function this.thinking(this, x, y)
-- setHook(MASKCALL, 1)
   if (getZoneDanger(this,x, y) != 0)
   then
      return (center(x, y, getLessDangerousDirection(this, x, y, MONSTER)))
   else
      return (center(x, y, trackPlayer(this, x, y, MONSTER)))
   end
   --    return (NODIR)		--chercher le joueur ?
end

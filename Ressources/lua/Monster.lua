#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)

dofile("Ressources/lua/INCLUDE_usefullFct.lua")
function this.thinking(this, x, y)
   print(getZoneDanger(this,x, y) * 100,
	 getZonePheromones(this, x, y) / 10)
   if ((getZoneDanger(this,x, y) * 100) >= getZonePheromones(this, x, y) / 10)
   then
      return (center(x, y, getLessDangerousDirection(this, x, y, MONSTER)))
   else
      return (center(x, y, trackPlayer(this, x, y, MONSTER)))
   end
   --    return (NODIR)		--chercher le joueur ?
end

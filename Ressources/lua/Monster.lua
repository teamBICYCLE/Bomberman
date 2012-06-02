#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)

dofile("Ressources/lua/INCLUDE_usefullFct.lua")
function this.thinking(this, x, y)
   local danger = getZoneDanger(this,floor(x), floor(y))
   local pheromones = getZonePheromones(this, x, y)
   
   if ((danger * 10) > (pheromones / 10) * 0.5)
    then
       print("FEAR mode enabled")
  --     print ("echap", showdir(getLessDangerousDirection(this, x, y, MONSTER)))
       return (center(x, y, escapeDanger(this, x, y , danger)))
    elseif (pheromones > 0)
    then
       print("TRACK mode enabled")
       --   print ("track" , showdir(trackPlayer(this, x, y, MONSTER)))
       return (center(x, y, trackPlayer(this, x, y, MONSTER)))
    else
       print("EXPLORATION mode enabled")
       return (center(x, y, exploreMap(this, x, y)))
    end
    -- return (center(x,y,NODIR))		--chercher le joueur
end

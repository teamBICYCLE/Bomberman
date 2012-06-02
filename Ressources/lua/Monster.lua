#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)

dofile("Ressources/lua/INCLUDE_usefullFct.lua")
function this.thinking(this, x, y)

   -- print(x, y)
   -- -- getZoneDanger(this, floor(x), floor(y))
--    print("coeff danger :", getZoneDanger(this,floor(x), floor(y)) * 10,
    --	  "coeff phero", getZonePheromones(this, x, y)  /10 * 0.5,
    --	  "at", x, y, "floor", math.floor(x), math.floor(y))

   local danger = getZoneDanger(this,floor(x), floor(y))
   local pheromones = getZonePheromones(this, x, y)
    if ((danger * 10) > (pheromones / 10) * 0.5)
    then
       print("FEAR mode enabled")
  --     print ("echap", showdir(getLessDangerousDirection(this, x, y, MONSTER)))
       return (center(x, y, getLessDangerousDirection(this, x, y, MONSTER)))
    elseif (pheromones > 0)
    then
       print("TRACK mode enabled")
       --   print ("track" , showdir(trackPlayer(this, x, y, MONSTER)))
       return (center(x, y, trackPlayer(this, x, y, MONSTER)))
    else
       print("EXPLORATION mode enabled")
       return (exploreMap(this, x, y))
    end
    -- return (center(x,y,NODIR))		--chercher le joueur
end

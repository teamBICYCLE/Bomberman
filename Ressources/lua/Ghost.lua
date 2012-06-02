#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)

dofile("Ressources/lua/INCLUDE_usefullFct.lua")

function this.thinking(this, x, y)
   local danger = getZoneDanger(this,floor(x), floor(y))
   local pheromones = getZonePheromones(this, x, y)

   if ((danger * 10) > (pheromones / 10) * 0.7)
    then
       print("FEAR mode enabled")
       return (center(x, y, getLessDangerousDirection(this, x, y , danger, GHOST)))
    elseif (pheromones > 0)
    then
       print("TRACK mode enabled")
       return (center(x, y, trackPlayer(this, x, y, GHOST)))
    else
       print("EXPLORATION mode enabled")
       return (center(x, y, exploreMap(this, x, y, GHOST)))
    end
end

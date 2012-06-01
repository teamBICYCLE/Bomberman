#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)

dofile("Ressources/lua/INCLUDE_usefullFct.lua")
function this.thinking(this, x, y)

   print(x, y)
   -- getZoneDanger(this, floor(x), floor(y))
    print("coeff danger :", getZoneDanger(this,floor(x), floor(y)) * 10,
    	  "coeff phero", getZonePheromones(this, x, y)  /10 * 0.7,
    	  "at", x, y, "floor", floor(x), floor(y))

  -- if ((getZoneDanger(this,floor(x), floor(y)) * 10) > (getZonePheromones(this, x, y) / 10) * 0.7)
  -- then
  --    print ("echap", showdir(getLessDangerousDirection(this, x, y, MONSTER)))
  --    return (center(x, y, getLessDangerousDirection(this, x, y, MONSTER)))
  -- else
  --    print ("track" , showdir(trackPlayer(this, x, y, MONSTER)))
  --    return (center(x, y, trackPlayer(this, x, y, MONSTER)))
  -- end
    return (center(x,y,NODIR))		--chercher le joueur 

end

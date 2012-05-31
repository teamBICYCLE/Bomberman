#!/usr/bin/lua

function showdir(res)
   if (res == NODIR)
   then
      return("NODIR")
   elseif (res == RIGHT)
   then
      return("RIGHT")
   elseif res == LEFT
   then
      return("LEFT")
   elseif res == UP
   then
      return("UP")
   elseif (res == DOWN)
   then
      return("DOWN")
   else
      return ("BADRETURN")
   end
end

function floor(x)
   x = math.floor(x + 0.001)
   if (x < 0)
   then
      x = 0
   end
   return (x)
end

function getZoneDanger(this, x, y)
   local posX = {x , x + 1 , x - 1 , x     , x     , x + 1 , x - 1 , x + 1 , x - 1}
   local posY = {y , y     , y     , y - 1 , y + 1 , y + 1 , y + 1 , y - 1 , y - 1}
   local res = 0
   local size = 0

   for j = 1, table.getn(posX) do
      local tmp = this:getDanger(posX[j], posY[j])
--      print("danger : ", "x ", posX[j], " y ", posY[j], this:getDanger(posX[j], posY[j]))
      if (tmp ~= (DANGER_MAX + 1))
      then
	 if (tmp > 0 and posX[j] == x and posY[j] == y)
	 then
--	    print("result :", tmp, j)
	    -- print()
	    return (tmp)
	 end
	 res = res + tmp
	 size = size + 1
      end
   end
   -- print()
   -- print(size)
    -- print("result :", res / size)
   -- print()
   -- print()
   -- print()
   return (res / size)
end

function testCross(this, x, y, type)
   local dir =  { RIGHT   , LEFT    , UP      , DOWN   }
   local posX = { x + 1   , x - 1   , x       , x       }
   local posY = { y       , y       , y - 1   , y + 1   }
   local dirX = { x + 0.05   , x - 0.05   , x       , x       }
   local dirY = { y       , y       , y - 0.05   , y + 0.05   }   
   local res_dir = NODIR
   local danger = getZoneDanger(this, x, y)
   
--   print("Danger local de ", danger)
   for  i = 1, table.getn(dir) do
      local tmpDanger = getZoneDanger(this, posX[i], posY[i])
  --    print("================= Testing : ", showdir(dir[i]) ," danger de :", floor(tmpDanger), "et crossable == ", this:isCrossable(floor(posX[i]), floor(posY[i]), type) == 1 and this:isCrossable(dirX[i], dirY[i], type) == 1)
      if (danger > 0 and
	  tmpDanger < danger
	  and this:isCrossable(floor(posX[i]), floor(posY[i]), type) == 1 and this:isCrossable(dirX[i], dirY[i], type) == 1)
      then
	 danger = tmpDanger
	 res_dir = dir[i]
       end
   end
   return res_dir, danger
end

function UpperRight(this, x, y, type)
   if (this:isCrossable(floor(x + 1), floor(y), type) == 1 and this:isCrossable(x + 0.05, y, type) == 1)
   then
      return (RIGHT)
   elseif (this:isCrossable(floor(x), floor(y - 1), type) == 1 and this:isCrossable(x, y - 0.05, type) == 1)
   then
      return (UP)
   end
   return (NODIR)
end

function UpperLeft(this, x, y, type)
   if (this:isCrossable(floor(x - 1), floor(y), type) == 1 and this:isCrossable(x - 0.05, y, type)== 1)
   then
      return (LEFT)
   elseif (this:isCrossable(floor(x), floor(y - 1), type) == 1 and this:isCrossable(x, y - 0.05, type)== 1)
   then
      return (UP)
   end
   return (NODIR)
end

function BottomRight(this, x, y, type)
   if (this:isCrossable(floor(x + 1), floor(y), type) == 1 and this:isCrossable(x + 0.05, y, type)== 1)
   then
      return (RIGHT)
   elseif (this:isCrossable(floor(x), floor(y + 1), type) == 1 and this:isCrossable(x, y + 0.05, type)== 1)
   then
      return (DOWN)
   end
   return (NODIR)
end

function BottomLeft(this, x, y, type)
   if (this:isCrossable(floor(x - 1), floor(y), type) == 1 and this:isCrossable(x - 0.05, y, type)== 1)
   then
      return (LEFT)
   elseif (this:isCrossable(floor(x), floor(y + 1), type) == 1 and this:isCrossable(x, y + 0.05, type)== 1)
   then
      return (DOWN)
   end
   return (NODIR)
end

function testAngles(this, x, y, type, danger, res_dir)
   local dir =  { {"bottom right"   , "upper right"}    , {"botom left"      , "upper left"}   }
   local posX = { x + 1   , x - 1 }
   local posY = { y + 1   , y - 1 }
   local funct = { {BottomRight, UpperRight}, {BottomLeft, UpperLeft}}

   for  i = 1, table.getn(posX) do
      for  j = 1, table.getn(posY) do
	 local tmpDanger = getZoneDanger(this, posX[i], posY[j])
--	 print("================= Testing : ", dir[i][j] ," danger de :", floor(tmpDanger), "et crossable == ", this:isCrossable(floor(posX[i]), floor(posY[j]), type) == 1 and funct[i][j](this, x, y, type) ~= NODIR)
	 if (danger > 0 and
	     tmpDanger < danger
	     and this:isCrossable(floor(posX[i]), floor(posY[j]), type) == 1)
	 then
	    danger = tmpDanger
	    res_dir = funct[i][j](this, x, y, type)
	 end
      end
   end
   return (res_dir)
end

function getLessDangerousDirection(this, x, y, type)
   local danger = 0
   local res_dir = NODIR
--   print (x, y, "floor", floor(x),floor(y))
   res_dir, danger = testCross(this, x, y, type)

   res_dir = testAngles(this, x, y, type, danger, res_dir)
   if (res_dir == NODIR)
   then
      -- aller quelque part
   end
--   print("======", showdir(res_dir), "=======")
   return (res_dir)
end

function trackPlayer(this, x, y, type)
   local dir =  { RIGHT   , LEFT    , UP      , DOWN     }
   local posX = { x + 1   , x - 1   , x       , x        }
   local posY = { y       , y       , y - 1   , y + 1    }
   local dirX = { x + 0.05, x - 0.05 , x      , x        }
   local dirY = { y       , y       , y - 0.05, y + 0.05 }

   local res_dir = NODIR
   local res_ph = this:getPheromones(x, y)
   for  k = 1, table.getn(dir) do
      local tmp = this:getPheromones(posX[k], posY[k])
      if (res_ph < tmp  and tmp > 0 and this:isCrossable(floor(posX[k]), floor(posY[k]), type) == 1
       and this:isCrossable(dirX[k], dirY[k], type) == 1)
      then
	 res_ph = tmp
	 --	 print(tmp, "x", floor(x), "y", floor(y))
	 res_dir = dir[k]
      end
   end
   -- print(showdir(res_dir))
   return (res_dir)

end
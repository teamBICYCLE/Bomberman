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


function getLessDangerousDirection(this, x, y, type)
   local dir = {NODIR, RIGHT   , LEFT    , UP      , DOWN     }
   local posX = {x   , x + 1   , x - 1   , x       , x        }
   local posY = {y   , y       , y       , y - 1   , y + 1    }
   local dirX = {x   , x + 1, x - 1, x       , x        }
   local dirY = {y   , y       , y       , y - 1, y + 1 }

--   print(posX[1], posX[2], posX[3])
   local res_dir = dir[1]
   local danger_res = getZoneDanger(this, posX[1], posY[1])
   print("Danger local de ", danger_res )
   for  i = 2, table.getn(dir) do
      local tmpDanger = getZoneDanger(this, posX[i], posY[i])
    print("================= Testing : ", showdir(dir[i]) ," danger de :", tmpDanger, "et crossable == ", this:isCrossable(dirX[i], dirY[i], type))
      if (danger_res > 0 and
      tmpDanger < danger_res
	  and this:isCrossable(dirX[i], dirY[i], type) == 1)
      then
   	 danger_res = tmpDanger
   	 res_dir = dir[i]
	 --print(showdir(res_dir))
      end
   end
    print("======", showdir(res_dir), "=======")
  -- print()
  -- print()
   return (res_dir)
end
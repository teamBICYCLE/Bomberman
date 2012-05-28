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

function round(num)
   under = math.floor(num)
   upper = math.floor(num) + 1
   underV = -(under - num)
    upperV = upper - num
   if (upperV > underV) then
        return under
   else
        return upper
   end
end


function getZoneDanger(this, x, y)
   posX = {x , x + 1 , x - 1 , x     , x     , x + 1 , x - 1 , x + 1 , x - x}
   posY = {y , y     , y     , y - 1 , y + 1 , y + 1 , y + 1 , y - 1 , y - 1}

   res = 0
   size = 0
   for i = 1, table.getn(posX) do
      tmp = this:getDanger(posX[i], posY[i])
      if (tmp ~= (DANGER_MAX + 1))
      then
	 res = res + tmp
	 size = size + 1
      end
   end
   return (res / size)
end


function getLessDangerousDirection(this, x, y, type)
   dir = {NODIR, RIGHT, LEFT , UP   , DOWN}
   posX = {x   , x + 1, x - 1, x    , x}
   posY = {y   , y    , y    , y - 1, y + 1}
   dirX = {x   , x + 1, x - 1, x    , x}
   dirY = {y   , y    , y    , y - 1, y + 1}


--    for i = 1, table.getn(dir) do
--       print(getZoneDanger(this, posX[i], posY[i]))
--    end
--    print()
--  return (NODIR)
-- end

   res_dir = dir[1]
   danger_res = getZoneDanger(this, posX[1], posY[1])
   for i = 1, table.getn(dir) do
      print(getZoneDanger(this, posX[i], posY[i]))-- this:isCrossable(dirX[i], dirY[i], type), showdir(dir[i]))
      if (getZoneDanger(this, posX[i], posY[i]) < danger_res
       and this:isCrossable(dirX[i], dirY[i], type) == 1)
      then
   	 danger_res = getZoneDanger(this, posX[i], posY[i])
   	 res_dir = dir[i]
	 -- print(showdir(res_dir))
      end
   end
   print(showdir(res_dir))
   -- print(res_dir, NODIR, UP, DOWN, LEFT, RIGHT)
   print()
   return (res_dir)
end
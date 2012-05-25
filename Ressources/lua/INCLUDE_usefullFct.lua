#!/usr/bin/lua

function showdir(res)
   if (res == NODIR)
   then
      return("NODIR")
   end
   if (res == RIGHT)
   then
      return("RIGHT")
   end
   if res == LEFT
   then
      return("LEFT")
   end
   if res == UP
   then
      return("UP")
   end
   if (res == DOWN)
   then
      return("DOWN")
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

function getLessDangerousDirection(this, x, y, type)
   -- x = round(x, 0)
   -- y = round(y, 0)
   dir = {NODIR, RIGHT, LEFT, UP, DOWN}
   posX = {x , x + 1, x - 1, x, x}
   posY = {y, y, y, y - 1, y + 1}
   dirX = {x, x + 1, x - 1, x, x}
   dirY = {y, y, y, y - 1, y + 1}

   res = dir[1]
   danger_res = this:getDanger(posX[1], posY[1], type)
   i = 1
   for i = 1, table.getn(dir)do
--      print (posX[i], posY[i], this:getDanger(posX[i], posY[i]), this:isCrossable(posX[i], posY[i], type), showdir(dir[i]))
      if (this:getDanger(posX[i], posY[i]) <= danger_res
       and this:isCrossable(dirX[i], dirY[i], type) == 1)
      then
	 danger_res = this:getDanger(posX[i], posY[i])
	 res = dir[i]
      end
   end
   -- print(showdir(dir[i]))
   -- print()
   -- print()
   -- print()
   -- nodir = this:getDanger(x, y)
   -- up =  this:getDanger(x, y -0.5)
   -- right = this:getDanger(x + 0.05, y)
   -- left = this:getDanger(x - 0.05, y)
   -- down = this:getDanger(x, y + 0.5)

   -- up_isgood = this:isCrossable(x, y - 0.05, type)
   -- right_isgood = this:isCrossable(x + 0.05, y, type)
   -- left_isgood =  this:isCrossable(x - 0.05, y, type)
   -- down_isgood = this:isCrossable(x, y + 0,5)
   return (res)
end
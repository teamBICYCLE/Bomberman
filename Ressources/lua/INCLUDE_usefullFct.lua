#!/usr/bin/lua

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

   for j = 1, #(posX) do
      local tmp = this:getDanger(posX[j], posY[j])
      if (tmp > 0 and j == 1)
      then
	 return (tmp)
      end
      res = res + tmp
   end
   return (res / #(posX))
end

function getZonePheromones(this, x, y)
   local posX = { x + 1     , x - 1     , x         , x         }
   local posY = { y         , y         , y - 1     , y + 1     }

   local res = 0
   for l = 1, #(posX) do
      tmp = this:getPheromones(posX[l], posY[l])
      if (tmp >= 0)
      then
	 res = res + tmp
      end
   end
   return (res / #(posX))
end


function testCross(this, x, y, type)
   local dir =  { RIGHT     , LEFT      , UP        , DOWN      }
   local posX = { x + 1     , x - 1     , x         , x         }
   local posY = { y         , y         , y - 1     , y + 1     }
   local dirX = { x + SPEED , x - SPEED , x         , x         }
   local dirY = { y         , y         , y - SPEED , y + SPEED }

   local res_dir = NODIR
   local danger = getZoneDanger(this, floor(x), floor(y))

   for  i = 1, #(dir) do
      local tmpDanger = getZoneDanger(this, floor(posX[i]), floor(posY[i]))
      if (danger > 0 and
	  tmpDanger < danger
	  and this:isCrossable(floor(posX[i]), floor(posY[i]), type) == 1
          and this:isCrossable(dirX[i], dirY[i], type) == 1)
      then
	 danger = tmpDanger
	 res_dir = dir[i]
      end
   end
   return res_dir, danger
end

function UpperRight(this, x, y, type)
   if (this:isCrossable(floor(x + 1), floor(y), type) == 1 and this:isCrossable(x + SPEED, y, type) == 1)
   then
      return (RIGHT)
   elseif (this:isCrossable(floor(x), floor(y - 1), type) == 1 and this:isCrossable(x, y - SPEED, type) == 1)
   then
      return (UP)
   end
   return (NODIR)
end

function UpperLeft(this, x, y, type)
   if (this:isCrossable(floor(x - 1), floor(y), type) == 1 and this:isCrossable(x - SPEED, y, type)== 1)
   then
      return (LEFT)
   elseif (this:isCrossable(floor(x), floor(y - 1), type) == 1 and this:isCrossable(x, y - SPEED, type)== 1)
   then
      return (UP)
   end
   return (NODIR)
end

function BottomRight(this, x, y, type)
   if (this:isCrossable(floor(x + 1), floor(y), type) == 1 and this:isCrossable(x + SPEED, y, type)== 1)
   then
      return (RIGHT)
   elseif (this:isCrossable(floor(x), floor(y + 1), type) == 1 and this:isCrossable(x, y + SPEED, type)== 1)
   then
      return (DOWN)
   end
   return (NODIR)
end

function BottomLeft(this, x, y, type)
   if (this:isCrossable(floor(x - 1), floor(y), type) == 1 and this:isCrossable(x - SPEED, y, type)== 1)
   then
      return (LEFT)
   elseif (this:isCrossable(floor(x), floor(y + 1), type) == 1 and this:isCrossable(x, y + SPEED, type)== 1)
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

   for  i = 1, #(posX) do
      for  j = 1, #(posY) do
	 local tmpDanger = getZoneDanger(this, floor(posX[i]), floor(posY[j]))
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

   res_dir, danger = testCross(this, x, y, type)
   res_dir = testAngles(this, x, y, type, danger, res_dir)
   if (res_dir == NODIR)
   then
      return (exploreMap(this, x, y, type))
   end
   return (res_dir)
end

function center(x, y, dir)
   local diffX = x - floor(x)
   local diffY = y - floor(y)

   if (dir == NODIR or dir == UP or dir == DOWN)
   then
      if (diffX > 0.25)
      then
	 return LEFT
      elseif (diffX < 0.20)
      then
	 return	RIGHT
      end
   end
   if (dir == NODIR or dir == RIGHT or dir == LEFT)
   then
      if (diffY > 0.25)
      then
	 return UP
      elseif (diffY < 0.20)
      then
	 return DOWN
      end
   end
   return dir
end

function trackPlayer(this, x, y, type)
   local dir =  { RIGHT   , LEFT    , UP      , DOWN     }
   local posX = { x + 1   , x - 1   , x       , x        }
   local posY = { y       , y       , y - 1   , y + 1    }
   local dirX = { x + SPEED, x - SPEED , x      , x        }
   local dirY = { y       , y       , y - SPEED, y + SPEED }

   local res_dir = NODIR
   local res_ph = this:getPheromones(floor(x), floor(y))
   for  k = 1, #(dir) do
      local tmp = this:getPheromones(floor(posX[k]), floor(posY[k]))
      if (res_ph < tmp  and tmp > 0 and this:isCrossable(floor(posX[k]), floor(posY[k]), type) == 1
       and this:isCrossable(dirX[k], dirY[k], type) == 1
    and getZoneDanger(this, floor(posX[k]), floor(posY[k])) ~= DANGER_MAX)
      then
	 res_ph = tmp
	 res_dir = dir[k]
      end
   end
   return (res_dir)
end

function exploreMap(this, x, y, type)
   local dir = {RIGHT      , LEFT     , UP       , DOWN     }
   local posX = { x + 1    , x - 1    , x        , x        }
   local posY = { y        , y        , y - 1    , y + 1    }
   local dirX = { x + SPEED, x - SPEED, x        , x        }
   local dirY = { y        , y        , y - SPEED, y + SPEED}
   goodDir = {NODIR}

   math.randomseed(os.time() + floor(x) + floor(y))
   for h = 1, #(dir) do
      if (this:isCrossable(floor(posX[h]), floor(posY[h]), type) == 1
       and this:isCrossable(dirX[h], dirY[h], type) == 1)
      then
	 goodDir[#(goodDir) + 1] = dir[h]
      end
   end
   local decision = math.random(1, #(goodDir))
   return (goodDir[decision])
end

function escapeDanger(this, x, y, danger, type)
   if (danger > 1.11)
   then
      return (getLessDangerousDirection(this, x, y, type))
   end
   math.randomseed(os.time())
   local mad = math.random(1, 100)
   if (mad > 30)
   then
      return (exploreMap(this, x, y))
   end
   return (getLessDangerousDirection(this, x, y, type))
end
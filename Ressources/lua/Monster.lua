#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)
-- debug hooker is the function setHook(HOOKTYPE, count)
-- HOOKTYPE are : MASKCOUT, MASKRET MASKCALL MASKLINE

function this.thinking(this, x, y)
   --setHook(MASKCOUNT, 4)
  --printDebug("Thinking Ia !")
  -- print (x, y)
  -- print (this:isCrossable(x, y - 1, MONSTER))

   -- right, left, up, down  = 0, 0, 0, 0;
   -- while (right ~= 1 and left ~= 1 and up ~= 1 and down ~= 1) do
      math.randomseed(os.time())
      a = math.random(1, 5)
      if a == 1
      then
      -- 	 up = 1
      -- 	    printDebug("testing UP")
   if this:isCrossable(x, y - 0.05, MONSTER) == 1
   then
--      printDebug("UP")
      --print(this:getDanger(x, y -0.5))
      return UP
   end
elseif a == 2
      then
--      	 right = 1
--       	    printDebug("testing RIGHT")
   if this:isCrossable(x + 0.05, y, MONSTER) == 1
   then
  --    printDebug("RIGHT")
      --print(this:getDanger(x + 0.05, y))
      return RIGHT
   end
      elseif a == 3
      then
      	 -- down = 1
	 -- printDebug("testing DOWN")
   if this:isCrossable(x, y + 0.05, MONSTER) == 1
   then
    --  printDebug("DOWN")
      --print(this:getDanger(x + 0.05, y))
      return DOWN
   end
elseif a == 4
then
--       	 left = 1
-- 	 printDebug("LEFT")
   if this:isCrossable(x - 0.05, y, MONSTER) == 1
   then
      --printDebug("LEFT")
      --print(this:getDanger(x - 0.05, y))
      return LEFT
   end
end
-- end
   return NODIR
end

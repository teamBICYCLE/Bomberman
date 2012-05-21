#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)
-- debug hooker is the function setHook(HOOKTYPE, count)
-- HOOKTYPE are : MASKCOUT, MASKRET MASKCALL MASKLINE

function this.thinking(this, x, y)
   --setHook(MASKCOUNT, 4)
  --printDebug("Thinking Ia !")
  print (x, y)
  print (this:isCrossable(x, y - 1, MONSTER))
  math.randomseed(os.time())
  a = math.random(1, 5)
  if a == 1 and this:isCrossable(x, y - 1, MONSTER) == 1
  then
     printDebug("UP")
     return UP
  elseif a == 2 and this:isCrossable(x + 1, y, MONSTER) == 1
  then
     printDebug("RIGHT")
     return RIGHT
  elseif a == 3 and this:isCrossable(x, y + 1, MONSTER) == 1
  then
     printDebug("DOWN")
     return DOWN
  elseif a == 4 and this:isCrossable(x - 1, y, MONSTER) == 1
  then
     printDebug("LEFT")
     return LEFT
  end
return NODIR
end

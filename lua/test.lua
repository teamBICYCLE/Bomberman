#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)
-- debug hooker is the function setHook(HOOKTYPE, count)
-- HOOKTYPE are : MASKCOUT, MASKRET MASKCALL MASKLINE

function this.thinking(this)
--   setHook(MASKCOUNT, 1)
--   printDebug("Thinking Ia !")
   -- this:test()
   -- this:hello2()
   -- a, b = this:hello3()
   -- print(a)
   -- print(b)
   math.randomseed(os.time())
   return math.random(1, 5)
end

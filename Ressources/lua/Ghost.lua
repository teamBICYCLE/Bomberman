#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)
-- debug hooker is the function setHook(HOOKTYPE, count)
-- HOOKTYPE are : MASKCOUT, MASKRET MASKCALL MASKLINE

function this.thinking(this, x, y)
-- --   setHook(MASKCOUNT, 1)
-- --   printDebug("Thinking Ia !")
--    -- this:test()
--    -- this:hello2()
--    -- a, b = this:hello3()
--    -- print(a)
--    -- print(b)
--    math.randomseed(os.time())
--    a = math.random(1, 5)
--    if a == 1
--    then return UP
--    elseif a == 2
--    then return RIGHT
--    elseif a == 3
--    then return DOWN
--    elseif a == 4
--    then return LEFT
--    end
 return NODIR
end

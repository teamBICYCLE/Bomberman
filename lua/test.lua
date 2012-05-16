#!/usr/bin/lua

-- a debug fonction is avaiable, call printDebug(String)
-- debug hooker is the function setHook(HOOKTYPE, count)
-- HOOKTYPE are : MASKCOUT, MASKRET MASKCALL MASKLINE

function this.thinking(this, nb)
--   setHook(MASKCOUNT, 1)
   io.write ("IA is currently thinking !\n")
   print("testing debug !")
   printDebug("Debug is working !")
   print("showing number")
   print(nb)
   this:test()
   -- this:hello2()
   -- a, b = this:hello3()
   -- print(a)
   -- print(b)
   return 5 -3
end

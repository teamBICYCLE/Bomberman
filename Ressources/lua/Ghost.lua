-- #!/usr/bin/lua

-- -- a debug fonction is avaiable, call printDebug(String)

-- dofile("Ressources/lua/INCLUDE_usefullFct.lua")

-- function this.thinking(this, x, y)
--    local danger = getZoneDanger(this,floor(x), floor(y))
--    local pheromones = getZonePheromones(this, x, y)

--    if ((danger * 10) > (pheromones / 10) * 0.9)
--     then
--        return (center(x, y, getLessDangerousDirection(this, x, y , danger, GHOST)))
--     elseif (pheromones > 0)
--     then
--        return (center(x, y, trackPlayer(this, x, y, GHOST)))
--     else
--        return (center(x, y, exploreMap(this, x, y, GHOST)))
--     end
-- end

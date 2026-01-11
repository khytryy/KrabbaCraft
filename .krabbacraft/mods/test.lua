local tarLogger = require("tarLogger")

return {
    tarOnTick = function(time)
        tarLogger.debug("KrabbaMod", "Tick! GLFW Time: " .. time .. " num: " .. math.random())
    end
}
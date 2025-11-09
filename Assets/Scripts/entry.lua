print("Hello from Lua!")

luaText = "Hello from Lua!"

local hasSetToolbar = false

function OnUpdate(_, currentTime)
	SetStatusBarMessage(currentTime .. ": This was done with Lua!")
--[==[
	if not hasSetToolbar then
		hasSetToolbar = true
		AddToolbar("Test toolbar", "Test action")
	end
]==]
end
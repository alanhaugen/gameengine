#include "ScriptingSystem.h"
#include <QDebug>
#include "Utilities.h"

gea::ScriptingSystem::ScriptingSystem(Engine *engineInstance) : SystemBase(engineInstance)
{
    //activeWindow = this;

    //Starts a new Lua state, which is like a new Lua interpreter
    lua_vm = luaL_newstate();

    //test if the Lua state was created successfully
    if (lua_vm == NULL)
    {
        qDebug() << "Lua state not generated - stopping now!\n";
        return;
    }

    // this is necessary to use Lua's standard libraries
    luaL_openlibs(lua_vm);

    //Register the C++ functions to be callable from Lua
    lua_register(lua_vm, "SetStatusBarMessage", lua_SetStatusBarMessage);
    lua_register(lua_vm, "AddToolbar", lua_AddToolbar);

    //Run the entry.lua script, which sets up the engine and calls user scripts
    int status = luaL_dofile(lua_vm, std::string(PATH + "Assets/Scripts/entry.lua").c_str());
    if (status != LUA_OK)
    {
        const char* error_msg = lua_tostring(lua_vm, -1);
        qDebug() << "Error running entry.lua: " << (error_msg ? error_msg : "Unknown error");
        lua_pop(lua_vm, 1); // remove error message from stack
        return; // exit with error code
    }

    std::thread t(outerLoop);
    t.detach();
}

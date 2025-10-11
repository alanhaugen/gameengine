#include "ScriptingSystem.h"
#include <QDebug>
#include <chrono>
#include <thread>
#include "Utilities.h"

gea::ScriptingSystem::ScriptingSystem(MainWindow *mainwindow, Engine *engineInstance) : SystemBase(engineInstance)
{
    mActiveWindow = mainwindow;

    //Starts a new Lua state, which is like a new Lua interpreter
    mLuaVm = luaL_newstate();

    //test if the Lua state was created successfully
    if (mLuaVm == NULL)
    {
        qDebug() << "Lua state not generated - stopping now!\n";
        return;
    }

    // this is necessary to use Lua's standard libraries
    luaL_openlibs(mLuaVm);

    //Register the C++ functions to be callable from Lua
    //lua_register(mLuaVm, "SetStatusBarMessage", lua_SetStatusBarMessage);
    // lua_register(mLuaVm, "AddToolbar", lua_AddToolbar);

    //Run the entry.lua script, which sets up the engine and calls user scripts
    int status = luaL_dofile(mLuaVm, std::string(PATH + "Assets/Scripts/entry.lua").c_str());
    if (status != LUA_OK)
    {
        const char* error_msg = lua_tostring(mLuaVm, -1);
        qDebug() << "Error running entry.lua: " << (error_msg ? error_msg : "Unknown error");
        lua_pop(mLuaVm, 1); // remove error message from stack
        return; // exit with error code
    }

    //fetches a variable from Lua
    lua_getglobal(mLuaVm, "luaText");	//"luaText" is pushed onto the stack inside Lua, and the value of "luaText" is now on top of the stack
    int i = lua_gettop(mLuaVm);			//fetches the index of the top element on the stack
    const char* message = lua_tostring(mLuaVm, i);	//gets the string value of the top element on the stack

    mActiveWindow->setStatusBarMessage(message);

    qDebug() << message;

    // std::thread t(OuterLoop);
    // t.detach();
}

void gea::ScriptingSystem::outerLoop()
{
    int FPS = 60;
    std::chrono::milliseconds frameDuration(1000 / FPS);
    std::chrono::milliseconds lastFrame(0);
    while (true) {
        auto now = std::chrono::system_clock::now();
        auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()
            );
        std::chrono::milliseconds timeSinceLastFrame = currentTime - lastFrame;
        if (timeSinceLastFrame >= frameDuration && mActiveWindow)
        {
            lastFrame = currentTime;
            // Call the Lua update function
            lua_getglobal(mLuaVm, "OnUpdate");
            lua_pushnumber(mLuaVm, timeSinceLastFrame.count()); // Push delta time in millisecondds
            lua_pushnumber(mLuaVm, currentTime.count()); // Push current time in millisecondds
            if (lua_pcall(mLuaVm, 2, 0, 0) != LUA_OK)
            {
                const char* error_msg = lua_tostring(mLuaVm, -1);
                qDebug() << "Error running OnUpdate: " << (error_msg ? error_msg : "Unknown error");
                lua_pop(mLuaVm, 1); // remove error message from stack
            }
        }
        std::this_thread::yield();
    }
}

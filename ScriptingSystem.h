#ifndef SCRIPTINGSYSTEM_H
#define SCRIPTINGSYSTEM_H

#include "lua.hpp"  //lua include that has the extern "C" thingy internally
#include <chrono>
#include <thread>
#include <QDebug>
#include "Systems.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

lua_State* lua_vm;
class MainWindow* activeWindow;


// ASSERT failure in QWidget: "Widgets must be created in the GUI thread.", file C:\Users\qt\work\qt\qtbase\src\widgets\kernel\qwidget.cpp, line 947
// So this needs to be somehow changed to be possible


extern "C" int lua_SetStatusBarMessage(lua_State * L)
{
    const char* msg = luaL_checkstring(L, 1);
    // MainWindow::SetStatusBarMessage(msg);
    return 0; // No return values to Lua
}

extern "C" int lua_AddToolbar(lua_State* L)
{
    const char* name = luaL_checkstring(L, 1);
    const char* action = luaL_checkstring(L, 2);
    // MainWindow::AddToolbar(name, action);
    return 0; // No return values to Lua
}

int FPS = 60;
std::chrono::milliseconds frameDuration(1000 / FPS);
std::chrono::milliseconds lastFrame(0);
void outerLoop()
{
    while (true) {
        auto now = std::chrono::system_clock::now();
        auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()
            );
        std::chrono::milliseconds timeSinceLastFrame = currentTime - lastFrame;
        if (timeSinceLastFrame >= frameDuration && activeWindow)
        {
            lastFrame = currentTime;
            // Call the Lua update function
            lua_getglobal(lua_vm, "OnUpdate");
            lua_pushnumber(lua_vm, timeSinceLastFrame.count()); // Push delta time in millisecondds
            lua_pushnumber(lua_vm, currentTime.count()); // Push current time in millisecondds
            if (lua_pcall(lua_vm, 2, 0, 0) != LUA_OK)
            {
                const char* error_msg = lua_tostring(lua_vm, -1);
                qDebug() << "Error running OnUpdate: " << (error_msg ? error_msg : "Unknown error");
                lua_pop(lua_vm, 1); // remove error message from stack
            }
        }
        std::this_thread::yield();
    }
}
namespace gea
{
class ScriptingSystem : public SystemBase
{
public:
    ScriptingSystem(class Engine* engineInstance);
    void Update(float deltaTime) override {};
};
}

#endif // SCRIPTINGSYSTEM_H

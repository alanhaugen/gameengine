#ifndef SCRIPTINGSYSTEM_H
#define SCRIPTINGSYSTEM_H

#include "lua.hpp"  //lua include that has the extern "C" thingy internally
//#include <chrono>
//#include <thread>
#include <QDebug>
#include "ECS/Systems.h"
#include "Editor/MainWindow.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// ASSERT failure in QWidget: "Widgets must be created in the GUI thread.",
//file C:\Users\qt\work\qt\qtbase\src\widgets\kernel\qwidget.cpp, line 947
// So this needs to be somehow changed to be possible


namespace gea
{

class ScriptingSystem : public SystemBase
{
public:
    ScriptingSystem(class MainWindow *mainwindow, class Engine* engineInstance);

    void update(float deltaTime) override {};

    void outerLoop();

    MainWindow* mActiveWindow{nullptr};

    lua_State* mLuaVm{nullptr};

    int luaSetStatusBarMessage(lua_State * L)
    {
        const char* msg = luaL_checkstring(L, 1);
        mActiveWindow->setStatusBarMessage(msg);
        return 0; // No return values to Lua
    }

    // int lua_AddToolbar(lua_State* L)
    // {
    //     const char* name = luaL_checkstring(L, 1);
    //     const char* action = luaL_checkstring(L, 2);
    //     mActiveWindow->AddToolbar(name, action);
    //     return 0; // No return values to Lua
    // }

};

} //namespace gea

#endif // SCRIPTINGSYSTEM_H

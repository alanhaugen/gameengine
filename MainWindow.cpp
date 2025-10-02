#include "MainWindow.h"

#include <iostream>

#include "ui_MainWindow.h"
#include "Renderer.h"
#include <QKeyEvent>
#include <thread>

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

lua_State* lua_vm;
MainWindow* activeWindow;

void MainWindow::SetStatusBarMessage(const char* message)
{
	activeWindow->statusBar()->showMessage(message);
}

// ASSERT failure in QWidget: "Widgets must be created in the GUI thread.", file C:\Users\qt\work\qt\qtbase\src\widgets\kernel\qwidget.cpp, line 947
// So this needs to be somehow changed to be possible
void MainWindow::AddToolbar(const char* name, const char* action)
{
    QToolBar* toolbar = activeWindow->addToolBar(QString(name));
    toolbar->addAction(QString(action));
}

extern "C" int lua_SetStatusBarMessage(lua_State * L)
{
    const char* msg = luaL_checkstring(L, 1);
    MainWindow::SetStatusBarMessage(msg);
    return 0; // No return values to Lua
}

extern "C" int lua_AddToolbar(lua_State* L)
{
	const char* name = luaL_checkstring(L, 1);
    const char* action = luaL_checkstring(L, 2);
	MainWindow::AddToolbar(name, action);
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
                std::cout << "Error running OnUpdate: " << (error_msg ? error_msg : "Unknown error") << std::endl;
                lua_pop(lua_vm, 1); // remove error message from stack
            }
        }
        std::this_thread::yield();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    activeWindow = this;

    //Starts a new Lua state, which is like a new Lua interpreter
    lua_vm = luaL_newstate();

    //test if the Lua state was created successfully
    if (lua_vm == NULL)
    {
        std::cout << "Lua state not generated - stopping now!\n";
        return;
    }

    // this is necessary to use Lua's standard libraries
    luaL_openlibs(lua_vm);

	//Register the C++ functions to be callable from Lua
    lua_register(lua_vm, "SetStatusBarMessage", lua_SetStatusBarMessage);
    lua_register(lua_vm, "AddToolbar", lua_AddToolbar);

    //Run the entry.lua script, which sets up the engine and calls user scripts

    int status = luaL_dofile(lua_vm, "../../../Scripts/entry.lua");
    if (status != LUA_OK) {
        const char* error_msg = lua_tostring(lua_vm, -1);
        std::cout << "Error running entry.lua: " << (error_msg ? error_msg : "Unknown error") << std::endl;
        lua_pop(lua_vm, 1); // remove error message from stack
        return; // exit with error code
    }

    ui->setupUi(this);
    //MainWindow size:
    resize(1300, 850);

    setWindowTitle("INNgine");  //Main app title

    mVulkanWindow = new Renderer();
    mVulkanWindow->setTitle("Renderer");    //Render window title

    //Have to set the size of the Vulkan window here, otherwise it can not set up the swapchain correctly
    mVulkanWindow->setWidth(1100);
    mVulkanWindow->setHeight(700);
    mVulkanWindow->initVulkan();

    // Wrap VulkanRenderer (QWindow) into a QWidget
    QWidget* vulkanWidget = QWidget::createWindowContainer(mVulkanWindow, this);
    vulkanWidget->setMinimumSize(1100, 700);

    ui->VulkanLayout->addWidget(vulkanWidget);

    //sets the keyboard input focus to the MainWindow when program starts
    this->setFocus();

    //statusBar()->showMessage(" put something cool here! ");
    std::thread t(outerLoop);
    t.detach();
}

MainWindow::~MainWindow()
{
    if(mVulkanWindow)
    {
        delete mVulkanWindow;
        mVulkanWindow = nullptr;
    }
    delete ui;
}

void MainWindow::start()
{
    qDebug("Start is called");
    mVulkanWindow->requestUpdate();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        delete mVulkanWindow;
        mVulkanWindow = nullptr;
        close(); // Example: close window on ESC
    }
    if (event->key() == Qt::Key_Space) {
        start();
    }

}

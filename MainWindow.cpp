#include "MainWindow.h"
#include "EntityContainer.h"
#include "EntityModel.h"
#include "ui_MainWindow.h"
#include "Renderer.h"
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include "DisplayWidget.cpp"
#include <QUrl>
#include <QFileInfo>
#include <QDebug>
#include <QPointer>
#include <QPlainTextEdit>

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

//Extern declaration of logger variable from main
extern QPointer<QPlainTextEdit> messageLogWidget;

MainWindow::MainWindow(QWidget* parent,
    std::vector<gea::RenderComponent> staticComponents, std::vector<gea::Transform> staticTransformComponents,
    std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures)
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
    int status = luaL_dofile(lua_vm, std::string(PATH + "Assets/Scripts/entry.lua").c_str());
    if (status != LUA_OK)
    {
        const char* error_msg = lua_tostring(lua_vm, -1);
        qDebug() << "Error running entry.lua: " << (error_msg ? error_msg : "Unknown error");
        lua_pop(lua_vm, 1); // remove error message from stack
        return; // exit with error code
    }

    ui->setupUi(this);

    //Assign logView widget
    messageLogWidget = ui->logView;
    messageLogWidget->setReadOnly(true);

    //MainWindow size:
    resize(1300, 850);

    setWindowTitle("INNgine");  //Main app title

    mVulkanWindow = new Renderer();
    mVulkanWindow->setTitle("Renderer");    //Render window title

    //Have to set the size of the Vulkan window here, otherwise it can not set up the swapchain correctly
    mVulkanWindow->setWidth(1100);
    mVulkanWindow->setHeight(700);

	SetupRenderSystem(staticComponents, staticTransformComponents, meshes, textures);
    //mVulkanWindow->initVulkan();

    // Wrap VulkanRenderer (QWindow) into a QWidget
    QWidget* mVulkanWidget = QWidget::createWindowContainer(mVulkanWindow, this);
    mVulkanWidget->setMinimumSize(1100, 700);

    // Put the mVulkanWidget into the VulkanLayout spot, made in the MainWindow.ui file
    ui->VulkanLayout->addWidget(mVulkanWidget);

    mEntityContainer = new gea::EntityContainer(this);
    mEntityModel = new gea::EntityModel(mEntityContainer, this);

    //Testing the layout - showing only number for now
    mEntityContainer->appendItem(gea::Entity());

    ui->entityList->setModel(mEntityModel);

    //sets the keyboard input focus to the MainWindow when program starts
    this->setFocus();

    //-------------------------------------------file system widget-------------------------------------------------------
    // need to get asset manager from renderer itself, since manager that holds assets is created there
    //AssetManager<ObjAsset>* objManager=new AssetManager<ObjAsset>();

    if (mVulkanWindow->filesImported==true)
    {
        //FilesWindow<ObjAsset> filesWidget(mVulkanWindow->objManager);
        filesWidget= new FilesWindow(mVulkanWindow->objManager);
    }

    //////////////model view test/////////
    // QWidget window;
    // QHBoxLayout* layout=new QHBoxLayout(&*vulkanWidget);

    // QFileSystemModel* model= new QFileSystemModel;
    // model->setRootPath(QDir::homePath());
    // model ->setNameFilters({"*.obj","*.png","*.jpg"});
    // model->setNameFilterDisables(false);
    // QModelIndex tree_root= model->index(QDir::homePath());

    // QTreeView* tree=new QTreeView;
    // tree->setModel(model);
    // tree->setRootIndex(tree_root);

    // //preview

    // displayWidget* displayIcons= new displayWidget;
    // //

    // layout->addWidget(tree);
    // layout->addWidget(displayIcons);

    // QObject::connect(tree,&QTreeView::clicked,[&](const QModelIndex &index) {
    //     QString path=model->filePath(index);
    //     displayIcons->previewFile(path);
    // });
    // window.resize(1000,200);
    // window.show();

    //Sound - using Qts Multimedia system
    mAudioOutput = new QAudioOutput(this);
    mAudioOutput->setVolume(0.5);

    mMediaPlayer = new QMediaPlayer(this);
    mMediaPlayer->setAudioOutput(mAudioOutput);

    playSound();
    mCamera = &dynamic_cast<Renderer*>(mVulkanWindow)->mCamera;

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

void MainWindow::SetupRenderSystem(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::Transform> staticTransformComponents, std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures)
{
    mRenderSystem = new gea::RenderSystem(mVulkanWindow);
    mRenderSystem->Initialize(staticComponents, staticTransformComponents, meshes, textures);
}

void MainWindow::UpdateRenderSystem(std::vector<gea::RenderComponent> dynamicComponents, std::vector<gea::Transform> dynamicTransformComponents)
{
	mRenderSystem->Update(dynamicComponents, dynamicTransformComponents);
}

void MainWindow::start()
{
    qDebug("Start is called");
    mVulkanWindow->requestUpdate();
}

void MainWindow::setCameraSpeed(float value)
{
    mCameraSpeed += value;

    //Keep within some min and max values
    if(mCameraSpeed < 0.01f)
        mCameraSpeed = 0.01f;
    if (mCameraSpeed > 0.3f)
        mCameraSpeed = 0.3f;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        delete mVulkanWindow;
        mVulkanWindow = nullptr;
        close(); // Example: close window on ESC
    }
    if (event->key() == Qt::Key_Space)
        start();
}

void MainWindow::playSound()
{
    QString filePath = QString(PATH.c_str()) + "Assets/Sounds/Test Drive.mp3";

    if(!QFileInfo::exists(filePath))
    {
        qDebug() << "File does not exist:" << filePath;
        return;
    }

    mMediaPlayer->setSource(QUrl::fromLocalFile(filePath));
    mMediaPlayer->play();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        mInput.RMB = true;
    if (event->button() == Qt::LeftButton)
        mInput.LMB = true;
    if (event->button() == Qt::MiddleButton)
        mInput.MMB = true;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        mInput.RMB = false;
    if (event->button() == Qt::LeftButton)
        mInput.LMB = false;
    if (event->button() == Qt::MiddleButton)
        mInput.MMB = false;
}

void MainWindow::handleInput()
{
    //Camera
    //mCamera->setSpeed(0.f);  //cancel last frame movement

    //setCameraSpeed(100.0f);

    //if(mInput.RMB)
        qDebug() << "RMB held down";

    //if (mInput.RMB)
    //{
    //    if (mInput.W)
    //        mCamera->setSpeed(mCameraSpeed);
    //    if (mInput.S)
    //        mCamera->setSpeed(-mCameraSpeed);
    //    if (mInput.D)
    //        mCamera->moveRight(-mCameraSpeed);
    //    if (mInput.A)
    //        mCamera->moveRight(mCameraSpeed);
    //    if (mInput.Q)
    //        mCamera->moveUp(mCameraSpeed);
    //    if (mInput.E)
    //        mCamera->moveUp(-mCameraSpeed);
    //}
}

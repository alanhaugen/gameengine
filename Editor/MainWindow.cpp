#include "MainWindow.h"
#include "Core/Engine.h"
#include "EntityModel.h"
#include "Core/Renderer.h"
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include "Editor/DisplayWidget.cpp"
#include <QUrl>
#include <QFileInfo>
#include <QDebug>
#include <QPointer>
#include <QPlainTextEdit>
#include "ECS/ScriptingSystem.h"
#include "ECS/SoundSystem.h"
#include "ECS/RenderSystem.h"
#include "Editor/OutlinerDock.h"
#include "ui_MainWindow.h"
#include <QKeyEvent>


//Extern declaration of logger variable from main
extern QPointer<QPlainTextEdit> messageLogWidget;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
    , mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);

    //Assign logView widget
    messageLogWidget = mUi->logView;
    messageLogWidget->setReadOnly(true);

    //MainWindow size:
    resize(1300, 940); //(1000, 740);

    setWindowTitle("INNgine");  //Main app title

    mVulkanWindow = new Renderer();
    mVulkanWindow->setTitle("Renderer");    //Render window title
    mVulkanWindow->mMainWindow = this;      //VulkanWindow can now refer to this instance

    //Have to set the size of the Vulkan window here, otherwise it can not set up the swapchain correctly
    mVulkanWindow->setWidth(700);//1100
    mVulkanWindow->setHeight(700);

    //Do we have to make the Engine here to let that make the RenderSystem - to make the VulkanRenderer ?
    mEngine = new gea::Engine(mVulkanWindow, this);
    mVulkanWindow->mEngine = mEngine;   //tell the renderer of the engine

    // Wrap VulkanRenderer (QWindow) into a QWidget
    QWidget* mVulkanWidget = QWidget::createWindowContainer(mVulkanWindow, this);
    mVulkanWidget->setMinimumSize(400, 400); //

    // Put the mVulkanWidget into the VulkanLayout spot, made in the MainWindow.ui file
    mUi->VulkanLayout->addWidget(mVulkanWidget);


	// Show the entity outliner dock
    // This could probably be a local variable and not a class variable?
    mEntityModel = new gea::EntityModel(mEngine, this);

    // Making it a dock widget with the Entity list:
    gea::OutlinerDock* outlinerDock = new gea::OutlinerDock(mEntityModel,this);

    //Testing the layout
    mEngine->createEntity();
    mEngine->mEntityVector.at(0).mName = "Primus";
    mEngine->createEntity();
    mEngine->mEntityVector.at(1).mName = "Octigon";
    mEngine->createEntity();
    mEngine->mEntityVector.at(2).mName = "Tertius";

	// Add the outliner dock to the main window right side
    addDockWidget(Qt::RightDockWidgetArea, outlinerDock);

    //mUi->entityList->setModel(mEntityModel);

    //sets the keyboard input focus to the MainWindow when program starts
    this->setFocus();

    //-------------------------------------------file system widget-------------------------------------------------------
    // new: need to create asset manager in the "engine" and call it here

    mFilesWidget= new FilesWindow<gea::Mesh>(mEngine->mMeshManager, "Meshes");
    addDockWidget(Qt::BottomDockWidgetArea,mFilesWidget); //add files window as a docker at the bottom
    //docker can float by itself and be moved out or in main window
    mFilesWidget->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);

    mTextureWidget= new FilesWindow<gea::Texture>(mEngine->mTextureManager, "Textures");
    addDockWidget(Qt::BottomDockWidgetArea,mTextureWidget); //add files window as a docker at the bottom
    //docker can float by itself and be moved out or in main window
    mTextureWidget->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);

    // Enable tabbed docks and make the texture dock a tab of the files dock
    setDockOptions(dockOptions() | QMainWindow::AllowTabbedDocks);
    tabifyDockWidget(mFilesWidget, mTextureWidget); // mTextureWidget becomes a tab in the same area
    mFilesWidget->raise(); // show the Files tab initially

    mCamera = &(mVulkanWindow->mCamera);

    //Should eventually be run from the Engine
    gea::SoundSystem* testSound = new gea::SoundSystem(mEngine);
    testSound->setMainWindow(this);
    // testSound->playSound("Test Drive.mp3");

    //gea::ScriptingSystem* testScript = new gea::ScriptingSystem(this, mEngine);

    //statusBar()->showMessage(" put something cool here! ");
}

MainWindow::~MainWindow()
{
    if(mVulkanWindow)
        delete mVulkanWindow;
    if(mEngine)
        delete mEngine;
    if (mFilesWidget)
        delete mFilesWidget;
    delete mUi;
}

void MainWindow::setStatusBarMessage(const char* message)
{
    statusBar()->showMessage(message);
}

void MainWindow::start()
{
    qDebug("Start is called");
    mVulkanWindow->requestUpdate();
    // mEngine->mIsRunning = true;
    // mEngine->GameLoop(); //not correct yet
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        //Quitting the app on ESC key
        QApplication::quit();
    }

    if (event->key() == Qt::Key_Space)
        start();

    // For editor camera
    if(event->key() == Qt::Key_W)
        mInput.W = true;
    if(event->key() == Qt::Key_S)
        mInput.S = true;
    if(event->key() == Qt::Key_D)
        mInput.D = true;
    if(event->key() == Qt::Key_A)
        mInput.A = true;
    if(event->key() == Qt::Key_Q)
        mInput.Q = true;
    if(event->key() == Qt::Key_E)
        mInput.E = true;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    // For editor camera
    if(event->key() == Qt::Key_W)
        mInput.W = false;
    if(event->key() == Qt::Key_S)
        mInput.S = false;
    if(event->key() == Qt::Key_D)
        mInput.D = false;
    if(event->key() == Qt::Key_A)
        mInput.A = false;
    if(event->key() == Qt::Key_Q)
        mInput.Q = false;
    if(event->key() == Qt::Key_E)
        mInput.E = false;
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

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mInput.RMB)
    {
        //Using mMouseXYlast as deltaXY so we don't need extra variables
        mMouseXlast = event->pos().x() - mMouseXlast;
        mMouseYlast = event->pos().y() - mMouseYlast;

        mCamera->mYaw += mMouseXlast * mCameraRotateSpeed;
        mCamera->mPitch += mMouseYlast * mCameraRotateSpeed;

    }
    mMouseXlast = event->pos().x();
    mMouseYlast = event->pos().y();

}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    //if RMB, change the speed of the camera
    //The values here could be set in a config-file instead of being hardcoded
    if (mInput.RMB)
    {
        if (numDegrees.y() > 1)
        {
            mCameraSpeed += 0.0005f;
            if (mCameraSpeed > 0.1f)    //test to not go to high
                mCameraSpeed = 0.1f;
        }
        if (numDegrees.y() < 1)
        {
            mCameraSpeed -= 0.0005f;    //test to not go to low / negative
            if (mCameraSpeed < 0.0005f)
                mCameraSpeed = 0.0005f;
        }
    }
    event->accept();

}

void MainWindow::handleInput()
{
    //If camera is not set, don't try to update it!
    if (!mCamera)
        return;

    mCamera->resetMovement();  //reset last frame movement

    if (mInput.RMB)
    {
        if (mInput.W)
            mCamera->mCameraMovement.z += mCameraSpeed; //forward
        if (mInput.S)
            mCamera->mCameraMovement.z -= mCameraSpeed; //backward
        if (mInput.D)
            mCamera->mCameraMovement.x += mCameraSpeed; //right
        if (mInput.A)
            mCamera->mCameraMovement.x -= mCameraSpeed; //left
        if (mInput.Q)
            mCamera->mCameraMovement.y -= mCameraSpeed; //down
        if (mInput.E)
            mCamera->mCameraMovement.y += mCameraSpeed; //up
    }
}

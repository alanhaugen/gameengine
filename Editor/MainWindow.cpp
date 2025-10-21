#include "MainWindow.h"
#include "Core/Engine.h"
#include "EntityContainer.h"
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
    resize(1300, 940);

    setWindowTitle("INNgine");  //Main app title

    mVulkanWindow = new Renderer();
    mVulkanWindow->setTitle("Renderer");    //Render window title
    mVulkanWindow->mMainWindow = this;      //VulkanWindow can now refer to this instance

    //Have to set the size of the Vulkan window here, otherwise it can not set up the swapchain correctly
    mVulkanWindow->setWidth(1100);
    mVulkanWindow->setHeight(700);

    //Do we have to make the Engine here to let that make the RenderSystem - to make the VulkanRenderer ?
    mEngine = new gea::Engine(mVulkanWindow, this);
    mVulkanWindow->mEngine = mEngine;   //tell the renderer of the engine

    // Wrap VulkanRenderer (QWindow) into a QWidget
    QWidget* mVulkanWidget = QWidget::createWindowContainer(mVulkanWindow, this);
    mVulkanWidget->setMinimumSize(1100, 700);

    // Put the mVulkanWidget into the VulkanLayout spot, made in the MainWindow.ui file
    mUi->VulkanLayout->addWidget(mVulkanWidget);

    mEntityContainer = new gea::EntityContainer(this);
    mEntityModel = new gea::EntityModel(mEntityContainer, this);

    //Testing the layout - showing only number for now
    mEntityContainer->appendItem(gea::Entity());

    mUi->entityList->setModel(mEntityModel);

    //sets the keyboard input focus to the MainWindow when program starts
    this->setFocus();

    //-------------------------------------------file system widget-------------------------------------------------------
    // need to get asset manager from renderer itself, since manager that holds assets is created there
    //AssetManager<ObjAsset>* objManager=new AssetManager<ObjAsset>();

    if (mVulkanWindow->filesImported==true)
    {
        //FilesWindow<ObjAsset> filesWidget(mVulkanWindow->objManager);
        mFilesWidget= new FilesWindow(mVulkanWindow->objManager);
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

    mCamera = &(mVulkanWindow->mCamera);

    //Should eventually be run from the Engine
    gea::SoundSystem* testSound = new gea::SoundSystem(mEngine);
    testSound->setMainWindow(this);
    // testSound->playSound("Test Drive.mp3");

    gea::ScriptingSystem* testScript = new gea::ScriptingSystem(this, mEngine);

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

// void MainWindow::AddToolbar(const char* name, const char* action)
// {
//     QToolBar* toolbar = addToolBar(QString(name));
//     toolbar->addAction(QString(action));
// }

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

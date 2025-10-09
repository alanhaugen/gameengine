#include "MainWindow.h"
#include "Engine.h"
#include "EntityContainer.h"
#include "EntityModel.h"
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
#include "SoundSystem.h"
#include "ui_MainWindow.h"
#include "Renderer.h"
#include "RenderSystem.h"
#include <QKeyEvent>


//Extern declaration of logger variable from main
extern QPointer<QPlainTextEdit> messageLogWidget;

MainWindow::MainWindow(QWidget* parent,
    std::vector<gea::RenderComponent> staticComponents, std::vector<gea::Transform> staticTransformComponents,
    std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Assign logView widget
    messageLogWidget = ui->logView;
    messageLogWidget->setReadOnly(true);

    //MainWindow size:
    resize(1300, 850);

    setWindowTitle("INNgine");  //Main app title

    mVulkanWindow = new Renderer();
    mVulkanWindow->setTitle("Renderer");    //Render window title
    mVulkanWindow->mMainWindow = this;      //VulkanWindow can now refer to this instance

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

    mCamera = &dynamic_cast<Renderer*>(mVulkanWindow)->mCamera;

    mEngine = new gea::Engine();

    gea::SoundSystem* testSound = new gea::SoundSystem(mEngine);
    testSound->SetMainWindow(this);
    testSound->playSound("Test Drive.mp3");

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
    delete ui;
}

void MainWindow::SetupRenderSystem(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::Transform> staticTransformComponents, std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures)
{
    mRenderSystem = new gea::RenderSystem(mEngine, mVulkanWindow);
    mRenderSystem->Initialize(staticComponents, staticTransformComponents, meshes, textures);
}

void MainWindow::UpdateRenderSystem(std::vector<gea::RenderComponent> dynamicComponents, std::vector<gea::Transform> dynamicTransformComponents)
{
	mRenderSystem->Update(dynamicComponents, dynamicTransformComponents);
}

void MainWindow::SetStatusBarMessage(const char* message)
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
        //Quitting the app on ESC key
        QApplication::quit();
    }

    if (event->key() == Qt::Key_Space)
        start();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

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

}

void MainWindow::wheelEvent(QWheelEvent *event)
{

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

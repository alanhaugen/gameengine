#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Renderer.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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

    statusBar()->showMessage(" put something cool here! ");
    mCamera = &dynamic_cast<Renderer*>(mVulkanWindow)->mCamera;
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
    if (event->key() == Qt::Key_Escape) {
        delete mVulkanWindow;
        mVulkanWindow = nullptr;
        close(); // Example: close window on ESC
    }
    if (event->key() == Qt::Key_Space) {
        start();
    }

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

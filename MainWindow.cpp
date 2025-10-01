#include "MainWindow.h"
#include "EntityContainer.h"
#include "EntityModel.h"
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
    QWidget* mVulkanWidget = QWidget::createWindowContainer(mVulkanWindow, this);
    mVulkanWidget->setMinimumSize(1100, 700);

    // Put the mVulkanWidget into the VulkanLayout spot, made in the MainWindow.ui file
    ui->VulkanLayout->addWidget(mVulkanWidget);

    mEntityContainer = new gea::EntityContainer(this);
    mEntityModel = new gea::EntityModel(mEntityContainer, this);

    ui->entityList->setModel(mEntityModel);

    //sets the keyboard input focus to the MainWindow when program starts
    this->setFocus();

    statusBar()->showMessage(" put something cool here! ");
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

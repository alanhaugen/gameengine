#include "MainWindow.h"
#include "resourcemanager.h"
#include "ui_MainWindow.h"
#include "Renderer.h"
#include <QKeyEvent>
#include <QApplication>
#include <QPlainTextEdit>
#include <QVulkanInstance>
#include <QLibraryInfo>
#include <QLoggingCategory>
#include <QPointer>
#include <QDockWidget>

MainWindow::MainWindow(ResourceManager* resourceMgr, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , resourceManager(resourceMgr)          //Assign from main
{
    ui->setupUi(this);
    //MainWindow size:
    resize(1300, 850);

    setWindowTitle("INNgine");  //Main app title

    mVulkanWindow = new Renderer();
    mVulkanWindow->setTitle("Renderer");

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



    /*
     * Logger Implementation in MainWindow
     */
    QDockWidget* logDock = new QDockWidget("Logger", this);
    logDock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);

    // Creating the Log Widget
    messageLogWidget = new QPlainTextEdit(logDock);
    messageLogWidget->setReadOnly(true);

    // Setting the logger inside the widget
    logDock->setWidget(messageLogWidget);

    // Adding dock
    addDockWidget(Qt::BottomDockWidgetArea, logDock);



    statusBar()->showMessage(" put something cool here! ");

    //Background musick (not annoying)
    resourceManager->toggleBackgroundMusick();
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
    if (event->key() == Qt::Key_W) {
        messageLogWidget->appendPlainText("Marvin Marvin Marvin");
    }
    if (event->key() == Qt::Key_A) {
        messageLogWidget->appendPlainText("Erik Er Best");
        resourceManager->clickSound();
    }
    if (event->key() == Qt::Key_Q) {
        resourceManager->toggleBackgroundMusick();
    }

}


void MainWindow::on_action_Quit_triggered()
{
    delete mVulkanWindow;
    mVulkanWindow = nullptr;
    close();
}




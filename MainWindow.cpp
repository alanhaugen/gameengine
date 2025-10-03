#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Renderer.h"
#include <QKeyEvent>
#include <QUrl>
#include <QFileInfo>
#include <QDebug>

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

    audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(0.5);

    player = new QMediaPlayer(this);
    player->setAudioOutput(audioOutput);

    playSound();
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

void MainWindow::playSound()
{
    QString filePath = "C:/GitHub/GEA2025/Assets/Sounds/Test Drive.wav";

    if(!QFileInfo::exists(filePath))
    {
        qDebug() << "File does not exist:" << filePath;
        return;
    }

    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();
}


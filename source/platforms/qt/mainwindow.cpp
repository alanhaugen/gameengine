#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "../../modules/renderer/vulkan/vulkanrenderer.h"
#include <QKeyEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent, const char* windowTitle, int windowWidth, int windowHeight)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //MainWindow size:
    resize((1300 - 1100) + windowWidth, (850 - 700) + windowHeight);

    setWindowTitle(windowTitle);  //Main app title

    mVulkanWindow = new VulkanRenderer();
    mVulkanWindow->setTitle("Renderer");    //Render window title

    //Have to set the size of the Vulkan window here, otherwise it can not set up the swapchain correctly
    mVulkanWindow->setWidth(windowWidth);
    mVulkanWindow->setHeight(windowHeight);
    mVulkanWindow->initVulkan();

    // Wrap VulkanRenderer (QWindow) into a QWidget
    vulkanWidget = QWidget::createWindowContainer(mVulkanWindow, this);
    //vulkanWidget->setMinimumSize(windowWidth, windowHeight);

    vulkanWidget->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
    vulkanWidget->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
    vulkanWidget->setMinimumWidth(200.0f);

    ui->VulkanLayout->addWidget(vulkanWidget);

    ui->splitter->setSizes(QList<int>()<<200<<900<<300);

    //sets the keyboard input focus to the MainWindow when program starts
    this->setFocus();

    statusBar()->showMessage(" put something cool here! ");

    QTreeWidgetItem* item1 = new QTreeWidgetItem(QStringList("Viking Room 1"), 0);
    QTreeWidgetItem* item2 = new QTreeWidgetItem(QStringList("Viking Room 2"), 0);
    ui->treeGameObjects->addTopLevelItem(item1);
    ui->treeGameObjects->addTopLevelItem(item2);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::MainGameLoop);

    timer->start(8); // 120 Hz

    lastTime = std::chrono::high_resolution_clock::now();
}

MainWindow::~MainWindow()
{
    cleanup();
}

void MainWindow::start()
{
    if (mVulkanWindow)
    {
        mVulkanWindow->requestUpdate();
    }
}

void MainWindow::cleanup()
{
    if(mVulkanWindow)
    {
        delete mVulkanWindow;
        mVulkanWindow = nullptr;
    }

    if (ui)
    {
        delete ui;
    }
}

// Fixed update time step
void MainWindow::MainGameLoop()
{
    // Calculate delta time, this can be used for a variable time step
    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
    lastTime = std::chrono::high_resolution_clock::now();

    if (scene)
    {
        scene->Update();
    }

    /*if (audio)
    {
        audio->Update();
    }

    if (filesystem)
    {
        filesystem->Update();
    }

    if (physics)
    {
        physics->Update();
    }

    if (script)
    {
        script->Update();
    }*/

    if (mVulkanWindow)
    {
        mVulkanWindow->Render();

        vulkanWidget->repaint();
    }
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

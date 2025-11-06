#include "mainwindow.h"
#include "core/platforms/qt/qtapplication.h"
#include "ui_MainWindow.h"
#include "systems/renderer/vulkan/vulkanrenderer.h"
#include "core/components/mesh.h"
#include "core/components/cube.h"
#include <QTimer>
#include "core/components/gameobject.h"
#include <qinputdialog.h>
#include "core/x-platform/locator.h"
#include "core/x-platform/scene.h"
#include "systems/audio/openal/openalaudio.h"
#include "systems/audio/qtaudio/qtmultimediaaudio.h"
#include "systems/physics/aaphysics/aaphysics.h"

MainWindow::MainWindow(QWidget *parent, const char* windowTitle, int windowWidth, int windowHeight)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeGameObjects->setContextMenuPolicy(Qt::CustomContextMenu);
    //MainWindow size:
    resize((1300 - 1100) + windowWidth, (850 - 700) + windowHeight);

    setWindowTitle(windowTitle);  //Main app title

    renderer = new VulkanRenderer();
    renderer->setTitle("Renderer");    //Render window title

    //Have to set the size of the Vulkan window here, otherwise it can not set up the swapchain correctly
    renderer->setWidth(windowWidth);
    renderer->setHeight(windowHeight);
    renderer->windowWidth = windowWidth;
    renderer->windowHeight = windowHeight;
    renderer->initVulkan();

    // Wrap VulkanRenderer (QWindow) into a QWidget
    vulkanWidget = QWidget::createWindowContainer(renderer, this);
    //vulkanWidget->setMinimumSize(windowWidth, windowHeight);

    vulkanWidget->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
    vulkanWidget->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);

    vulkanWidget->setFocusPolicy(Qt::StrongFocus);

    ui->VulkanLayout->addWidget(vulkanWidget);

    //ui->splitter->setSizes(QList<int>()<<200<<900<<300);


    splitDockWidget(ui->dockGameObjects,ui->SceneDock,Qt::Horizontal);
    splitDockWidget(ui->SceneDock,ui->DockInspector ,Qt::Horizontal);


    //GameObject treewidget
    ui->treeGameObjects->setMinimumWidth(100);

    //sets the keyboard input focus to the renderer when program starts
    vulkanWidget->setFocus();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::MainGameLoop);

    timer->start(8); // 120 Hz


    //Connections to functions
    connect(ui->actionViking_Room, &QAction::triggered, this, &MainWindow::AddVikingRoom);
    connect(ui->actionCube, &QAction::triggered, this, &MainWindow::AddCube);
    connect(ui->actionSphere, &QAction::triggered, this, &MainWindow::AddSphere);

    //
    connect(ui->treeGameObjects, &QTreeWidget::customContextMenuRequested, this, &MainWindow::OnRightClickGameObjectWidget);

    lastTime = std::chrono::high_resolution_clock::now();

    //OpenALAudio* openAL = new OpenALAudio();
    QtMultimediaAudio* qtAudio = new QtMultimediaAudio();
    AAPhysics* aaphysics = new AAPhysics();

    //Locator::SetAudio(openAL);
    Locator::SetAudio(qtAudio);
    Locator::SetPhysics(aaphysics);
    Locator::SetRenderer(renderer);

    Locator::audio->Init();
    Locator::renderer->Init();
    Locator::script->Init();
    Locator::physics->Init();
    Locator::renderer->Init();
    Locator::filesystem->Init();
}

MainWindow::~MainWindow()
{
    cleanup();
}

void MainWindow::start()
{
    if (renderer)
    {
        renderer->requestUpdate();
    }
}

void MainWindow::cleanup()
{
    if(renderer)
    {
        delete renderer;
        renderer = nullptr;
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

    Locator::input.Update();
    scene->editor->UpdateStatusBar((std::string("(") + std::to_string(Locator::input.mouse.x) + ", " + std::to_string(Locator::input.mouse.y) + std::string(")")).c_str());

    if (scene)
    {
        scene->camera.Update();
        scene->Update();

        for (auto* obj : scene->gameObjects)
        {
            obj->Update();
        }
    }

    if (Locator::audio)
    {
        Locator::audio->Update();
    }

    if (Locator::filesystem)
    {
        Locator::filesystem->Update();
    }

    if (Locator::physics)
    {
        Locator::physics->Update();
    }

    if (Locator::script)
    {
        Locator::script->Update();
    }

    if (Locator::renderer)
    {
        Locator::renderer->Update();

        vulkanWidget->repaint();
    }
}

void MainWindow::OnRightClickGameObjectWidget(const QPoint &ClickedOn)
{
    qDebug() << "Right-click detected at" << ClickedOn;
    QTreeWidgetItem * GameObjSelected = ui->treeGameObjects->itemAt(ClickedOn);

    if(!GameObjSelected)
    {
        return;
    }

    QMenu menu(this);
    QAction* Rename = menu.addAction("Rename");

    QAction* Selected = menu.exec(ui->treeGameObjects->viewport()->mapToGlobal(ClickedOn));


    if(Selected == Rename)
    {
        QString newName = QInputDialog::getText(this,"Rename","NewName",QLineEdit::Normal,GameObjSelected->text(0));

        if(!newName.isEmpty())
        {
            GameObjSelected->setText(0,newName);

            void* ptrToObj = GameObjSelected->data(0,Qt::UserRole).value<void*>();
            GameObject* obj = reinterpret_cast<GameObject*>(ptrToObj);

            if(obj)
            {
                obj->SetName(newName);
            }
        }
    }

    if (isAlive == false)
    {
        close();
    }
}

void MainWindow::AddVikingRoom()
{
    GameObject* gameobj = new GameObject("VikingRoom");

    Mesh* mesh = new Mesh("Assets/Models/viking_room.obj");

    gameobj->AddComponent(mesh);

    scene->gameObjects.push_back(gameobj);
}

void MainWindow::AddCube()
{
    GameObject* gameobj = new GameObject("Cube");

    Cube* cube = new Cube();

    gameobj->AddComponent(cube);

    scene->gameObjects.push_back(gameobj);
}

void MainWindow::AddSphere()
{
    GameObject* gameobj = new GameObject("Sphere");

    Mesh* mesh = new Mesh("Assets/Models/ball.obj");

    gameobj->AddComponent(mesh);

    scene->gameObjects.push_back(gameobj);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (renderer)
    {
        delete renderer;
        renderer = nullptr;
        close();
    }

    timer->stop();
}

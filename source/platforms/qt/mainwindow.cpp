#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "../../modules/renderer/vulkan/vulkanrenderer.h"
#include "../../components/mesh.h"
#include <QKeyEvent>
#include <QTimer>
#include "../../components/GameObject.h"
#include <qinputdialog.h>


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
    renderer->initVulkan();

    // Wrap VulkanRenderer (QWindow) into a QWidget
    vulkanWidget = QWidget::createWindowContainer(renderer, this);
    //vulkanWidget->setMinimumSize(windowWidth, windowHeight);

    vulkanWidget->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
    vulkanWidget->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
    vulkanWidget->setMinimumWidth(200.0f);

    ui->VulkanLayout->addWidget(vulkanWidget);

    ui->splitter->setSizes(QList<int>()<<200<<900<<300);

    //GameObject treewidget
    ui->treeGameObjects->setMinimumWidth(100);


    //sets the keyboard input focus to the MainWindow when program starts
    this->setFocus();

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::MainGameLoop);

    timer->start(8); // 120 Hz


    //Connections to functions
    connect(ui->actionViking_Room, &QAction::triggered, this, &MainWindow::AddVikingRoom);
    connect(ui->actionCube, &QAction::triggered, this, &MainWindow::AddCube);
    connect(ui->actionSphere, &QAction::triggered, this, &MainWindow::AddSphere);

    //
    connect(ui->treeGameObjects, &QTreeWidget::customContextMenuRequested, this, &MainWindow::OnRightClickGameObjectWidget);





    lastTime = std::chrono::high_resolution_clock::now();
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


    for (auto* obj : scene->GameObjects)
    {
        if (!obj){

            qDebug()<<"Empty";
            continue;
        }

        qDebug()<<"Empty";
        if(obj->GetEntityId()==1)
        {
            qDebug()<<"Name" << obj->GetName();
        }
    }

    if (renderer)
    {
        renderer->Render();

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



}

void MainWindow::AddVikingRoom()
{
    Entity EntityID = 1;
    GameObject* gameobj = new GameObject("VikingRoom",EntityID);

    Mesh* mesh = new Mesh("Assets/Models/viking_room.obj", renderer, scene->editor);

    gameobj->AddComponent(mesh);

    scene->GameObjects.push_back(gameobj);

    scene->components.push_back(mesh);
    QTreeWidgetItem * MainObj = new QTreeWidgetItem(ui->treeGameObjects);

    MainObj->setText(0,gameobj->GetName());
    MainObj->setData(0, Qt::UserRole, QVariant::fromValue((void*)gameobj));
    MainObj->setExpanded(true);

    QTreeWidgetItem * ObjItem = new QTreeWidgetItem(MainObj);
   ObjItem->setText(0,"mesh");
   ObjItem->setData(0, Qt::UserRole, QVariant::fromValue((void*)mesh));

   MainObj->addChild(ObjItem);

    qDebug() << "Viking room";
}

void MainWindow::AddCube()
{
    //scene->components.push_back(new Mesh("Assets/Models/viking_room.obj", renderer, scene->editor));
    qDebug() << "Cube";
}

void MainWindow::AddSphere()
{
    //scene->components.push_back(new Mesh("Assets/Models/viking_room.obj", renderer, scene->editor));
    qDebug() << "Sphere";
}



void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        delete renderer;
        renderer = nullptr;
        close(); // Example: close window on ESC
    }
    if (event->key() == Qt::Key_Space) {
        start();
    }
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    delete renderer;
    renderer = nullptr;
    close();
}

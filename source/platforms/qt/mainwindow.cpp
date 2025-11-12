#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "../../modules/renderer/vulkan/vulkanrenderer.h"
#include "../../components/mesh.h"
#include <QTimer>
#include "../../components/gameobject.h"
#include "../../components/AssetManager.h"
#include <qinputdialog.h>
#include "../../x-platform/locator.h"
#include "../../modules/audio/openal/openalaudio.h"
#include "../../modules/physics/aaphysics/aaphysics.h"

MainWindow::MainWindow(QWidget *parent, const char* windowTitle, int windowWidth, int windowHeight)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeGameObjects->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->treeGameObjects->viewport()->installEventFilter(this);

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

    vulkanWidget->setFocusPolicy(Qt::NoFocus);

    ui->VulkanLayout->addWidget(vulkanWidget);

    //ui->splitter->setSizes(QList<int>()<<200<<900<<300);


    splitDockWidget(ui->dockGameObjects,ui->SceneDock,Qt::Horizontal);
    splitDockWidget(ui->SceneDock,ui->DockInspector ,Qt::Horizontal);


    //GameObject treewidget
    ui->treeGameObjects->setMinimumWidth(100);

    //sets the keyboard input focus to the MainWindow when program starts
    this->setFocus();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::MainGameLoop);

    timer->start(8); // 120 Hz

    //assetManager
    mAssetManager = new AssetManager;



    //allow the spinBox go to negative numbers
    ui->PosXSpin->setMinimum(-990);
    ui->PosYSpin->setMinimum(-990);
    ui->PosZSpin->setMinimum(-990);

    ui->RotationXSpin->setMinimum(-990);
    ui->RotationYSpin->setMinimum(-990);
    ui->RotationZSpin->setMinimum(-990);


    //Connections to functions

    // connect(ui->actionViking_Room, &QAction::triggered, this, &MainWindow::AddVikingRoom);
    // connect(ui->actionCube, &QAction::triggered, this, &MainWindow::AddCube);
    // connect(ui->actionSphere, &QAction::triggered, this, &MainWindow::AddSphere);

    //new version


    for (const QString& Objects : mAssetManager->GetMeshNames())
    {
        QAction* action =ui->menuAdd->addAction(Objects);


        connect(action,&QAction::triggered, this, [this, Objects](){AddNewObj(Objects);});
    }


    //SpinBoxes
    //Position
    connect(ui->PosXSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::PosObj);
    connect(ui->PosYSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::PosObj);
    connect(ui->PosZSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::PosObj);
    //Rotation
    connect(ui->RotationXSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::PosObj);
    connect(ui->RotationYSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::PosObj);
    connect(ui->RotationZSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::PosObj);
    //Scale
    connect(ui->ScaleXSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::PosObj);
    connect(ui->ScaleYSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::PosObj);
    connect(ui->ScaleZSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::PosObj);





    //MeshAvailables
    AvailableMeshes();

    ui->Inspectorwidget->setHidden(true);


    //clicks
    connect(ui->treeGameObjects, &QTreeWidget::customContextMenuRequested, this, &MainWindow::OnRightClickGameObjectWidget);


    connect(ui->treeGameObjects, &QTreeWidget::itemClicked, this, &MainWindow::OnLeftClickGameObjectWidget);


    lastTime = std::chrono::high_resolution_clock::now();

    OpenALAudio* openAL = new OpenALAudio();
    AAPhysics* aaphysics = new AAPhysics();

    Locator::SetAudio(openAL);
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

    //working area
    if(ObjSelected)
    {
         ui->Inspectorwidget->setHidden(false);
        if(ObjSelected->components.empty())
        {
            ui->MeshBox->setHidden(true);
        }
        else
        {
            ui->MeshBox->setHidden(false);
        }
    }
    else
    {
        ui->Inspectorwidget->setHidden(true);
    }




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
    //QAction* AddMesh = menu.addAction("AddMesh");
    //QAction* AddCollider = menu.addAction("AddCollider");
    QAction* Delete = menu.addAction("Delete");

    QAction* Selected = menu.exec(ui->treeGameObjects->viewport()->mapToGlobal(ClickedOn));

    void* ptrToObj = GameObjSelected->data(0,Qt::UserRole).value<void*>();
    GameObject* obj = reinterpret_cast<GameObject*>(ptrToObj);

    if(Selected == Rename)
    {
        QString newName = QInputDialog::getText(this,"Rename","NewName",QLineEdit::Normal,GameObjSelected->text(0));

        if(!newName.isEmpty())
        {
            GameObjSelected->setText(0,newName);

            if(obj)
            {
                obj->SetName(newName);
            }
        }
    }
    if(Selected == Delete)
    {

    }
}

void MainWindow::OnLeftClickGameObjectWidget(QTreeWidgetItem *item, int column)
{
    //needs a way to figure what you clicked on, atm just works if you click the parent

    if(!item)
    {
        ObjSelected = nullptr;
        return;
    }

    qDebug() << "Left-click detected at" << item;


    void* ptrToObj = item->data(column,Qt::UserRole).value<void*>();

    QString type = item->data(column,Qt::UserRole+1).toString();
    GameObject* obj =reinterpret_cast<GameObject*>(ptrToObj);
    Component* comp =reinterpret_cast<Component*>(ptrToObj);

    //ObjSelected = reinterpret_cast<GameObject*>(ptrToObj);


    //check what i click, but always connects it to the parent
    if(type == "GameObject")
    {
        ObjSelected =obj;
        //qDebug()<<"Parent";
    }
    else if(type == "Component")
    {
        ObjSelected = comp->GetGameObjectOwner();
       // qDebug()<<"componentboi"<< column;
    }


    UpdateInspector();

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->treeGameObjects->viewport() && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent= static_cast<QMouseEvent*>(event);
        QTreeWidgetItem* item = ui->treeGameObjects->itemAt(mouseEvent->pos());

        if(!item)
        {
            ObjSelected = nullptr;
            ui->treeGameObjects->clearSelection();
        }
    }

    return QMainWindow::eventFilter(obj,event);
}

void MainWindow::UpdateInspector()
{

    IsInspectorUpdated = true;

    ui->PosXSpin->setValue(ObjSelected->mTransform.mPosition.x);
    ui->PosYSpin->setValue(ObjSelected->mTransform.mPosition.y);
    ui->PosZSpin->setValue(ObjSelected->mTransform.mPosition.z);


    ui->RotationXSpin->setValue(ObjSelected->mTransform.mRotation.x);
    ui->RotationYSpin->setValue(ObjSelected->mTransform.mRotation.y);
    ui->RotationZSpin->setValue(ObjSelected->mTransform.mRotation.z);

    ui->ScaleXSpin->setValue(ObjSelected->mTransform.mScale.x);
    ui->ScaleYSpin->setValue(ObjSelected->mTransform.mScale.y);
    ui->ScaleZSpin->setValue(ObjSelected->mTransform.mScale.z);


  // qDebug() <<"helllllll"<<ObjSelected->mTransform.mScale.y;
    //when it get completed the editor this will attach the info of the components to the inspector
    if(!ObjSelected->components.empty())
    {
        for (Component* comp: ObjSelected->components)
        {
            qDebug()<<"found componentes" <<"/n";
            QString typeName = comp->GetName();

            if(typeName == "Mesh")
            {
                qDebug()<<"Has Mesh" <<"/n";
                Mesh* mesh = dynamic_cast<Mesh*>(comp);
                QString currentMeshName = QFileInfo(mesh->FilePath).baseName();
                qDebug()<<"info here:"<<currentMeshName <<"/n";
                int index = ui->Mesh_Combo->findText(currentMeshName);
                ui->Mesh_Combo->setCurrentIndex(index);
            }
        }
    }


    IsInspectorUpdated = false;


}

void MainWindow::AddNewObj(const QString &ObjectName)
{

    QString FilePath = mAssetManager->FindMesh(ObjectName);
    qDebug() << "Connected action" << FilePath;
    GameObject* gameobj = new GameObject(ObjectName);
    std::string path = FilePath.toStdString();

    //Mesh* mesh = new Mesh(path.c_str());

    try {
        Mesh* mesh = new Mesh(path.c_str());
        gameobj->AddComponent(mesh);
    } catch (const std::exception& e) {
        qDebug() << "Failed to load mesh:" << e.what();
    }
    //gameobj->AddComponent(mesh);





    scene->gameObjects.push_back(gameobj);

    QTreeWidgetItem * MainObj = new QTreeWidgetItem(ui->treeGameObjects);

    MainObj->setText(0,gameobj->GetName());
    MainObj->setData(0, Qt::UserRole, QVariant::fromValue((void*)gameobj));
    MainObj->setData(0,Qt::UserRole +1,"GameObject");
    MainObj->setExpanded(true);

    // QTreeWidgetItem * ObjItem = new QTreeWidgetItem(MainObj);
    // ObjItem->setText(0,"mesh");
    // ObjItem->setData(0, Qt::UserRole, QVariant::fromValue((void*)mesh));
    // ObjItem->setData(0,Qt::UserRole +1,"Component");

    // MainObj->addChild(ObjItem);

}





void MainWindow::AddVikingRoom()
{
    qDebug() << "Connected VikingRoom action";
    GameObject* gameobj = new GameObject("VikingRoom");

    Mesh* mesh = new Mesh("Assets/Models/viking_room.obj");

    gameobj->AddComponent(mesh);





    scene->gameObjects.push_back(gameobj);

    QTreeWidgetItem * MainObj = new QTreeWidgetItem(ui->treeGameObjects);

    MainObj->setText(0,gameobj->GetName());
    MainObj->setData(0, Qt::UserRole, QVariant::fromValue((void*)gameobj));
    MainObj->setData(0,Qt::UserRole +1,"GameObject");
    MainObj->setExpanded(true);

    QTreeWidgetItem * ObjItem = new QTreeWidgetItem(MainObj);
    ObjItem->setText(0,"mesh");
    ObjItem->setData(0, Qt::UserRole, QVariant::fromValue((void*)mesh));
    ObjItem->setData(0,Qt::UserRole +1,"Component");

    MainObj->addChild(ObjItem);
}

void MainWindow::AddCube()
{
    GameObject* gameobj = new GameObject("Cube");
    QTreeWidgetItem * MainObj = new QTreeWidgetItem(ui->treeGameObjects);

    MainObj->setText(0,gameobj->GetName());
    MainObj->setData(0, Qt::UserRole, QVariant::fromValue((void*)gameobj));
    MainObj->setData(0,Qt::UserRole +1,"GameObject");
    MainObj->setExpanded(true);
    //scene->components.push_back(new Mesh("Assets/Models/viking_room.obj", renderer, scene->editor));
    qDebug() << "Cube";
}

void MainWindow::AddSphere()
{
    GameObject* gameobj = new GameObject("Sphere");
    QTreeWidgetItem * MainObj = new QTreeWidgetItem(ui->treeGameObjects);

    MainObj->setText(0,gameobj->GetName());
    MainObj->setData(0, Qt::UserRole, QVariant::fromValue((void*)gameobj));
    MainObj->setData(0,Qt::UserRole +1,"GameObject");
    MainObj->setExpanded(true);
    //scene->components.push_back(new Mesh("Assets/Models/viking_room.obj", renderer, scene->editor));
    qDebug() << "Sphere";
}

void MainWindow::AvailableMeshes()
{
    ui->Mesh_Combo->clear();
    QStringList meshNames = mAssetManager->GetMeshNames();
    ui->Mesh_Combo->addItems(meshNames);
    //qDebug() <<"Hereitis" << ui->Mesh_Combo->count() << "/n";
}

void MainWindow::PosObj(double)
{

    if(!ObjSelected)
    {
        qDebug()<<"not found";
        return;
    }

    if(IsInspectorUpdated)
    {
        return;
    }

     qDebug()<<"found it";
    float Posx = static_cast<float>(ui->PosXSpin->value());
    float Posy = static_cast<float>(ui->PosYSpin->value());
    float Posz = static_cast<float>(ui->PosZSpin->value());


     glm::vec3 Pos =glm::vec3(Posx, Posy, Posz);

    float Rotx = static_cast<float>(ui->RotationXSpin->value());
    float Roty = static_cast<float>(ui->RotationYSpin->value());
    float Rotz = static_cast<float>(ui->RotationZSpin->value());

    glm::vec3 Rotation =glm::vec3(Rotx, Roty, Rotz);

    float Scalex = static_cast<float>(ui->ScaleXSpin->value());
    float Scaley = static_cast<float>(ui->ScaleYSpin->value());
    float Scalez = static_cast<float>(ui->ScaleZSpin->value());

    glm::vec3 Scale =glm::vec3(Scalex, Scaley, Scalez);


    ObjSelected->UpdateTransform(Pos,Rotation,Scale);
    UpdateInspector();





}

void MainWindow::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_WIN
    if (renderer)
    {
        delete renderer;
        renderer = nullptr;
        close();
        timer->stop();
    }
#endif
}

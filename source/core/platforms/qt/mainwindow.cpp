#include "mainwindow.h"
#include "core/components/ballemitter.h"
#include "core/components/boxcollider.h"
#include "core/components/bsplinesurface.h"
#include "core/components/cube.h"
#include "core/components/fpscamera.h"
#include "core/components/rigidbody.h"
#include "core/components/sphere.h"
#include "core/components/spherecollider.h"
#include "core/components/terrain.h"
#include "core/components/text.h"
#include "core/components/trackingspline.h"
#include "ui_MainWindow.h"
#include "systems/renderer/vulkan/vulkanrenderer.h"
#include "core/components/mesh.h"
#include <QTimer>
#include <QApplication>
#include <QFileDialog>
#include <qinputdialog.h>
#include "core/components/gameobject.h"
#include "core/x-platform/locator.h"
#include "core/x-platform/services.h"
#include "core/x-platform/generatedscene.h"
#include "systems/audio/openal/openalaudio.h"
#include "systems/audio/qtaudio/qtmultimediaaudio.h"
#include "systems/physics/aaphysics/aaphysics.h"

MainWindow::MainWindow(QWidget *parent, const char* windowTitle, int windowWidth, int windowHeight)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //AssetManager
    mAssetManager = new AssetManager();

    ui->setupUi(this);
    ui->treeGameObjects->setContextMenuPolicy(Qt::CustomContextMenu);
    //MainWindow size:

    QScreen *screen = this->screen();  // Qt finds the correct monitor
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    this->resize(width, height);

    this->setGeometry(0, 0,
                      screenGeometry.width(),
                      screenGeometry.height());

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

    vulkanWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    vulkanWidget->setFixedSize(windowWidth, windowHeight);

    vulkanWidget->setFocusPolicy(Qt::StrongFocus);

    ui->VulkanLayout->addWidget(vulkanWidget, 0);

    //ui->splitter->setSizes(QList<int>()<<200<<900<<300);


    //allow the spinBox go to negative numbers
    ui->PosXSpin->setMinimum(-990);
    ui->PosYSpin->setMinimum(-990);
    ui->PosZSpin->setMinimum(-990);

    ui->RotationXSpin->setMinimum(-990);
    ui->RotationYSpin->setMinimum(-990);
    ui->RotationZSpin->setMinimum(-990);

    ui->PosXSpin->setMaximum(990);
    ui->PosYSpin->setMaximum(990);
    ui->PosZSpin->setMaximum(990);

    ui->RotationXSpin->setMaximum(990);
    ui->RotationYSpin->setMaximum(990);
    ui->RotationZSpin->setMaximum(990);

    //Connections to functions Old version
    // connect(ui->actionViking_Room, &QAction::triggered, this, &MainWindow::AddVikingRoom);
    // connect(ui->actionCube, &QAction::triggered, this, &MainWindow::AddCube);
    // connect(ui->actionSphere, &QAction::triggered, this, &MainWindow::AddSphere);


    //Scenes
    connect(ui->actionEmpty_2,&QAction::triggered, this, [this](){NewScenes(4);});
    connect(ui->actionVikingRoom_2,&QAction::triggered, this, [this](){NewScenes(1);});
    connect(ui->actionPong_2,&QAction::triggered, this, [this](){NewScenes(2);});



    //new version
    /*for (const QString& Objects : mAssetManager->GetMeshNames())
    {
        QAction* action =ui->menuAdd->addAction(Objects);


        connect(action,&QAction::triggered, this, [this, Objects](){AddNewObj(Objects);});
    }*/

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
    AvailableTextures();

    //ui->Inspectorwidget->setHidden(true);


    //clicks
    connect(ui->treeGameObjects, &QTreeWidget::customContextMenuRequested, this, &MainWindow::OnRightClickGameObjectWidget);
    connect(ui->treeGameObjects, &QTreeWidget::itemClicked, this, &MainWindow::OnLeftClickGameObjectWidget);

    connect(ui->actionSave_Scene, &QAction::triggered, this, &MainWindow::SaveScene);
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::OpenScene);

    // New game object
    connect(ui->actionNew_GameObject, &QAction::triggered, this, &MainWindow::NewGameObject);
    connect(ui->AddComponentButton, &QPushButton::pressed, this, &MainWindow::OpenComponentSelection);

    // Component actions
    connect(ui->actionCube_2, &QAction::triggered, this, &MainWindow::CreateCube);
    connect(ui->actionSphere_2, &QAction::triggered, this, &MainWindow::CreateSphere);
    connect(ui->actionSphere_Collider, &QAction::triggered, this, &MainWindow::CreateSphereCollider);
    connect(ui->actionBox_Collider, &QAction::triggered, this, &MainWindow::CreateBoxCollider);
    connect(ui->actionSprite, &QAction::triggered, this, &MainWindow::CreateSprite);
    connect(ui->actionText, &QAction::triggered, this, &MainWindow::CreateText);
    connect(ui->actionParticle_system, &QAction::triggered, this, &MainWindow::CreateParticleSystem);
    connect(ui->actionTerrain, &QAction::triggered, this, &MainWindow::CreateTerrain);
    connect(ui->actionWater, &QAction::triggered, this, &MainWindow::CreateWaterEmittor);
    connect(ui->actionRigid_Body_physics, &QAction::triggered, this, &MainWindow::CreateRigidBody);
    connect(ui->actionTracking_spline, &QAction::triggered, this, &MainWindow::CreateTrackingSpline);
    connect(ui->actionBSpline_surface, &QAction::triggered, this, &MainWindow::CreateBSplineSurface);

    connect(ui->actionPause, &QAction::triggered, this, &MainWindow::Pause);
    connect(ui->actionPlay, &QAction::triggered, this, &MainWindow::Play);

    connect(ui->action_Quit, &QAction::triggered, this, &QApplication::quit);

    //Mesh part
    connect(ui->Mesh_Combo, &QComboBox::currentTextChanged, this,&MainWindow::ChangeMesh);
    connect(ui->Material_box, &QComboBox::currentTextChanged, this,&MainWindow::ChangeMaterial);

    //GameObject treewidget
    ui->treeGameObjects->setMinimumWidth(100);

    //sets the keyboard input focus to the renderer when program starts
    vulkanWidget->setFocus();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::MainGameLoop);

    timer->start(8); // 120 Hz


    //Connections to functions
    //connect(ui->actionViking_Room, &QAction::triggered, this, &MainWindow::AddVikingRoom);
    //connect(ui->actionCube, &QAction::triggered, this, &MainWindow::AddCube);
    //connect(ui->actionSphere, &QAction::triggered, this, &MainWindow::AddSphere);

    //
    //connect(ui->treeGameObjects, &QTreeWidget::customContextMenuRequested, this, &MainWindow::OnRightClickGameObjectWidget);

    AUDIO* audio = new AUDIO();
    PHYSICS* physics = new PHYSICS();

    Locator::SetAudio(audio);
    Locator::SetPhysics(physics);
    Locator::SetRenderer(renderer);

    Locator::audio->Init();
    Locator::renderer->Init();
    Locator::script->Init();
    Locator::physics->Init();
    Locator::renderer->Init();
    Locator::filesystem->Init();

    //Camera

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

    deltaTime.Start();
}

void MainWindow::cleanup()
{
    if(renderer)
    {
        //delete renderer;
        //renderer = nullptr;
    }

    if (ui)
    {
        delete ui;
    }
}

// Fixed update time step
void MainWindow::MainGameLoop()
{
    //working area
    if(ObjSelected)
    {
        //ui->Inspectorwidget->setHidden(false);
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
        //ui->Inspectorwidget->setHidden(true);
    }

    Scene* scene = Services::currentScene;

    if (scene)
    {
        if (Locator::input.Held(Locator::input.Key.O))
        {
            Cam.speed += 0.01f;
        }
        if (Locator::input.Held(Locator::input.Key.L))
        {
            Cam.speed -= 0.01f;
        }

        Cam.camera = &scene->camera;
        Cam.Update();
        scene->camera.Update();

        if (paused == false)
        {
            scene->Update(deltaTime.TimeSinceStarted());
        }

        for (auto* obj : scene->gameObjects)
        {
            if (paused == false)
            {
                obj->Update();
            }

            if (Locator::editor)
            {
                Locator::editor->UpdateStatusBar((std::string("(") + std::to_string(Locator::input.mouse.x) + ", " + std::to_string(Locator::input.mouse.y) + std::string(")")).c_str());

                if (Locator::input.Held(Locator::input.Key.F))
                {
                    if (ObjSelected)
                    {
                        scene->camera.position = ObjSelected->GetPosition() - scene->camera.forward * 10.0f;
                    }
                }

                if (Locator::input.mouse.Down)
                {
                    if (Locator::physics->isColliding(scene->camera.ScreenPointToRay(Locator::input.mouse.x, Locator::input.mouse.y), obj))
                    {
                        if (ObjSelected)
                        {
                            ObjSelected->wiredCube->Hide();
                        }

                        ObjSelected = obj;
                        ObjSelected->wiredCube->Show();
                        UpdateInspector();
                    }
                }
            }
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

    Locator::input.Update();

    deltaTime.Reset();
}

void MainWindow::SaveScene()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Save Scene"),
        "",
        tr("Scene Files (*.json);;All Files (*)")
        );

    // Check if user canceled
    if (fileName.isEmpty())
        return;

    Services::currentScene->Save(fileName.toStdString());
    Log("Scene saved: " + fileName.toStdString());
}

void MainWindow::OpenScene()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open Scene"),
        "",
        tr("Scene Files (*.json);;All Files (*)")
        );

    // Check if user canceled
    if (fileName.isEmpty())
        return;

    Services::SetScene(new GeneratedScene(fileName.toStdString()));
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
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
                obj->name = newName.toStdString();
            }
        }
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

    if (ObjSelected)
    {
        ObjSelected->wiredCube->Hide();
    }

    qDebug() << "Left-click detected at" << item;

    // void* ptrToObj = item->data(column,Qt::UserRole).value<void*>();

    // QString type = item->data(column,Qt::UserRole+1).toString();
    // GameObject* obj =reinterpret_cast<GameObject*>(ptrToObj);
    // Component* comp =reinterpret_cast<Component*>(ptrToObj);

    // ObjSelected = reinterpret_cast<GameObject*>(ptrToObj);

    Scene* scene = Services::currentScene;

    uint32_t EntityID =  item->data(column,Qt::UserRole).toUInt();
    QString type = item->data(column,Qt::UserRole+1).toString();
    auto it = std::find_if(scene->gameObjects.begin(),scene->gameObjects.end(),[EntityID](GameObject* go){return go->id == EntityID;});
    GameObject* obj;
    if(it != scene->gameObjects.end())
    {
        obj= *it;
       // qDebug()<<"aya" << obj->name;
    }
    else
    {
        obj = nullptr;
       // qDebug()<<"Balls";
    }

    ObjSelected = obj;

    if (ObjSelected)
    {
        ObjSelected->wiredCube->Show();
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

    if (!ObjSelected)
    {
         qDebug()<<"no where";
        return;
    }

    glm::vec3 pos = glm::vec3(ObjSelected->matrix[3]);

    ui->PosXSpin->setValue(pos.x);
    ui->PosYSpin->setValue(pos.y);
    ui->PosZSpin->setValue(pos.z);

    glm::quat rotation = glm::quat(ObjSelected->matrix);
    glm::vec3 eulerAngles = glm::eulerAngles(rotation);

    ui->RotationXSpin->setValue(eulerAngles.x);
    ui->RotationYSpin->setValue(eulerAngles.y);
    ui->RotationZSpin->setValue(eulerAngles.z);

    glm::vec3 col1 = glm::vec3(ObjSelected->matrix[0]); // X-axis
    glm::vec3 col2 = glm::vec3(ObjSelected->matrix[1]); // Y-axis
    glm::vec3 col3 = glm::vec3(ObjSelected->matrix[2]); // Z-axis

    // Calculate the length of each vector to get the scaling factors
    glm::vec3 scale;
    scale.x = glm::length(col1);
    scale.y = glm::length(col2);
    scale.z = glm::length(col3);

    ui->ScaleXSpin->setValue(scale.x);
    ui->ScaleYSpin->setValue(scale.y);
    ui->ScaleZSpin->setValue(scale.z);

    // when it get completed the editor this will attach the info of the components to the inspector
    if(!ObjSelected->components.empty())
    {
        for (Component* comp: ObjSelected->components)
        {
            QString typeName = comp->name.c_str();

            if(typeName == "Mesh")
            {
                qDebug()<<"Has Mesh" <<"/n";
                Mesh* mesh = dynamic_cast<Mesh*>(comp);
                QString currentMeshName = QFileInfo(QString(mesh->FilePath.c_str())).baseName();
                QString currentTexture = QFileInfo(mesh->texture.c_str()).baseName();

                qDebug()<<"info here:"<<currentMeshName <<"/n";
                int index = ui->Mesh_Combo->findText(currentMeshName);
                int TextureIndex= ui->Material_box->findText(currentTexture);

                //qDebug()<<"Wow"<< mesh->texture << " :" << TextureIndex;
                //block it from colling change mesh
                QSignalBlocker blocker( ui->Mesh_Combo);
                QSignalBlocker blockerMaterial( ui->Material_box);
                ui->Mesh_Combo->setCurrentIndex(index);
                ui->Material_box->setCurrentIndex(TextureIndex);
            }
        }
    }

    IsInspectorUpdated = false;
}

void MainWindow::AddNewObj(const QString &ObjectName)
{
    QString FilePath = mAssetManager->FindMesh(ObjectName);
    qDebug() << "Connected action" << FilePath;
    GameObject* gameobj = new GameObject(ObjectName.toStdString());
    std::string path = FilePath.toStdString();

    Mesh* mesh = new Mesh(path.c_str());

    // try {
    //     Mesh* mesh = new Mesh(path.c_str());
    //     gameobj->AddComponent(mesh);
    // } catch (const std::exception& e) {
    //     qDebug() << "Failed to load mesh:" << e.what();
    // }
    gameobj->AddComponent(mesh);

    // QTreeWidgetItem * MainObj = new QTreeWidgetItem(ui->treeGameObjects);

    // MainObj->setText(0,gameobj->name.c_str());
    // MainObj->setData(0, Qt::UserRole, QVariant::fromValue(gameobj->id));
    // MainObj->setData(0,Qt::UserRole +1,"GameObject");
    // MainObj->setExpanded(true);

    // QTreeWidgetItem * ObjItem = new QTreeWidgetItem(MainObj);
    // ObjItem->setText(0,"mesh");
    // ObjItem->setData(0, Qt::UserRole, QVariant::fromValue(gameobj->id));
    // ObjItem->setData(0,Qt::UserRole +1,"Component");

    // MainObj->addChild(ObjItem);
}

void MainWindow::NewGameObject()
{
    GameObject* newObject = new GameObject();
    Camera* camera = &Services::currentScene->camera;
    newObject->SetPosition(camera->position + (camera->forward * 10.0f));
    newObject->wiredCube->Show();
    ObjSelected = newObject;

    newObject->wiredCube->drawable->ubo.model = newObject->matrix;

    UpdateInspector();
}

void MainWindow::OpenComponentSelection()
{
    ui->menuComponent->show();
}

void MainWindow::CreateCube()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    ObjSelected->AddComponent(new Cube);
}

void MainWindow::CreateSphere()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    ObjSelected->AddComponent(new Sphere);
}

void MainWindow::CreateSphereCollider()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    ObjSelected->AddComponent(new SphereCollider(ObjSelected));
}

void MainWindow::CreateBoxCollider()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    ObjSelected->AddComponent(new BoxCollider(ObjSelected, Physics::STATIC));
}

void MainWindow::CreateText()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    ObjSelected->AddComponent(new Text("Empty text"));
}

void MainWindow::CreateSprite()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    ObjSelected->AddComponent(new Sprite("Assets/Textures/orange.jpg"));
}

void MainWindow::CreateParticleSystem()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    //ObjSelected->AddComponent(new P(""));
}

void MainWindow::CreateTerrain()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    mainTerrain = new Terrain("tools/pointconverter/output.png", "Assets/Textures/aerial_rocks_04_diff_1k.jpg");//"Assets/Textures/snow.jpg");
    ObjSelected->AddComponent(mainTerrain);
}

void MainWindow::CreateWaterEmittor()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    ObjSelected->AddComponent(new BallEmitter(mainTerrain));
}

void MainWindow::CreateRigidBody()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    if (mainTerrain == nullptr)
    {
        CreateTerrain();
    }

    ObjSelected->AddComponent(new RigidBody(mainTerrain));
}

void MainWindow::CreateTrackingSpline()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    ObjSelected->AddComponent(new TrackingSpline);
}

void MainWindow::CreateBSplineSurface()
{
    if (ObjSelected == nullptr)
    {
        NewGameObject();
    }

    ObjSelected->AddComponent(new BSplineSurface);
}

void MainWindow::Pause()
{
    paused = true;
}

void MainWindow::Play()
{
    paused = false;
}

void MainWindow::AvailableTextures()
{
    ui->Material_box->clear();
    QStringList TextureNames = mAssetManager->GetTexturesNames();
    ui->Material_box->addItems(TextureNames);
}

void MainWindow::AvailableMeshes()
{
    ui->Mesh_Combo->clear();
    QStringList meshNames = mAssetManager->GetMeshNames();
    ui->Mesh_Combo->addItems(meshNames);
}

void MainWindow::ChangeMesh(const QString &meshname)
{
    for (Component* comp: ObjSelected->components)
    {
        if(comp->name == "Mesh")
        {
            Mesh* mesh = dynamic_cast<Mesh*>(comp);

            QString path = mAssetManager->FindMesh(meshname);
            mesh->loadMesh( path.toStdString().c_str());
        }
    }
}

void MainWindow::ChangeMaterial(const QString &Materialname)
{
   // qDebug() << "Fucky";
    for (Component* comp: ObjSelected->components)
    {
        if(comp->name == "Mesh")
        {
            Mesh* mesh = dynamic_cast<Mesh*>(comp);

            QString path = mAssetManager->FindTexture(Materialname);
            mesh->texture = path.toStdString().c_str();
            qDebug() << path;
            ChangeMesh(ui->Mesh_Combo->currentText());
        }
    }
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

    float Posx = static_cast<float>(ui->PosXSpin->value());
    float Posy = static_cast<float>(ui->PosYSpin->value());
    float Posz = static_cast<float>(ui->PosZSpin->value());

    float Rotx = static_cast<float>(ui->RotationXSpin->value());
    float Roty = static_cast<float>(ui->RotationYSpin->value());
    float Rotz = static_cast<float>(ui->RotationZSpin->value());

    float Scalex = static_cast<float>(ui->ScaleXSpin->value());
    float Scaley = static_cast<float>(ui->ScaleYSpin->value());
    float Scalez = static_cast<float>(ui->ScaleZSpin->value());

    // Rebuild model matrix from scratch
    ObjSelected->matrix = glm::mat4(1.0f);
    ObjSelected->matrix = glm::translate(ObjSelected->matrix, glm::vec3(Posx, Posy, Posz));
    ObjSelected->matrix = glm::rotate(ObjSelected->matrix, glm::radians(Rotx), glm::vec3(1, 0, 0));
    ObjSelected->matrix = glm::rotate(ObjSelected->matrix, glm::radians(Roty), glm::vec3(0, 1, 0));
    ObjSelected->matrix = glm::rotate(ObjSelected->matrix, glm::radians(Rotz), glm::vec3(0, 0, 1));
    ObjSelected->matrix = glm::scale(ObjSelected->matrix, glm::vec3(Scalex, Scaley, Scalez));

    // Update collison box for mouse picking in editor
    ObjSelected->dimensions = glm::vec3(Scalex, Scaley, Scalez);

    UpdateInspector();
}

void MainWindow::NewScenes(int index)
{
    if(ObjSelected)
    {
        ObjSelected->wiredCube->Hide();
        ObjSelected = nullptr;
    }
    ui->treeGameObjects->clear();
    Service.SetScene(index);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    timer->stop();
}

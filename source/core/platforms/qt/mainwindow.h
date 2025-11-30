#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtreewidget.h>
#include "core/components/fpvcamera.h"
#include "core/components/timer.h"
#include "core/x-platform/services.h"
#include "systems/renderer/vulkan/vulkanrenderer.h"

class Scene;
class GameObject;
class Terrain;
#include "assetmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class About;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,
               const char *windowTitle = "Inngine",
               int windowWidth = 1100,
               int windowHeight = 700);
    ~MainWindow();
    void closeEvent(QCloseEvent *event) override;
    void start();
    void cleanup();

    void MainGameLoop();
    void SaveScene();
    void OpenScene();

    bool paused = false;

    VulkanRenderer* renderer{nullptr};

    Ui::MainWindow *ui = nullptr;
    Ui::About *about = nullptr;
    QWidget *aboutWindow;

    void mousePressed(QMouseEvent*event);

    Timer deltaTime;




private:
    QWidget* vulkanWidget;
    QWidget* aboutWidget;

    //FPSCamera
    FPVCamera Cam;
    //Service
    Services Service;

    //ObjectSelect
    GameObject* ObjSelected = nullptr;

    void showEvent(QShowEvent *event) override;

    std::chrono::time_point<std::chrono::steady_clock> lastTime;

    //right click the object in gameobjectWidget
    void OnRightClickGameObjectWidget(const QPoint& ClickedOn);

    //Left click the object in gameobjectWidget
    void OnLeftClickGameObjectWidget(QTreeWidgetItem* item, int column);
    //deselect
    bool eventFilter(QObject* obj,QEvent* event) override;

    //Update inspector with values
    void UpdateInspector();
    //bool to prevent set value from changing values
    bool IsInspectorUpdated = false;

    //for the Menuadd
    //add Objects to the scene and to the gameobject
    void AddNewObj(const QString& ObjectName);
    void NewGameObject();
    void OpenComponentSelection();

    void CreateCube();
    void CreateSphere();
    void CreateSphereCollider();
    void CreateBoxCollider();
    void CreateText();
    void CreateSprite();
    void CreateParticleSystem();
    void CreateTerrain();
    void CreateWaterEmittor();
    void CreateRigidBody();
    void CreateTrackingSpline();
    void CreateBSplineSurface();
    void ShowOrHideGameObject();
    void CreatePointCloud();

    void ShowAboutWidget();
    void HideAboutWidget();

    void Pause();
    void Play();

    Terrain* mainTerrain;

    //add Textures to the scene and to the gameobject
    void AvailableTextures();


    //Adds the meshes to the combobox of meshes
    void AvailableMeshes();

    //Adds colliders to the combobox collider
    void AvailableColliders();

    //change mesh
    void ChangeMesh(const QString &meshname);

    void ChangeMaterial(const QString &Materialname);

    void PosObj(double);

    void NewScenes(int index);

    void CheckComponent();

    QTimer* timer;

    AssetManager* mAssetManager;
};
#endif // MAINWINDOW_H

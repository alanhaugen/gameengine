#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtreewidget.h>
#include "../../components/AssetManager.h"
#include "../../modules/renderer/vulkan/vulkanrenderer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
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

    VulkanRenderer* renderer{nullptr};

    Scene* scene = nullptr;
    Ui::MainWindow *ui = nullptr;

    void mousePressed(QMouseEvent*event);

private:
    QWidget* vulkanWidget;

    std::chrono::time_point<std::chrono::steady_clock> lastTime;

    //ObjectSelect
    GameObject* ObjSelected = nullptr;

    //bool to prevent set value from changing values
    bool IsInspectorUpdated = false;

    //QWidget* mRenderWindowContainer{nullptr};   //Qt container for the RenderWindow

    //right click the object in gameobjectWidget
   void OnRightClickGameObjectWidget(const QPoint& ClickedOn);

        //Left click the object in gameobjectWidget
   void OnLeftClickGameObjectWidget(QTreeWidgetItem* item, int column);
   //deselect
   bool eventFilter(QObject* obj,QEvent* event) override;

   //Update inspector with values
   void UpdateInspector();

    //for the Menuadd
    //add Objects to the scene and to the gameobject
    void AddVikingRoom();
    void AddCube();
    void AddSphere();



    void AvailableMeshes();


    void PosObj(double);

    QTimer* timer;

    AssetManager* mAssetManager;
};
#endif // MAINWINDOW_H

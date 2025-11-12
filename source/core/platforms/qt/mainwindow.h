#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtreewidget.h>
#include "systems/renderer/vulkan/vulkanrenderer.h"

class Scene;
class GameObject;

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

    //right click the object in gameobjectWidget
    void OnRightClickGameObjectWidget(const QPoint& ClickedOn);

    //for the Menuadd
    //add Objects to the scene and to the gameobject
    void AddVikingRoom();
    void AddCube();
    void AddSphere();


    void PosObj(double);

    QTimer* timer;
};
#endif // MAINWINDOW_H

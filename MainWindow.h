#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Engine.h"
#include "Mesh.h"
#include "Texture.h"
#include "FilesWindow.h"
#include <QKeyEvent>
#include "Components.h"

#include "Input.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

namespace gea {
    //Forward declarations
    class EntityContainer;
    class EntityModel;
    class RenderSystem;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

    ~MainWindow();

    void SetStatusBarMessage(const char* message);
    // void AddToolbar(const char* name, const char* action);

    void start();
    void handleInput();

private:
    Ui::MainWindow *ui;

    class Renderer* mVulkanWindow{nullptr};

    FilesWindow* mFilesWidget{nullptr};
    //FilesWindow<mVulkanWindow->objManager>(mVulkanWindow->objManager)* mFilesWidget{nullptr};

    //GUI for Entities
    class gea::EntityContainer* mEntityContainer{nullptr};
    class gea::EntityModel* mEntityModel{nullptr};
    class Camera* mCamera{ nullptr };

    void setCameraSpeed(float value);

    float mCameraSpeed{0.005f};
    float mCameraRotateSpeed{ -0.001f };
    int mMouseXlast{0}; //for mouse rotate input
    int mMouseYlast{0};
    Input mInput;

    gea::Engine* mEngine{nullptr};

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;


    friend class Renderer;    //so renderer can access protected methods

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fileswindow.h"
#include <QKeyEvent>
#include "RenderSystem.h"
#include "Components.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include "Input.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace gea {
class EntityContainer;
class EntityModel;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr,
        std::vector<gea::RenderComponent> staticComponents = std::vector<gea::RenderComponent>(), std::vector<gea::Transform> staticTransformComponents = std::vector<gea::Transform>(),
        std::vector<gea::Mesh> meshes = std::vector<gea::Mesh>(), std::vector<gea::Texture> textures = std::vector<gea::Texture>());

    ~MainWindow();

    void start();
    void UpdateRenderSystem(std::vector<gea::RenderComponent> dynamicComponents, std::vector<gea::Transform> dynamicTransformComponents);
    void handleInput();

private:
    Ui::MainWindow *ui;

    class Renderer* mVulkanWindow{nullptr};
    gea::RenderSystem* mRenderSystem{nullptr};

    void SetupRenderSystem(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::Transform> staticTransformComponents, std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures);

    FilesWindow* filesWidget{nullptr};
    //FilesWindow<mVulkanWindow->objManager>(mVulkanWindow->objManager)* filesWidget{nullptr};

    QMediaPlayer *mMediaPlayer{nullptr};
    QAudioOutput *mAudioOutput{nullptr};

    void playSound();

    //GUI for Entities
    class gea::EntityContainer* mEntityContainer{nullptr};
    class gea::EntityModel* mEntityModel{nullptr};
    class camera* mCamera{ nullptr };

    void setCameraSpeed(float value);

    float mCameraSpeed{0.005f};
    Input mInput;

protected:
    void keyPressEvent(QKeyEvent* event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H

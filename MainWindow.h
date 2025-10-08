#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fileswindow.h"
#include <QKeyEvent>
#include "RenderSystem.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr,
        std::vector<gea::RenderComponent> staticComponents = std::vector<gea::RenderComponent>(), std::vector<gea::TransformComponent> staticTransformComponents = std::vector<gea::TransformComponent>(),
        std::vector<gea::Mesh> meshes = std::vector<gea::Mesh>(), std::vector<gea::Texture> textures = std::vector<gea::Texture>());
    ~MainWindow();

    void start();
    void UpdateRenderSystem(std::vector<gea::RenderComponent> dynamicComponents, std::vector<gea::TransformComponent> dynamicTransformComponents);

private:
    Ui::MainWindow *ui;

    class Renderer* mVulkanWindow{nullptr};
    gea::RenderSystem* mRenderSystem{nullptr};

    void SetupRenderSystem(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::TransformComponent> staticTransformComponents, std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures);

    FilesWindow* filesWidget{nullptr};
    //FilesWindow<mVulkanWindow->objManager>(mVulkanWindow->objManager)* filesWidget{nullptr};

protected:
    void keyPressEvent(QKeyEvent* event) override;
};
#endif // MAINWINDOW_H

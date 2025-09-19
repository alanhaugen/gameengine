#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void start();
    void cleanup();

    VulkanRenderer* mVulkanWindow{nullptr};

private:
    Ui::MainWindow *ui = nullptr;

    //QWidget* mRenderWindowContainer{nullptr};   //Qt container for the RenderWindow

protected:
    void keyPressEvent(QKeyEvent* event) override;
};
#endif // MAINWINDOW_H

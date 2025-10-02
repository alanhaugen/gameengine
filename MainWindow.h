#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Input.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void start();
    void handleInput();

private:
    Ui::MainWindow *ui;

    //QWidget* mRenderWindowContainer{nullptr};   //Qt container for the RenderWindow
    class Renderer* mVulkanWindow{nullptr};
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

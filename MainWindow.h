#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameWorld.h"
#include <QMainWindow>
#include <qplaintextedit.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ResourceManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ResourceManager* resourceMgr, QWidget *parent = nullptr);
    ~MainWindow();

    QPlainTextEdit* messageLogWidget{nullptr};

    void start();

private:
    Ui::MainWindow *ui;
    ResourceManager* resourceManager = nullptr;       //Store pointer

    //QWidget* mRenderWindowContainer{nullptr};   //Qt container for the RenderWindow
    class Renderer* mVulkanWindow{nullptr};
    bbl::GameWorld mGameWorld;

    //GameWorld mGameWorld;

protected:
    //bool eventFilter(QObject* obj, QEvent* event);
    void keyPressEvent(QKeyEvent* event) override;
private slots:
    void on_action_Quit_triggered();
};
#endif // MAINWINDOW_H

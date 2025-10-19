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
    static QPointer<QPlainTextEdit> messageLogWidget;

    void start();

private:
    Ui::MainWindow *ui;
    ResourceManager* resourceManager = nullptr;

    //QWidget* mRenderWindowContainer{nullptr};   //Qt container for the RenderWindow
    class Renderer* mVulkanWindow{nullptr};
    bbl::GameWorld mGameWorld;

    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);


protected:
    //bool eventFilter(QObject* obj, QEvent* event);


private slots:
    void on_action_Quit_triggered();
    void on_action_Open_triggered();
};
#endif // MAINWINDOW_H

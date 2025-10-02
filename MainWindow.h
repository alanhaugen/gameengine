#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lua.hpp"  //lua include that has the extern "C" thingy internally

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static void SetStatusBarMessage(const char* message);
    static void AddToolbar(const char* name, const char* action);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void start();

private:
    Ui::MainWindow *ui;

    //QWidget* mRenderWindowContainer{nullptr};   //Qt container for the RenderWindow
    class Renderer* mVulkanWindow{nullptr};

protected:
    void keyPressEvent(QKeyEvent* event) override;
};
#endif // MAINWINDOW_H

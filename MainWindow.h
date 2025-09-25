#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    //QWidget* mRenderWindowContainer{nullptr};   //Qt container for the RenderWindow
    class Renderer* mVulkanWindow{nullptr};

protected:
    void keyPressEvent(QKeyEvent* event) override;
private slots:
    void on_action_Quit_triggered();
};
#endif // MAINWINDOW_H

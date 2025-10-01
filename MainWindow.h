#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>


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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void start();

private:
    Ui::MainWindow *ui;

    class Renderer* mVulkanWindow{nullptr};
    class gea::EntityContainer* mEntityContainer{nullptr};
    class gea::EntityModel* mEntityModel{nullptr};

protected:
    void keyPressEvent(QKeyEvent* event) override;
};
#endif // MAINWINDOW_H

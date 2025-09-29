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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QPointer<QPlainTextEdit> messageLogWidget;

    void start();

private:
    Ui::MainWindow *ui;

    //QWidget* mRenderWindowContainer{nullptr};   //Qt container for the RenderWindow
    class Renderer* mVulkanWindow{nullptr};
    bbl::GameWorld mGameWorld;

    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);


protected:
    //bool eventFilter(QObject* obj, QEvent* event);
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void on_action_Quit_triggered();
};
#endif // MAINWINDOW_H

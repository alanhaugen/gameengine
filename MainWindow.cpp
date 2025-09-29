#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Renderer.h"
#include <QKeyEvent>
#include <QApplication>
#include <QPlainTextEdit>
#include <QVulkanInstance>
#include <QLibraryInfo>
#include <QLoggingCategory>
#include <QPointer>
#include <QDockWidget>


QPointer<QPlainTextEdit> MainWindow::messageLogWidget = nullptr;

MainWindow::MainWindow(ResourceManager* resourceMgr, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , resourceManager(resourceMgr)          //Assign from main
{
    ui->setupUi(this);
    //MainWindow size:
    resize(1300, 850);

    setWindowTitle("INNgine");  //Main app title

    mVulkanWindow = new Renderer();
    mVulkanWindow->setTitle("Renderer");

    //Have to set the size of the Vulkan window here, otherwise it can not set up the swapchain correctly
    mVulkanWindow->setWidth(1100);
    mVulkanWindow->setHeight(700);
    mVulkanWindow->initVulkan();

    // Wrap VulkanRenderer (QWindow) into a QWidget
    QWidget* vulkanWidget = QWidget::createWindowContainer(mVulkanWindow, this);
    vulkanWidget->setMinimumSize(1100, 700);

    ui->VulkanLayout->addWidget(vulkanWidget);

    //sets the keyboard input focus to the MainWindow when program starts
    this->setFocus();
    vulkanWidget->setFocusPolicy(Qt::NoFocus);



    /*
     * Logger Implementation in MainWindow
     */
    QDockWidget* logDock = new QDockWidget("Logger", this);
    logDock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);

    // Creating the Log Widget
    messageLogWidget = new QPlainTextEdit(logDock);
    messageLogWidget->setReadOnly(true);
    logDock->setWidget(messageLogWidget);
    addDockWidget(Qt::BottomDockWidgetArea, logDock);
    qInstallMessageHandler(MainWindow::messageHandler);

    //Menu
    logDock->setObjectName("LoggerDock");
    ui->actionLogger->setCheckable(true);
    ui->actionLogger->setChecked(true); // visible by default

    connect(ui->actionLogger, &QAction::toggled, logDock, &QDockWidget::setVisible);
    connect(logDock, &QDockWidget::visibilityChanged, ui->actionLogger, &QAction::setChecked);

    statusBar()->showMessage(" put something cool here! ");
}

MainWindow::~MainWindow()
{
    if(mVulkanWindow)
    {
        delete mVulkanWindow;
        mVulkanWindow = nullptr;
    }
    delete ui;
}

void MainWindow::start()
{
    qDebug("Start is called");
    mVulkanWindow->requestUpdate();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        delete mVulkanWindow;
        mVulkanWindow = nullptr;
        close(); // Example: close window on ESC
    }
    if (event->key() == Qt::Key_Space) {
        start();
    }
    if (event->key() == Qt::Key_W) {
        //messageLogWidget->appendPlainText("Marvin Marvin Marvin");
        qWarning("MARVIN");
    }
    if (event->key() == Qt::Key_A) {
        //messageLogWidget->appendPlainText("Erik Er Best");

    }
}


void MainWindow::on_action_Quit_triggered()
{
    delete mVulkanWindow;
    mVulkanWindow = nullptr;
    close();
}

void MainWindow::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (!messageLogWidget)
        return;

    QString level;
    QString color;

    switch(type)
    {
    case QtDebugMsg:    level = "Debug";    color = "white";    break;
    case QtInfoMsg:     level = "Info";     color = "blue";     break;
    case QtWarningMsg:  level = "Warning";  color = "orange";   break;
    case QtCriticalMsg: level = "Critical"; color = "red";      break;
    case QtFatalMsg:    level = "Fatal";    color = "darkred";  break;
    }

    // Timestamp
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");

    // Gives u which line and file the issue is within
    QString location;
    if (context.file && context.line > 0)
        location = QString("%1:%2").arg(context.file).arg(context.line);

    // Fow the format of the final message while look like
    QString formattedMsg = QString("<span style=\"color:%1;\">[%2] [%3] [%4] %5</span>")
                               .arg(color, timestamp, level, location.isEmpty() ? "unknown" : location, msg.toHtmlEscaped());

    messageLogWidget->appendHtml(formattedMsg);

    if (type == QtFatalMsg) {
        abort();
    }
}





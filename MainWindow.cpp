#include "MainWindow.h"
#include "resourcemanager.h"
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
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <qPushButton>


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

    //===============TABS==================
    //Create a vertical splitter
    QSplitter* splitter = new QSplitter(Qt::Vertical, this);
    splitter->setChildrenCollapsible(false);

    //Put Vulkan window on top of the splitter
    splitter->addWidget(vulkanWidget);

    //Create tab widget
    QTabWidget* tabWidget = new QTabWidget(splitter);
    tabWidget->setObjectName("MainTabWidget");

    //Tab 1 with logger
    QWidget* loggerTab = new QWidget(tabWidget);
    QVBoxLayout* loggerLayout = new QVBoxLayout(loggerTab);
    messageLogWidget = new QPlainTextEdit(loggerTab);
    messageLogWidget->setReadOnly(true);
    loggerLayout->setContentsMargins(4,4,4,4);
    loggerLayout->addWidget(messageLogWidget);
    loggerTab->setLayout(loggerLayout);
    tabWidget->addTab(loggerTab, tr("Logger"));

    //Tab 2 (empty)
    QWidget* secondTab = new QWidget(tabWidget);
    tabWidget->addTab(secondTab, tr("Second Tab"));

    //Add splitter to bottom
    splitter->addWidget(tabWidget);

    //================Right side buttons==============
    //Right side UI
    QWidget* rightPanel = new QWidget(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    //Create buttons
    QPushButton* button1 = new QPushButton("Square", rightPanel);
    QPushButton* button2 = new QPushButton("Ball", rightPanel);
    QPushButton* button3 = new QPushButton("Lizard", rightPanel);

    //Add button to layout
    rightLayout->addWidget(button1);
    rightLayout->addWidget(button2);
    rightLayout->addWidget(button3);

    //Connect buttons
    connect(button1, &QPushButton::clicked, this, &MainWindow::onSquareClicked);
    connect(button2, &QPushButton::clicked, this, &MainWindow::onBallClicked);
    connect(button3, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    //Add strech
    rightLayout->addStretch(1);

    //Put everything into a horizontal layout
    QHBoxLayout* mainLayout = new QHBoxLayout;;
    mainLayout->addWidget(splitter, 4);
    mainLayout->addWidget(rightPanel, 1);

    //Central widget
    QWidget* central = new QWidget(this);
    central->setLayout(mainLayout);
    setCentralWidget(central);

    //Install logger
    qInstallMessageHandler(MainWindow::messageHandler);

    //============Bottom text======================
    statusBar()->showMessage("Don't be afraid of slow progress, be afraid of standing still.");

    //Background musick (not annoying)
    resourceManager->toggleBackgroundMusic();
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
        qWarning("MARVIN");
    }
    if (event->key() == Qt::Key_A) {
        resourceManager->clickSound();
    }
    if (event->key() == Qt::Key_Q) {
        resourceManager->toggleBackgroundMusic();
    }
}

void MainWindow::onSquareClicked()
{
    qInfo() << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHHHHHHHH!!";
}
void MainWindow::onBallClicked()
{
    qInfo() << "Ball";
}
void MainWindow::onButtonClicked()
{
    qInfo() << "Lizzard";
    resourceManager->lizardSound();
}


void MainWindow::on_action_Quit_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quit INNgine", "Are you sure you want to quit? ", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        delete mVulkanWindow;
        mVulkanWindow = nullptr;
        close();
    }
}


void MainWindow::on_action_Open_triggered()
{
    //Gets username from PC
    QString username = QDir::home().dirName();
    QString repeate;
    for (int i = 0; i < 280; i++)
    {
        repeate += username + "! ";
    }
    QMessageBox::StandardButton creepy;
    creepy = QMessageBox::warning(this,"Why would you do this? ", repeate,QMessageBox::No);
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







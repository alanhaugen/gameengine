#include "Editor/MainWindow.h"
#include "Core/Utilities.h"
#include <QApplication>
#include <QSplashScreen>
#include <QPlainTextEdit>
#include <QVulkanInstance>
#include <QLibraryInfo>
#include <QLoggingCategory>
#include <QPointer>

Q_LOGGING_CATEGORY(lcVk, "qt.vulkan")

QPointer<QPlainTextEdit> messageLogWidget;
static QtMessageHandler oldMessageHandler{ nullptr };

//Logger system from Qt. Nice to print out messages directly to our program
static void messageHandler(QtMsgType msgType, const QMessageLogContext &logContext, const QString &text)
{
    if (!messageLogWidget.isNull())
        messageLogWidget->appendPlainText(text);
    if (oldMessageHandler)
        oldMessageHandler(msgType, logContext, text);
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Splash screen
    QSplashScreen *mSplash = new QSplashScreen;
    mSplash->setPixmap(QPixmap(QString::fromStdString(PATH) + "Assets/Engine/INNgine_splash.png"));
    mSplash->show();

    //Logger setup
    messageLogWidget = new QPlainTextEdit(QLatin1String(QLibraryInfo::build()) + QLatin1Char('\n'));
    messageLogWidget->setReadOnly(true);
    oldMessageHandler = qInstallMessageHandler(messageHandler);
    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

    MainWindow mainWindow = MainWindow(nullptr);
    mainWindow.move(200, 100);
    mainWindow.show();
    mainWindow.start();

    mSplash->hide();

    //app.exec() runs the rest of the program
    return app.exec();
}

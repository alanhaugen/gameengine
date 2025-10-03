#include "MainWindow.h"
#include <QApplication>
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

    QApplication a(argc, argv);

    //Logger setup
    //messageLogWidget = new QPlainTextEdit(QLatin1String(QLibraryInfo::build()) + QLatin1Char('\n'));
    //messageLogWidget->setReadOnly(true);
    oldMessageHandler = qInstallMessageHandler(messageHandler);
    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));


    MainWindow w;
    w.move(200, 100);
    w.show();
    w.start();
    return a.exec();
}

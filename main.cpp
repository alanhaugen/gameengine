#include "MainWindow.h"
#include "Utilities.h"
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

    QSplashScreen *mSplash = new QSplashScreen;
    mSplash->setPixmap(QPixmap(QString::fromStdString(PATH) + "Assets/Engine/INNgine_splash.png")); // splash picture
    mSplash->show();

    //Logger setup
    messageLogWidget = new QPlainTextEdit(QLatin1String(QLibraryInfo::build()) + QLatin1Char('\n'));
    messageLogWidget->setReadOnly(true);
    oldMessageHandler = qInstallMessageHandler(messageHandler);
    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

    std::vector<gea::Mesh> mMeshes;
    std::vector<gea::Texture> mTextures;
    std::vector<gea::RenderComponent> mRenderComponents;
    std::vector<gea::RenderComponent> mStaticRenderComponents;
    //this is done for testing sake. in the real ecs there would only be one vector of transform components
    std::vector<gea::Transform> mTransformComponents;
    std::vector<gea::Transform> mStaticTransformComponents;

    mMeshes.push_back(gea::Mesh());
    mTextures.push_back(gea::Texture());

    mRenderComponents.push_back(gea::RenderComponent(0, 0, 0));
    gea::Transform t1 = gea::Transform(0);
    t1.mPosition = glm::vec3(1.0f, 0.0f, 0.0f);
    mTransformComponents.push_back(t1);

    mStaticRenderComponents.push_back(gea::RenderComponent(0, 0, 1));
    gea::Transform t2 = gea::Transform(1);
    t2.mPosition = glm::vec3(-1.0f, 0.0f, 0.0f);
    mStaticTransformComponents.push_back(t2);

    MainWindow mainWindow = MainWindow(nullptr, mStaticRenderComponents, mStaticTransformComponents, mMeshes, mTextures);

    mainWindow.move(200, 100);
    mainWindow.show();
    mainWindow.start();
    mainWindow.UpdateRenderSystem(mRenderComponents, mTransformComponents);

    mSplash->hide();

    //app.exec() runs the rest of the program
    return app.exec();
}

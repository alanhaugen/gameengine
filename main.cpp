#include "MainWindow.h"
#include "Utilities.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *mSplash = new QSplashScreen;
    mSplash->setPixmap(QPixmap(QString::fromStdString(PATH) + "Assets/Engine/INNgine_splash.png")); // splash picture
    mSplash->show();

    std::vector<gea::Mesh> mMeshes;
    std::vector<gea::Texture> mTextures;
    std::vector<gea::RenderComponent> mRenderComponents;
    std::vector<gea::RenderComponent> mStaticRenderComponents;
    //this is done for testing sake. in the real ecs there would only be one vector of transform components
    std::vector<gea::TransformComponent> mTransformComponents;
    std::vector<gea::TransformComponent> mStaticTransformComponents;

    mMeshes.push_back(gea::Mesh());
    mTextures.push_back(gea::Texture());

    mRenderComponents.push_back(gea::RenderComponent(0, 0, 0));
    gea::TransformComponent t1 = gea::TransformComponent(0);
    t1.position = glm::vec3(1.0f, 0.0f, 0.0f);
    mTransformComponents.push_back(t1);

    mStaticRenderComponents.push_back(gea::RenderComponent(0, 0, 1));
    gea::TransformComponent t2 = gea::TransformComponent(1);
    t2.position = glm::vec3(-1.0f, 0.0f, 0.0f);
    mStaticTransformComponents.push_back(t2);

    MainWindow w = MainWindow(nullptr, mStaticRenderComponents, mStaticTransformComponents, mMeshes, mTextures);
    w.move(200, 100);
    w.show();
    w.start();

    mSplash->hide();

	w.UpdateRenderSystem(mRenderComponents, mTransformComponents);
    return a.exec();
}
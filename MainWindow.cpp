#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Renderer.h"
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include "displayWidget.cpp"


MainWindow::MainWindow(QWidget* parent,
    std::vector<gea::RenderComponent> staticComponents, std::vector<gea::TransformComponent> staticTransformComponents,
    std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //MainWindow size:
    resize(1300, 850);

    setWindowTitle("INNgine");  //Main app title

    mVulkanWindow = new Renderer();
    mVulkanWindow->setTitle("Renderer");    //Render window title

    //Have to set the size of the Vulkan window here, otherwise it can not set up the swapchain correctly
    mVulkanWindow->setWidth(1100);
    mVulkanWindow->setHeight(700);

	SetupRenderSystem(staticComponents, staticTransformComponents, meshes, textures);
    //mVulkanWindow->initVulkan();

    // Wrap VulkanRenderer (QWindow) into a QWidget
    QWidget* mVulkanWidget = QWidget::createWindowContainer(mVulkanWindow, this);
    mVulkanWidget->setMinimumSize(1100, 700);

    // Put the mVulkanWidget into the VulkanLayout spot, made in the MainWindow.ui file
    ui->VulkanLayout->addWidget(mVulkanWidget);

    //sets the keyboard input focus to the MainWindow when program starts
    this->setFocus();

    statusBar()->showMessage(" put something cool here! ");
    //-------------------------------------------file system widget-------------------------------------------------------
    // need to get asset manager from renderer itself, since manager that holds assets is created there
    //AssetManager<ObjAsset>* objManager=new AssetManager<ObjAsset>();

    if (mVulkanWindow->filesImported==true){
        //FilesWindow<ObjAsset> filesWidget(mVulkanWindow->objManager);
        filesWidget= new FilesWindow(mVulkanWindow->objManager);
    }

    //////////////model view test/////////
    // QWidget window;
    // QHBoxLayout* layout=new QHBoxLayout(&*vulkanWidget);

    // QFileSystemModel* model= new QFileSystemModel;
    // model->setRootPath(QDir::homePath());
    // model ->setNameFilters({"*.obj","*.png","*.jpg"});
    // model->setNameFilterDisables(false);
    // QModelIndex tree_root= model->index(QDir::homePath());

    // QTreeView* tree=new QTreeView;
    // tree->setModel(model);
    // tree->setRootIndex(tree_root);

    // //preview

    // displayWidget* displayIcons= new displayWidget;
    // //

    // layout->addWidget(tree);
    // layout->addWidget(displayIcons);

    // QObject::connect(tree,&QTreeView::clicked,[&](const QModelIndex &index) {
    //     QString path=model->filePath(index);
    //     displayIcons->previewFile(path);
    // });
    // window.resize(1000,200);
    // window.show();
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

void MainWindow::SetupRenderSystem(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::TransformComponent> staticTransformComponents, std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures)
{
    mRenderSystem = new gea::RenderSystem(mVulkanWindow);
    mRenderSystem->Initialize(staticComponents, staticTransformComponents, meshes, textures);
}

void MainWindow::UpdateRenderSystem(std::vector<gea::RenderComponent> dynamicComponents, std::vector<gea::TransformComponent> dynamicTransformComponents)
{
	mRenderSystem->Update(dynamicComponents, dynamicTransformComponents);
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

}

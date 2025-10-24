#include "FilesWindow.h"

#include <QString>
#include <QDebug>

//"If parent is nullptr, the new widget becomes a window. If parent is another widget, this widget becomes a child window inside parent.

FilesWindow::FilesWindow(AssetManager<gea::Mesh*>* manager,QWidget* parent)
{
    setWindowTitle("Files");
    setMinimumHeight(100);
    setMinimumWidth(500);
    setAcceptDrops(true);

    mAssetsPtr= manager;

    mCentralWidget=new QWidget(this);  //main parent, which is a docker window
    mMainLayout=new QVBoxLayout(mCentralWidget); //central widget (parent) contains main layout(child)

    //main layout contains: a status bar and a scroller (with its children)
    mScrolling=new QScrollArea(mCentralWidget); //main layout holds the scroller, but layouts cant be parents, so the central widget is
    mScrollingWidget=new QWidget(mScrolling); //scroller (parent) has scrolling widget(child)
    mScrollingLayout=new QVBoxLayout(mScrollingWidget); //scrolling widget (parent) has layout (child) for future buttons
    mScrollingWidget->setLayout(mScrollingLayout);
    mScrolling->setWidget(mScrollingWidget); //scrollers content is scrolling widget with the future buttons
    mScrolling->setWidgetResizable(true);

    mMainLayout->addWidget(mScrolling); //main layout has scroller

    mStatus=new QStatusBar(mCentralWidget);
    mStatus->showMessage(" Drop new files in this window ");

    mMainLayout->addWidget(mStatus); //main layout has status

    mCentralWidget->setLayout(mMainLayout);
    setWidget(mCentralWidget); //docker window content is the central widget parent that contains all the children: main layout->scroller, -->status, etc

    createButtons(mAssetsPtr);
    show();
}

void FilesWindow::mHandleButton(int index)
{
    //QString new_text=QString::number(assets_ptr->int_assets[index]);
    QString new_text="test";
    // change the text
    mDisplayAssets[index]->setText(new_text);
    // resize button
    mDisplayAssets[index]->resize(100,100);
}

void FilesWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }
}

void FilesWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls=event->mimeData()->urls();
    for(const QUrl &it: urls){
        QString path=it.toLocalFile();
        QString name=QFileInfo(path).baseName();
        //looking up an element in QSet is faster than iterating over a stack
        if(path.endsWith(".obj")&& !mAssetsPtr->mFilesNamesSet.contains(name)) //file has not been imported allready
        {
            mAssetsPtr->mFilesNamesSet.insert(name);
            int i=mAssetsPtr->mFilesNamesSet.size();
            gea::Mesh* newMesh=new gea::Mesh(path);
            mAssetsPtr->addNewAsset(newMesh);
            QPushButton* new_button=new QPushButton(name, mScrollingWidget);
            mDisplayAssets.push_back(new_button);
            mScrollingLayout->addWidget(new_button);
            //displayAssets.back()->setGeometry(QRect(QPoint(200*i, 100), QSize(200, 50)));

            //connect buttons to the objects
            connect(mDisplayAssets.back(), &QPushButton::released, this,[this, i]{ mHandleButton(i-1); });
            mStatus->showMessage(" Drop new files in this window ");
        }
        else
            mStatus->showMessage(" File is already imported. ");
    }
}

// void FilesWindow::dragMoveEvent(QDragMoveEvent *event)
// {

// }

// void FilesWindow::mousePressEvent(QMouseEvent *event)
// {

// }

void FilesWindow::createButtons(AssetManager<gea::Mesh*> *assets_)
{
    for(int i=0; i<assets_->mAssets.size(); i++){
        //create button
        //should never run this, but in case we have more paths than objects
        if(assets_->mFilesNamesSet.size()!=assets_->mAssets.size() || assets_->mFilesNamesSet.size()<1){
            //assets_ptr->filesNamesSet.resize(assets_ptr->assets.size());
            qDebug()<<"names "<<assets_->mFilesNamesSet.size()
                     <<" assets: "<<assets_->mAssets.size();
            break;
        }

        QString name_=QFileInfo(assets_->mFilesNamesStack[i]).baseName();
        QPushButton* new_button=new QPushButton(name_, mScrollingWidget);
        mDisplayAssets.push_back(new_button);
        mScrollingLayout->addWidget(new_button);
        //set size
        //displayAssets[i]->setGeometry(QRect(QPoint(200*i, 100), QSize(200, 50)));
        //connect buttons to the objects
        connect(mDisplayAssets[i], &QPushButton::released, this,[this, i]{ mHandleButton(i); });
    }
}

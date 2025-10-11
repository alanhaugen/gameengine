#include "FilesWindow.h"

#include <QString>
#include <QDebug>

FilesWindow::FilesWindow(AssetManager<ObjAsset>* manager)
{
    setWindowTitle("Files");
    setMinimumHeight(100);
    setMinimumWidth(500);
    setAcceptDrops(true);

    mAssetsPtr= manager;

    mMainLayout=new QVBoxLayout(this);

    //window has 2 children: a status bar and a scroller
    mScrolling=new QScrollArea(this);
    mScrollingLayout=new QVBoxLayout(mScrollingWidget);
    mScrollingWidget->setLayout(mScrollingLayout);
    mScrolling->setWidget(mScrollingWidget);
    mScrolling->setWidgetResizable(true);
    //scrolling->setGeometry(0,0,width(), height());
    mMainLayout->addWidget(mScrolling);

    mStatus=new QStatusBar(this);
    mStatus->showMessage(" Drop new files in this window ");
    mMainLayout->addWidget(mStatus);
    //mainLayout->setGeometry(0,0,width(), height());
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
            //importObjects(path);
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

void FilesWindow::createButtons(AssetManager<ObjAsset> *assets_)
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

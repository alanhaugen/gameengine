#include "FilesWindow.h"

#include <QString>
#include <QDebug>

FilesWindow::FilesWindow(AssetManager<ObjAsset>* manager)
{
    setWindowTitle("Files");
    setMinimumHeight(100);
    setMinimumWidth(500);
    setAcceptDrops(true);

    assets_ptr= manager;

    mainLayout=new QVBoxLayout(this);

    //window has 2 children: a status bar and a scroller
    scrolling=new QScrollArea(this);
    scrollingLayout=new QVBoxLayout(scrollingWidget);
    scrollingWidget->setLayout(scrollingLayout);
    scrolling->setWidget(scrollingWidget);
    scrolling->setWidgetResizable(true);
    //scrolling->setGeometry(0,0,width(), height());
    mainLayout->addWidget(scrolling);

    status=new QStatusBar(this);
    status->showMessage(" Drop new files in this window ");
    mainLayout->addWidget(status);
    //mainLayout->setGeometry(0,0,width(), height());
    createButtons(assets_ptr);
    show();
}

void FilesWindow::handleButton(int index)
{
    //QString new_text=QString::number(assets_ptr->int_assets[index]);
    QString new_text="test";
    // change the text
    displayAssets[index]->setText(new_text);
    // resize button
    displayAssets[index]->resize(100,100);
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
        if(path.endsWith(".obj")&& !assets_ptr->filesNamesSet.contains(name)){ //file has not been imported allready
            assets_ptr->filesNamesSet.insert(name);
            int i=assets_ptr->filesNamesSet.size();
            //importObjects(path);
            QPushButton* new_button=new QPushButton(name, scrollingWidget);
            displayAssets.push_back(new_button);
            scrollingLayout->addWidget(new_button);
            //displayAssets.back()->setGeometry(QRect(QPoint(200*i, 100), QSize(200, 50)));

            //connect buttons to the objects
            connect(displayAssets.back(), &QPushButton::released, this,[this, i]{
                handleButton(i-1);
            });
            status->showMessage(" Drop new files in this window ");
        }
        else{
            status->showMessage(" File is already imported. ");
        }
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
    for(int i=0; i<assets_->assets.size(); i++){
        //create button
        //should never run this, but in case we have more paths than objects
        if(assets_->filesNamesSet.size()!=assets_->assets.size() || assets_->filesNamesSet.size()<1){
            //assets_ptr->filesNamesSet.resize(assets_ptr->assets.size());
            qDebug()<<"names "<<assets_->filesNamesSet.size()
                     <<" assets: "<<assets_->assets.size();
            break;
        }

        QString name_=QFileInfo(assets_->filesNamesStack[i]).baseName();
        QPushButton* new_button=new QPushButton(name_, scrollingWidget);
        displayAssets.push_back(new_button);
        scrollingLayout->addWidget(new_button);
        //set size
        //displayAssets[i]->setGeometry(QRect(QPoint(200*i, 100), QSize(200, 50)));
        //connect buttons to the objects
        connect(displayAssets[i], &QPushButton::released, this,[this, i]{
            handleButton(i);
        });
    }
}

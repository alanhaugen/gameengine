#include "fileswindow.h"

#include <QString>
#include <QDebug>

FilesWindow::FilesWindow(AssetManager<ObjAsset>* manager) {
    setWindowTitle("Files");
    setMinimumHeight(100);
    setMinimumWidth(1000);
    setAcceptDrops(true);

    assets_ptr= manager;
    createButtons(assets_ptr);
    show();

}


void FilesWindow::handleButton(int index) //
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
        if(path.endsWith(".obj")){
            assets_ptr->filesNamesStack.push_back(path);
            int i=assets_ptr->filesNamesStack.size();
            //importObjects(path);
            displayAssets.push_back(new QPushButton(path, this));
            displayAssets.back()->setGeometry(QRect(QPoint(200*i, 100), QSize(200, 50)));
            //connect buttons to the objects
            //connect(displayAssets.back(), &QPushButton::released, this,[this, i]{
            //handleButton(i);};
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
        if(assets_->filesNamesStack.size()!=assets_->assets.size() || assets_->filesNamesStack.size()<1){
            //assets_ptr->filesNamesStack.resize(assets_ptr->assets.size());
            qDebug()<<"names "<<assets_->filesNamesStack.size()
                     <<" assets: "<<assets_->assets.size();
            break;
        }

        QString name_=assets_->filesNamesStack[i];
        displayAssets.push_back(new QPushButton(name_, this));
        //set size
        displayAssets[i]->setGeometry(QRect(QPoint(200*i, 100), QSize(200, 50)));
        //connect buttons to the objects
        connect(displayAssets[i], &QPushButton::released, this,[this, i]{
            handleButton(i);
        });
    }

}

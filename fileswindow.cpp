#include "fileswindow.h"

#include <QString>
#include <QDebug>

FilesWindow::FilesWindow(AssetManager<ObjAsset>* manager) {
    setWindowTitle("Files");
    setMinimumHeight(100);
    setMinimumWidth(1000);


    assets_ptr= manager;
    for(int i=0; i<assets_ptr->assets.size(); i++){
        //create button
        //should never run this, but in case we have more paths than objects
        if(assets_ptr->filesNamesStack.size()!=assets_ptr->assets.size() || assets_ptr->filesNamesStack.size()<1){
            //assets_ptr->filesNamesStack.resize(assets_ptr->assets.size());
            qDebug()<<"names "<<assets_ptr->filesNamesStack.size()
                     <<" assets: "<<assets_ptr->assets.size();
            break;
        }

        QString name_=assets_ptr->filesNamesStack[i];
        displayAssets.push_back(new QPushButton(name_, this));
        //set size
        displayAssets[i]->setGeometry(QRect(QPoint(200*i, 100), QSize(200, 50)));
        //connect buttons to the objects
        connect(displayAssets[i], &QPushButton::released, this,[this, i]{
            handleButton(i);
        });
    }

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

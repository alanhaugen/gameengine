#include "fileswindow.h"

#include <QString>
FilesWindow::FilesWindow() {
    setWindowTitle("Files");
    setMinimumHeight(100);
    setMinimumWidth(1000);


    assets_ptr= new AssetManager<int>({1,2,3});
    for(int i=0; i<assets_ptr->int_assets.size(); i++){
        //create button
        displayAssets.push_back(new QPushButton("test click", this));
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
    QString new_text=QString::number(assets_ptr->int_assets[index]);
    // change the text
    displayAssets[index]->setText(new_text);
    // resize button
    displayAssets[index]->resize(100,100);
}

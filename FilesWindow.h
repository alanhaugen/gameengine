#ifndef FILESWINDOW_H
#define FILESWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "AssetManager.h"
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QFrame>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStatusBar>

 //template <typename T>
class FilesWindow: public QFrame //for drag and drop
{
public:
    FilesWindow(AssetManager<ObjAsset>* manager); // T
    std::vector<QPushButton*> displayAssets; //based on assets input vector size
    AssetManager<ObjAsset>* assets_ptr{nullptr};
    QScrollArea* scrolling;
    QWidget* scrollingWidget=new QWidget();
    QVBoxLayout* scrollingLayout;
    QVBoxLayout* mainLayout;
    QStatusBar* status;
    void handleButton(int index);

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    // void dragMoveEvent(QDragMoveEvent *event) override;
    // void mousePressEvent(QMouseEvent *event) override;

    void createButtons(AssetManager<ObjAsset>* assets_);

};

#endif // FILESWINDOW_H

#ifndef FILESWINDOW_H
#define FILESWINDOW_H
#include "QWidget"
#include "QPushButton"
#include "assetmanager.h"
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QFrame>
 //template <typename T>
class FilesWindow: public QFrame
{
public:
    FilesWindow(AssetManager<ObjAsset>* manager); // T
    std::vector<QPushButton*> displayAssets; //based on assets input vector size
    //AssetManager<int>* assets_ptr{nullptr};
    AssetManager<ObjAsset>* assets_ptr{nullptr};
    //QPushButton* test{nullptr};
    void handleButton(int index);

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    // void dragMoveEvent(QDragMoveEvent *event) override;
    // void mousePressEvent(QMouseEvent *event) override;

    void createButtons(AssetManager<ObjAsset>* assets_);
};

#endif // FILESWINDOW_H

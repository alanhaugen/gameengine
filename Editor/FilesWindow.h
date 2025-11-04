#ifndef FILESWINDOW_H
#define FILESWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "AssetManager/AssetManager.h"
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QDockWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStatusBar>

 //template <typename T>
class FilesWindow: public QDockWidget //for drag and drop
{
public:
    FilesWindow(AssetManager<ObjAsset>* manager); // T

    std::vector<QPushButton*> mDisplayAssets; //based on assets input vector size
    AssetManager<ObjAsset>* mAssetsPtr{nullptr};
    QWidget* mCentralWidget{nullptr};
    QScrollArea* mScrolling{nullptr};
    QWidget* mScrollingWidget = new QWidget();
    QVBoxLayout* mScrollingLayout{nullptr};
    QVBoxLayout* mMainLayout{nullptr};
    QStatusBar* mStatus{nullptr};
    void mHandleButton(int index);

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    // void dragMoveEvent(QDragMoveEvent *event) override;
    // void mousePressEvent(QMouseEvent *event) override;

    void createButtons(AssetManager<ObjAsset>* assets_);
};

#endif // FILESWINDOW_H

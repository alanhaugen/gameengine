#ifndef FILESWINDOW_H
#define FILESWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "AssetManager/AssetManager.h"
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QFrame>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStatusBar>
#include <QDockWidget>
#include "AssetManager/Mesh.h"
#include "AssetManager/Texture.h"
#include "AssetManager/Sound.h"
 //template <typename T>
class FilesWindow: public QDockWidget // public QFrame for drag and drop
{


public:
    FilesWindow(AssetManager<gea::Mesh>* manager, QWidget* parent=nullptr); // T

    std::vector<QPushButton*> mDisplayAssets; //based on assets input vector size
    AssetManager<gea::Mesh>* mAssetsPtr{nullptr};
    QWidget* mCentralWidget{nullptr};
    QScrollArea* mScrolling{nullptr};
    QWidget* mScrollingWidget{nullptr};
    QVBoxLayout* mScrollingLayout{nullptr};
    QVBoxLayout* mMainLayout{nullptr};
    QStatusBar* mStatus{nullptr};
    void mHandleButton(int index);

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    // void dragMoveEvent(QDragMoveEvent *event) override;
    // void mousePressEvent(QMouseEvent *event) override;

    void createButtons(AssetManager<gea::Mesh>* assets_);
};

#endif // FILESWINDOW_H

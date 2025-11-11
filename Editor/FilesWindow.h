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
#include <type_traits>
template <typename T>
class FilesWindow: public QDockWidget // public QFrame for drag and drop
{
public:
    FilesWindow(AssetManager<T>* manager, QWidget* parent=nullptr); // T

    std::vector<QPushButton*> mDisplayAssets; //based on assets input vector size
    AssetManager<T>* mAssetsPtr{nullptr};
    QWidget* mCentralWidget{nullptr};
    QScrollArea* mScrolling{nullptr};
    QWidget* mScrollingWidget{nullptr};
    QVBoxLayout* mScrollingLayout{nullptr};
    QVBoxLayout* mMainLayout{nullptr};
    QStatusBar* mStatus{nullptr};
    void mHandleButton(int index);
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void createButtons(AssetManager<T>* assets_);

    //------------------mesh specific-----------------------------------------
    // FilesWindow(AssetManager<gea::Mesh>* manager, QWidget* parent=nullptr); // T

    // std::vector<QPushButton*> mDisplayAssets; //based on assets input vector size
    // AssetManager<gea::Mesh>* mAssetsPtr{nullptr};
    // QWidget* mCentralWidget{nullptr};
    // QScrollArea* mScrolling{nullptr};
    // QWidget* mScrollingWidget{nullptr};
    // QVBoxLayout* mScrollingLayout{nullptr};
    // QVBoxLayout* mMainLayout{nullptr};
    // QStatusBar* mStatus{nullptr};
    // void mHandleButton(int index);

    // void dragEnterEvent(QDragEnterEvent* event) override;
    // void dropEvent(QDropEvent* event) override;
    // // void dragMoveEvent(QDragMoveEvent *event) override;
    // // void mousePressEvent(QMouseEvent *event) override;

    // void createButtons(AssetManager<gea::Mesh>* assets_);
};
template<typename T>
FilesWindow<T>::FilesWindow(AssetManager<T> *manager, QWidget *parent)
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

    createButtons(manager);
    show();

}

template<typename T>
void FilesWindow<T>::mHandleButton(int index)
{
    //QString new_text=QString::number(assets_ptr->int_assets[index]);
    QString new_text="test";
    // change the text
    mDisplayAssets[index]->setText(new_text);
    // resize button
    //mDisplayAssets[index]->resize(100,100);
}

template<typename T>
void FilesWindow<T>::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }
}

template<typename T>
void FilesWindow<T>::dropEvent(QDropEvent *event)
{
    //can import multiple files with list
    QList<QUrl> urls=event->mimeData()->urls(); //mimedata is the draggable object
    for(const QUrl &it: urls){
        QString path=it.toLocalFile();
        QString name=QFileInfo(path).baseName();
        //looking up an element in QSet is faster than iterating over a stack
        //------------------------add mesh-------------------
        if constexpr (std::is_same<T,gea::Mesh>::value){ //if window is mesh window
            if (path.endsWith(".obj")){
                if(!mAssetsPtr->mFilesNamesSet.contains(name)){ //file has not been imported allready
                int value= mAssetsPtr->mFilesNamesSet.size();
                mAssetsPtr->mFilesNamesSet.insert(name,value);
                mAssetsPtr->mFilesNamesStack.push_back(path);
                int i=mAssetsPtr->mFilesNamesSet.size();
                //gea::Mesh* newMesh=new gea::Mesh(path);
                T* newMesh=new T(path);
                mAssetsPtr->addNewAsset(newMesh); //actually import a new object with its vertices&indices
                QPushButton* new_button=new QPushButton(name, mScrollingWidget);
                mDisplayAssets.push_back(new_button);
                mScrollingLayout->addWidget(new_button);

                //connect buttons to the objects
                connect(mDisplayAssets.back(), &QPushButton::released, this,[this, i]{ mHandleButton(i-1); });
                mStatus->showMessage(" Drop new files in this window ");
                }
                else
                    mStatus->showMessage(" File is already imported. ");
            }
            else
                mStatus->showMessage(" Incorrect file type. ");
        }

        //-----------add texture----------------------
        else if constexpr (std::is_same<T,gea::Texture>::value){ //if window is textures window

            if(path.endsWith(".png") || path.endsWith(".jpg")){ //if correct type,check if already has been imported
                if(!mAssetsPtr->mFilesNamesSet.contains(name)){
                    int value= mAssetsPtr->mFilesNamesSet.size();
                    mAssetsPtr->mFilesNamesSet.insert(name,value);
                    int i=mAssetsPtr->mFilesNamesSet.size();
                    //gea::Texture* newTexture=new gea::Texture(path);
                    T* newTexture=new T(path);
                    mAssetsPtr->addNewAsset(newTexture);//actually importing new texture
                    QPushButton* new_button=new QPushButton(name, mScrollingWidget);
                    mDisplayAssets.push_back(new_button);
                    mScrollingLayout->addWidget(new_button);

                    //connect buttons to the objects
                    connect(mDisplayAssets.back(), &QPushButton::released, this,[this, i]{ mHandleButton(i-1); });
                    mStatus->showMessage(" Drop new files in this window ");
                }
                else
                    mStatus->showMessage(" File is already imported. ");
            }
            else
                mStatus->showMessage(" Incorrect file type. ");
        }
        //-----------------------add sound---------------
        //TODO
        else{
            qDebug()<<"weird stuff-------------------------------------------------";
        }
    }
}

template<typename T>
void FilesWindow<T>::createButtons(AssetManager<T> *assets_)
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

#endif // FILESWINDOW_H

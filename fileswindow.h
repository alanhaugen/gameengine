#ifndef FILESWINDOW_H
#define FILESWINDOW_H
#include "QWidget"
#include "QPushButton"
#include "assetmanager.h"
 //template <typename T>
class FilesWindow: public QWidget
{
public:
    FilesWindow(AssetManager<ObjAsset>* manager);
    std::vector<QPushButton*> displayAssets; //based on assets input vector size
    //AssetManager<int>* assets_ptr{nullptr};
    AssetManager<ObjAsset>* assets_ptr{nullptr};
    //QPushButton* test{nullptr};
    void handleButton(int index);
};

#endif // FILESWINDOW_H

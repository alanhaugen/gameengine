#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <vector>
#include <QString>
#include <QSet>
#include <QStack>
#include "QDirIterator"
#include "AssetManager/Mesh.h"
#include "AssetManager/Texture.h"
//#include "AssetManager/Sound.h"
#include "WavfileReader.h"
#include <type_traits>
template <typename T>
class AssetManager{
public:
    AssetManager<T>(){AssetManager<T>::importObjects();};

    std::vector<T*> mAssets;
    //std::vector<gea::Texture*> mTextures;
    //std::vector<wave_t> mSounds;

    QSet<QString> mFilesNamesSet;
    QStack<QString> mFilesNamesStack;

    // void addNewMesh(gea::Mesh* newMesh);
    void addNewAsset(T* newAsset);

    void importTextures();
    void importSounds();
    void importObjects();

    void importAssets(QString folder, QString object_type, QString object_type2);


    // void deleteAsset(T asset);
};

template<typename T>
void AssetManager<T>::importAssets(QString folder, QString object_type, QString object_type2)
{
    QDirIterator it(QString(PATH.c_str()) + "Assets/"+folder+"/",QStringList()<<object_type, QDir::NoFilter,QDirIterator::Subdirectories );
    while(it.hasNext())
    {
        QString path=it.next();
        QFileInfo fileInfo(path);
        QString name=fileInfo.baseName();
        //qDebug()<<fileInfo.filePath()<<" "<<fileInfo.absoluteFilePath()<<"\n";
        mFilesNamesSet.insert(name); //for future check if mesh has been imported in the engine before
        mFilesNamesStack.push_back(path); //for loading in all meshes when we start engine
    }

    //thought this is needed because we probably dont want to limit to either .jpg or .png, so we read both
    //maybe we use it for different sounds formats later too
    if(object_type2!=nullptr){
        QDirIterator it2(QString(PATH.c_str()) + "Assets/"+folder+"/",QStringList()<<object_type2, QDir::NoFilter,QDirIterator::Subdirectories );
        while(it2.hasNext())
        {
            QString path=it2.next();
            QFileInfo fileInfo(path);
            QString name=fileInfo.baseName();
            //qDebug()<<fileInfo.filePath()<<" "<<fileInfo.absoluteFilePath()<<"\n";
            mFilesNamesSet.insert(name); //for future check if mesh has been imported in the engine before
            mFilesNamesStack.push_back(path); //for loading in all meshes when we start engine
        }
    }

    for(auto it: mFilesNamesStack)
    {
        T* asset=new T(it);
        mAssets.push_back(asset);
    }
}

// template<typename T>
// inline void AssetManager<T>::addNewMesh(gea::Mesh *newMesh)
// {
//     mAssets.push_back(newMesh);
// }

template<typename T>
inline void AssetManager<T>::addNewAsset(T *newAsset)
{
    mAssets.push_back(newAsset);
}

template<typename T>
inline void AssetManager<T>::importTextures()
{

}



template<typename T>
void AssetManager<T>::importObjects(){

    if constexpr (std::is_same<T,gea::Mesh*>::value){ //constexpr
        QString folder="Models";
        QString object_type="*.obj";
        importAssets(folder, object_type, nullptr);
    }
    else if constexpr (std::is_same<T,gea::Texture>::value){
        QString folder="Textures";
        QString object_type="*.obj";
        QString object_type2="*.png";
        importAssets(folder, object_type,object_type2);
    }
    else if constexpr (std::is_same<T,wave_t>::value){
        QString folder="Sounds";
        QString object_type="*.wav"; //or mp3
        importAssets(folder, object_type,nullptr);
    }
};

#endif // ASSETMANAGER_H

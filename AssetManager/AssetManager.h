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

    std::vector<gea::Mesh*> mAssets;
    std::vector<gea::Texture*> mTextures;
    std::vector<wave_t> mSounds;

    QSet<QString> mFilesNamesSet;
    QStack<QString> mFilesNamesStack;
    void importMeshes();
    void addNewMesh(gea::Mesh* newMesh);

    void importTextures();
    void importSounds();
    void importObjects();


    // void deleteAsset(T asset);
};

template<typename T>
void AssetManager<T>::importMeshes()
{
    QDirIterator it(QString(PATH.c_str()) + "Assets/Models/",QStringList()<<"*.obj", QDir::NoFilter,QDirIterator::Subdirectories );
    while(it.hasNext())
    {
        QString path=it.next();
        QFileInfo fileInfo(path);
        QString name=fileInfo.baseName();
        //qDebug()<<fileInfo.filePath()<<" "<<fileInfo.absoluteFilePath()<<"\n";
        mFilesNamesSet.insert(name); //for future check if mesh has been imported in the engine before
        mFilesNamesStack.push_back(path); //for loading in all meshes when we start engine
    }

    for(auto it: mFilesNamesStack)
    {
        gea::Mesh* mesh=new gea::Mesh(it);
        mAssets.push_back(mesh);
    }
}

template<typename T>
inline void AssetManager<T>::addNewMesh(gea::Mesh *newMesh)
{
    mAssets.push_back(newMesh);
}



template<typename T>
void AssetManager<T>::importObjects(){

    if constexpr (std::is_same<T,gea::Mesh*>::value){ //constexpr
        importMeshes();
    }
    else if constexpr (std::is_same<T,gea::Texture>::value){
        importTextures();
    }
    else if constexpr (std::is_same<T,wave_t>::value){
        importSounds();
    }
};

#endif // ASSETMANAGER_H

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
#include "Core/Utilities.h"
#include <type_traits>

template <typename T>
class AssetManager{
public:
    AssetManager<T>() = default;
    void initialize()
    {
        importObjects();
    };

    std::vector<T*> mAssets;
    //std::vector<gea::Texture*> mTextures;
    //std::vector<wave_t> mSounds;

    QSet<QString> mFilesNamesSet;
    QStack<QString> mFilesNamesStack;

    void addNewAsset(T* newAsset);
    void changeFilePath(T* newAsset, QString correctFolder);
    //void addNewAsset(const T& newAsset);

    // void importTextures();
    // void importSounds();

    void importObjects();
    void importAssets(QString folder, QString object_type, QString object_type2);


    // void deleteAsset(T asset);
};

template<typename T>
void AssetManager<T>::importAssets(QString folder, QString object_type, QString object_type2)
{
    qDebug() << "AssetManager reading " << object_type << " files";
    QDirIterator it(QString(PATH.c_str()) + "Assets/"+folder+"/",QStringList()<<object_type, QDir::NoFilter,QDirIterator::Subdirectories );
    std::vector<QFileInfo> files; //temporary storing files, so we can sort them by modification date or it messes up order of indexes for next time qt starts
    while(it.hasNext())
    {
        files.push_back(QFileInfo(it.next()));
    }

    // QString path=it.next();
    // QFileInfo fileInfo(path);
    // QString name=fileInfo.baseName();
    // //qDebug()<<fileInfo.filePath()<<" "<<fileInfo.absoluteFilePath()<<"\n";
    // mFilesNamesSet.insert(name); //for future check if mesh has been imported in the engine before
    // mFilesNamesStack.push_back(path); //for loading in all meshes when we start engine

    //thought this is needed because we probably dont want to limit to either .jpg or .png, so we read both
    //maybe we use it for different sounds formats later too
    if(object_type2!=nullptr)
    {
        QDirIterator it2(QString(PATH.c_str()) + "Assets/"+folder+"/",QStringList()<<object_type2, QDir::NoFilter,QDirIterator::Subdirectories );
        while(it2.hasNext())
        {
            files.push_back(QFileInfo(it2.next()));
            // QString path=it2.next();
            // QFileInfo fileInfo(path);
            // QString name=fileInfo.baseName();
            // //qDebug()<<fileInfo.filePath()<<" "<<fileInfo.absoluteFilePath()<<"\n";
            // mFilesNamesSet.insert(name); //for future check if mesh has been imported in the engine before
            // mFilesNamesStack.push_back(path); //for loading in all meshes when we start engine
        }
    }

    //reorder assets in a folder based on how recently they have been added, newest last
    std::sort(files.begin(), files.end(), [](const QFileInfo& newestFile, const QFileInfo& oldFile){
        // if ( oldFile.birthTime()>newestFile.birthTime())
        //     return oldFile;
        //return oldFile.birthTime()>newestFile.birthTime();
        return oldFile.lastModified()>newestFile.lastModified();
    });


    for(QFileInfo& it: files)
    {
        QString path = it.filePath();
        QString name = it.baseName();
        qDebug() << "   " << name; //<<fileInfo.absoluteFilePath()<<"\n";
        mFilesNamesSet.insert(name); //for future check if mesh has been imported in the engine before
        mFilesNamesStack.push_back(path); //for loading in all meshes when we start engine
    }

    for(auto it: mFilesNamesStack)
    {
        T* asset=new T(it);
        mAssets.push_back(asset);
    }
}



template<typename T>
void AssetManager<T>::addNewAsset(T *newAsset)
{
    mAssets.push_back(newAsset);
    //move new asset to correct folder
    if constexpr (std::is_same<T,gea::Mesh>::value)
    {
        QString correctFolder=QString(PATH.c_str()) + "Assets/Models/"; //folder we are copying new file to
        // if(newAsset->mPath){
        changeFilePath(newAsset, correctFolder);
    }
    else if constexpr (std::is_same<T,gea::Texture>::value)
    {
        QString correctFolder=QString(PATH.c_str()) + "Assets/Textures/";
        changeFilePath(newAsset, correctFolder);
    }
    else if constexpr (std::is_same<T,wave_t>::value)
    {
        QString correctFolder=QString(PATH.c_str()) + "Assets/Sounds/";
        changeFilePath(newAsset, correctFolder);
    }
    else
        qDebug()<<"WRONG: not reading objects";
}

template<typename T>
inline void AssetManager<T>::changeFilePath(T* newAsset, QString correctFolder)
{
    QFileInfo fileInfo(newAsset->mPath); //get new file path, so we can change it
    QString new_path = correctFolder+fileInfo.fileName();
    QFile::copy(newAsset->mPath,new_path);
    newAsset->mPath = new_path;
    //change time to sort by "added to folder" date
    QFile importedFile(new_path);
    if(importedFile.open(QIODevice::ReadWrite))
    {//this is supposed to "open" the file without opening it to change modification date
        importedFile.setFileTime(QDateTime::currentDateTime(),QFileDevice::FileModificationTime); //set last modified to the time when we import this to correct folder
        importedFile.close();
    }
    //fileInfo.birthTime()=current time;
}

// template<typename T>
// void AssetManager<T>::addNewAsset(const T& newAsset)
// {
//     mAssets.push_back(newAsset);
// }

template<typename T>
void AssetManager<T>::importObjects()
{
    if constexpr (std::is_same<T,gea::Mesh>::value)
    { //const expression comparisson, check if T is Mesh, call import Assets with mesh
        QString folder="Models";
        QString object_type="*.obj";
        importAssets(folder, object_type, nullptr);
    }
    else if constexpr (std::is_same<T,gea::Texture>::value)
    {
        QString folder="Textures";
        QString object_type="*.jpg";
        QString object_type2="*.png";
        importAssets(folder, object_type,object_type2);
    }
    else if constexpr (std::is_same<T,wave_t>::value)
    {
        QString folder="Sounds";
        QString object_type="*.wav"; //or mp3
        importAssets(folder, object_type,nullptr);
    }
    else
        qDebug()<<"WRONG: not reading objects";
};

#endif // ASSETMANAGER_H

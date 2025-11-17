#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "../../components/mesh.h"

#include <QHash>
#include <qobject.h>
#include <QDirIterator>



class AssetManager
{
public:
    AssetManager();



protected:

    //Path to the folder
    QString AssethPath = "Assets";

    QString FileType = "*.obj";
     QString TextureType = "*.jpg";
    //contains all meshes
    std::vector<std::unique_ptr<Mesh>> mMesh;
    std::vector<std::unique_ptr<QString>> mTextures;

    //Stores a mesh name, for quick check
    QHash<QString, int> mFilesNames;
    //Stores all filepaths to objects
     QHash<QString, QString> mFilesPath;

    //Stores all filepaths to objects
    QHash<QString, QString> mTexturesPath;


public:

    void ImportMesh(const QString& AssethPath);

    QStringList GetMeshNames()const;

    QString FindMesh(const QString& Name);


     QStringList GetTexturesNames()const;

};

#endif // ASSETMANAGER_H

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "mesh.h"

#include <QHash>
#include <qobject.h>
#include <QDirIterator>



class AssetManager
{
public:
    AssetManager();



protected:

    //Path to the folder
    QString AssethPath = "Assets/Models";

    //contains all meshes
    std::vector<std::unique_ptr<Mesh>> mMesh;

    //Stores a mesh name, for quick check
    QHash<QString, int> mFilesNames;


public:

    void FindObject();

    void ImportMesh(const QString& AssethPath);

    QStringList GetMeshNames()const;




};

#endif // ASSETMANAGER_H

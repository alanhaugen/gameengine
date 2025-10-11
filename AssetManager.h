#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <vector>
#include "Vertex.h"
#include <QString>
#include <QSet>
#include <QStack>

template <typename T>
class AssetManager{
public:
    AssetManager<T>()=default;
    AssetManager<T>(std::vector<T> input_vector)
    {
        for(auto it: input_vector)
        {
            mIntintAssets.push_back(it);
        }
    };

    std::vector<T*> mAssets;

    std::vector<T> mIntintAssets;

    QSet<QString> mFilesNamesSet;
    QStack<QString> mFilesNamesStack;
    // void import(T asset);
    // void deleteAsset(T asset);
};

struct ObjAsset
{  //currently mesh component
    ObjAsset()=default;

    std::vector<Vertex> mVertices;
    std::vector<uint32_t> mIndices;
    bool mIsActive=false;
};

//add flag if the mesh is used when drawing it after loading them in
//use the flags to also give warning before deleting the mesh, if any entities use that mesh


#endif // ASSETMANAGER_H

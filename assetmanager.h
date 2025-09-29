#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <vector>
#include "Vertex.h"
#include <QString>
#include <QStack>
template <typename T>
class AssetManager{
public:
    std::vector<T*> assets;

    std::vector<T> int_assets;
    AssetManager<T>()=default;
    AssetManager<T>(std::vector<T> input_vector){
        for(auto it: input_vector){
            int_assets.push_back(it);
        }};

    QStack<QString> filesNamesStack;
    // void import(T asset);
    // void deleteAsset(T asset);
};


struct ObjAsset{  //currently mesh component
    ObjAsset()=default;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    bool isActive=false;
};
//add flag if the mesh is used when drawing it after loading them in
//use the flags to also give warning before deleting the mesh, if any entities use that mesh


#endif // ASSETMANAGER_H

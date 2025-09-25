#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <vector>
#include "Vertex.h"
template <class T>
class AssetManager{
public:
    std::vector<T> assets;
    AssetManager<T>(std::vector<T> input_type){for (auto it: input_type)
        {
            assets.push_back(it);};};

    // void import(T asset);
    // void deleteAsset(T asset);
};

struct Asset{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

};
//add flag if the mesh is used when drawing it after loading them in
//use the flags to also give warning before deleting the mesh, if any entities use that mesh


#endif // ASSETMANAGER_H

#ifndef SCENE_H
#define SCENE_H

#include <vulkan/vulkan_core.h>
#include <QString>
#include "External/json.hpp"


namespace gea
{

class Scene
{
public:
    Scene();

    void LoadScene(QString MODEL_PATH);
};

#endif // SCENE_H
}

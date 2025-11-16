#ifndef GENERATEDSCENE_H
#define GENERATEDSCENE_H

#include "core/x-platform/scene.h"

class GeneratedScene : public Scene
{
public:
    GeneratedScene(std::string fileName);
    void Init();
    void Update();
    void Clean();
};

#endif // GENERATEDSCENE_H

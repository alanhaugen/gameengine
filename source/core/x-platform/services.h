#ifndef SERVICES_H
#define SERVICES_H

#include "core/x-platform/locator.h"
#include "core/x-platform/scene.h"

class Services : public Locator
{
public:
    Services();

private:
    static std::vector<Scene*> scenes;

public:
    static Scene* currentScene;

    void AddScene(Scene* scene);
    void SetScene(Scene* scene);
    static void SetScene(int index);
    static Scene* GetScenes();

};

#endif // SERVICES_H

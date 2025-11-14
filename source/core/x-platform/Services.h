#ifndef SERVICES_H
#define SERVICES_H

#include "core/x-platform/locator.h"
#include "core/x-platform/scene.h"
class Services : public Locator
{
public:
    Services();

private:
    std::vector<Scene*> scenes;
    Scene* currentScene= nullptr;

public:
    void AddScene(Scene* scene);
    void SetScene(Scene* scene);
   static void SetScene(int index);

    Scene* GetCurrentScene();




};

#endif // SERVICES_H

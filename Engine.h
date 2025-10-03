#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <memory>
#include "Entity.h"
#include "Components.h"

class Renderer;

namespace gea
{
    class System;

    class Engine
    {
    public:
        Engine();
        ~Engine();

        void Initialize(Renderer* renderer);
        void Update(float deltaTime);
        void Quit();

        Entity& CreateEntity();
        void DestroyEntity(size_t entityID);

    private:
        std::vector<std::unique_ptr<System>> mSystems;
        void InitializeSystems();
    };
}
#endif // ENGINE_H

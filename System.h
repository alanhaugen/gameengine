#ifndef SYSTEM_H
#define SYSTEM_H

// Base class for all game systems
// Systems operate on component data and implement game logic

namespace gea
{
    class System
    {
    public:
        virtual void update(float deltaTime) = 0;
        virtual ~System() = default;

        // Enable/disable systems
        bool mEnabled{true};
    };
}

#endif // SYSTEM_H

#ifndef SYSTEM_H
#define SYSTEM_H


//Maybe make a parent class that different systems should inherit from?

//One could have a common update() function for all Systems and then have a vector allSystems with all systems.
//Then run
//for (auto sys : allSystems) {
//    sys->update();
//}


//We will not have that many systems, and maybe want to control what order the systems will run, so I don't see that this is wise...
//Seems easier at the start to just make the separate systems on their own in their own independent classes...


//Need namespace, since we start to get naming collisions with other code
namespace gea
{
    class System
    {
    public:
        virtual void update() = 0;        // pure virtual → interface
        virtual ~System() = default;     // virtual dtor: safe deletion

    };
}

#endif // SYSTEM_H

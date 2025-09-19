#pragma once

#define PLATFORM_HEADER "qt/qtapplication.h"
#define PLATFORM QtApplication

#include PLATFORM_HEADER

class Application : public PLATFORM
{
public:
    Application(int argc, char* argv[]);
    int Run();
};


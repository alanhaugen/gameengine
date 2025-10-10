#include "debug.h"
#include <iostream>

Debug::Debug()
{
}

void Debug::Write(std::string log)
{
    std::cout << log;
}

void Debug::Warning(std::string log)
{
    std::cout << log;
}

void Debug::Error(std::string log)
{
    std::cout << log;
}

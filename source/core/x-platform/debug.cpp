#include "debug.h"
#include <iostream>

#include "locator.h"

Debug::Debug()
{
}

void Debug::Write(std::string log)
{
    //std::cout << log;
    Locator::editor->AddLogMessage(log.c_str());
}

void Debug::Warning(std::string log)
{
    //std::cout << log;
    Locator::editor->AddLogMessage(log.c_str());
}

void Debug::Error(std::string log)
{
    std::cout << log;
}

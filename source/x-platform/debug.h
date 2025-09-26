#ifndef DEBUG_H
#define DEBUG_H

#include <string>

class Debug
{
public:
    Debug();
    void Write(std::string log);
    void Warning(std::string log);
    void Error(std::string log);
};

#endif // DEBUG_H

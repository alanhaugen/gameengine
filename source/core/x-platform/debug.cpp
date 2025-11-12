#include "debug.h"
#include <iostream>
#include <QMessageBox>
#include <QString>

#include "locator.h"

Debug::Debug()
{
}

void Debug::Write(std::string log)
{
    Locator::editor->AddLogMessage(log.c_str());
}

void Debug::Warning(std::string log)
{
    Locator::editor->AddLogMessage("Warning:");
    Locator::editor->AddLogMessage(log.c_str());
}

void Debug::Error(std::string log)
{
    QMessageBox::critical(nullptr, "Error", QString(log.c_str()));
    std::cout << log;
}

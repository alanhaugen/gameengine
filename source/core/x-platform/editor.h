#ifndef EDITOR_H
#define EDITOR_H

class Editor
{
public:
    virtual void AddEntity(const char* name,unsigned id) = 0;
    virtual void UpdateStatusBar(const char* text) = 0;
    virtual void AddLogMessage(const char* text) = 0;
};

#endif // EDITOR_H

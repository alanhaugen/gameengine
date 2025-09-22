#ifndef QTEDITOR_H
#define QTEDITOR_H

#include "../../x-platform/editor.h"
#include "mainwindow.h"

class QtEditor : public Editor
{
private:
    Ui::MainWindow* ui;

public:
    QtEditor(Ui::MainWindow* inUi);
    void AddEntity(const char* name);
};

#endif // QTEDITOR_H

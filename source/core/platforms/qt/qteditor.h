#ifndef QTEDITOR_H
#define QTEDITOR_H

#include "../../x-platform/editor.h"
#include "mainwindow.h"

class QtEditor : public Editor
{
private:
    Ui::MainWindow* ui;
    QStatusBar *statusBar = nullptr;
    std::unordered_map<unsigned, QTreeWidgetItem*> entityItems;

public:
    QtEditor(Ui::MainWindow* inUi, QStatusBar* inStatusBar);
    void AddEntity(const char* name, unsigned int id);
    void AddComponent(const char* name, unsigned int id);
    void UpdateStatusBar(const char* text);
    void AddLogMessage(const char* text);
};

#endif // QTEDITOR_H

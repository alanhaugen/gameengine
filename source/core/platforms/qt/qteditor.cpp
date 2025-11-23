#include "qteditor.h"
#include "ui_MainWindow.h"
#include <QTreeWidget>

QtEditor::QtEditor(Ui::MainWindow *inUi, QStatusBar *inStatusBar)
{
    ui = inUi;
    statusBar = inStatusBar;
}

void QtEditor::AddEntity(const char *name,unsigned id)
{
    QTreeWidgetItem* MainObj = new QTreeWidgetItem(ui->treeGameObjects);

    MainObj->setText(0, name);
    MainObj->setData(0, Qt::UserRole, QVariant::fromValue(id));
    MainObj->setExpanded(true);

    entityItems[id] = MainObj;
}

void QtEditor::AddComponent(const char *name, unsigned int id)
{
    auto it = entityItems.find(id);
    if (it == entityItems.end())
        return; // No entity with this ID

    QTreeWidgetItem* MainObj = it->second;

    QTreeWidgetItem* ObjItem = new QTreeWidgetItem(MainObj);
    ObjItem->setText(0, name);
    ObjItem->setData(0,Qt::UserRole +1,"Component");

    MainObj->addChild(ObjItem);
}

void QtEditor::UpdateStatusBar(const char *text)
{
    if (statusBar)
    {
        statusBar->showMessage(text);
    }
}

void QtEditor::AddLogMessage(const char *text)
{
    ui->plainTextEdit->appendPlainText(text);
}

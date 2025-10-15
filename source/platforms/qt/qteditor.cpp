#include "qteditor.h"
#include "ui_MainWindow.h"
#include <QTreeWidget>

QtEditor::QtEditor(Ui::MainWindow *inUi, QStatusBar *inStatusBar)
{
    ui = inUi;
    statusBar = inStatusBar;
}

void QtEditor::AddEntity(const char *name)
{
    QTreeWidgetItem * MainObj = new QTreeWidgetItem(ui->treeGameObjects);

    MainObj->setText(0, "GameObject");
    MainObj->setExpanded(true);

    QTreeWidgetItem * ObjItem = new QTreeWidgetItem(MainObj);
    ObjItem->setText(0, "mesh");

    MainObj->addChild(ObjItem);
}

void QtEditor::UpdateStatusBar(const char *text)
{
    if (statusBar)
    {
        statusBar->showMessage(text);
    }
}

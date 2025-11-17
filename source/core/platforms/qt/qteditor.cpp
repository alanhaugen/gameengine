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
    QTreeWidgetItem * MainObj = new QTreeWidgetItem(ui->treeGameObjects);


    MainObj->setText(0, "GameObject");
    MainObj->setData(0, Qt::UserRole, QVariant::fromValue(id));
    MainObj->setData(0,Qt::UserRole +1,"GameObject");
    MainObj->setExpanded(true);

    QTreeWidgetItem * ObjItem = new QTreeWidgetItem(MainObj);
    ObjItem->setText(0, "mesh");
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

#include "qteditor.h"
#include "ui_MainWindow.h"
#include <QTreeWidget>

QtEditor::QtEditor(Ui::MainWindow *inUi)
{
    ui = inUi;
}

void QtEditor::AddEntity(const char *name)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(name), 0);
    ui->treeGameObjects->addTopLevelItem(item);
}

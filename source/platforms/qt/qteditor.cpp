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
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(name), 0);
    ui->treeGameObjects->addTopLevelItem(item);
}

void QtEditor::UpdateStatusBar(const char *text)
{
    if (statusBar)
    {
        statusBar->showMessage(text);
    }
}

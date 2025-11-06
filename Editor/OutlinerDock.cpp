#include "Editor/OutlinerDock.h"
#include "Editor/EntityModel.h"
#include <QListView>
#include <QAbstractItemView>

gea::OutlinerDock::OutlinerDock(EntityModel *modelIn, QWidget* parent) : QDockWidget(tr("Outliner"), parent)
{
    mView = new QListView(this);
    mView->setSelectionMode(QAbstractItemView::SingleSelection);
    mModel = modelIn;
    mView->setModel(mModel);
    setWidget(mView);
    // Optional: enable drag & drop on the view if needed
    mView->setDragEnabled(true);
    //mView->setAcceptDrops(true);
    //mView->setDropIndicatorShown(true);
}

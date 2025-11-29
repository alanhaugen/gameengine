#include "ui_gameobjecttree.h"
#include <qevent.h>

UI_GameObjectTree::UI_GameObjectTree() {}

void UI_GameObjectTree::mousePressEvent(QMouseEvent *event)
{
    QTreeWidgetItem* item = itemAt(event->pos());

    if(item)
    {
        QTreeWidget::mousePressEvent(event);
    }
    else
    {
        EmptyArea();
    }
}



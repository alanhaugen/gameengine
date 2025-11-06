#ifndef OUTLINERDOCK_H
#define OUTLINERDOCK_H

#include <QDockWidget>

//forward declare - not part of gea::
class QListView;

namespace gea
{
//forward declare
class EntityModel;

class OutlinerDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit OutlinerDock(EntityModel* modelIn, QWidget* parent = nullptr);

private:
    EntityModel* mModel{ nullptr };
    QListView* mView{ nullptr };
};

} // namespace gea

#endif // OUTLINERDOCK_H

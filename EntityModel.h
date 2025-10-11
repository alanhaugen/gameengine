#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include <qabstractitemmodel.h>
#include <qobject.h>
#include "EntityContainer.h"
namespace gea
{

class EntityModel : public QAbstractListModel
{
    Q_OBJECT
public:
    EntityModel(EntityContainer* entityData, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private slots:
    void handleNewEntity(int newIndex);

private:

    EntityContainer* mContainer{nullptr};
};

} //namespace gea

#endif // ENTITYMODEL_H

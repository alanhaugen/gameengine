#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include <qabstractitemmodel.h>
#include <qobject.h>
#include "Core/Engine.h"

namespace gea
{

class EntityModel : public QAbstractListModel
{
    Q_OBJECT
public:
    EntityModel(Engine* owner, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private slots:
    void handleNewEntity(int newIndex);

private:

    std::vector<Entity>* mContainer{nullptr};
};

} //namespace gea

#endif // ENTITYMODEL_H

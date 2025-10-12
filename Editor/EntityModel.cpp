#include "EntityModel.h"


gea::EntityModel::EntityModel(EntityContainer *entityData, QObject *parent) : QAbstractListModel(parent), mContainer(entityData)
{
    connect(mContainer, &EntityContainer::itemAppended, this, &EntityModel::handleNewEntity);
}

int gea::EntityModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return mContainer->count();
}

QVariant gea::EntityModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= mContainer->count())
        return QVariant();

    if (role == Qt::DisplayRole) {
        //had to explicitly return a QVariant on Mac - mEntityID is size_t
        return QVariant::fromValue(mContainer->getItem(index.row()).mEntityID);
    }

    return QVariant();
}

void gea::EntityModel::handleNewEntity(int newIndex)
{
    beginInsertRows(QModelIndex(), newIndex, newIndex);
    endInsertRows();
}

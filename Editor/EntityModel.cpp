#include "EntityModel.h"


gea::EntityModel::EntityModel(Engine *owner, QObject *parent) : QAbstractListModel(parent), mContainer(&owner->mEntities)
{
    connect(owner, &Engine::itemAppended, this, &EntityModel::handleNewEntity);
}

int gea::EntityModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
            return 0;
    return mContainer->size();
}

QVariant gea::EntityModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= mContainer->size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return QVariant::fromValue(mContainer->at(index.row()).mName);

    return QVariant();
}

void gea::EntityModel::handleNewEntity(int newIndex)
{
    beginInsertRows(QModelIndex(), newIndex, newIndex);
    endInsertRows();
}

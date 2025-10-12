#include "EntityContainer.h"

gea::EntityContainer::EntityContainer(QObject *parent) : QObject(parent)
{}

void gea::EntityContainer::appendItem(const gea::Entity &addition)
{
    mData.append(addition);
    emit itemAppended(mData.size() - 1);
}

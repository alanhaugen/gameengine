#ifndef ENTITYCONTAINER_H
#define ENTITYCONTAINER_H

#include <qobject.h>
#include "ECS/Entity.h"
namespace gea
{

class EntityContainer : public QObject
{
    Q_OBJECT
public:
    EntityContainer(QObject* parent = nullptr);

    int count() const { return mData.size(); }
    const Entity& getItem(int index) const { return mData.at(index); }


    void appendItem(const Entity& addition);

signals:
    void itemAppended(int newIndex);

private:
    QVector<Entity> mData;
};

} //namespace gea

#endif // ENTITYCONTAINER_H

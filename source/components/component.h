#pragma once

#include <qobject.h>


class Component
{
protected:
     QString Name;

public:


    virtual void Update() = 0;


    virtual void SetName(const QString NewName){Name = NewName;};

    virtual const QString GetName(){return Name;};
};



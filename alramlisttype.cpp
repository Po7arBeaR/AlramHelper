
#include "alramlisttype.h"

AlramListType::AlramListType(QObject *parent)
    : QObject{parent}
{
    AlramText.clear();
    isLoged=false;
}

AlramListType::AlramListType(const AlramListType &obj)
{
    this->AlramText=obj.AlramText;
    this->isLoged=obj.isLoged;
}

AlramListType AlramListType::operator=(const AlramListType &obj)
{

    if(this!=&obj)
    {
        this->AlramText=obj.AlramText;
        this->isLoged=obj.isLoged;
    }
    return *this;
}


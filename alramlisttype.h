
#ifndef ALRAMLISTTYPE_H
#define ALRAMLISTTYPE_H


#include <QObject>


class AlramListType : public QObject
{
    Q_OBJECT
public:
    explicit AlramListType(QObject *parent = nullptr);
    AlramListType(const  AlramListType& obj);
    AlramListType operator=(const  AlramListType& obj);

public:
    QString AlramText;
    bool isLoged;
};

#endif // ALRAMLISTTYPE_H

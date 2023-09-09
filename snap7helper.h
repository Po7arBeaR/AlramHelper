
#ifndef SNAP7HELPER_H
#define SNAP7HELPER_H


#include <QObject>
#include "snap7.h"
#include "load_config.h"
#include "alramlisttype.h"
class Snap7Helper : public QObject
{
    Q_OBJECT
public:
    explicit Snap7Helper(QObject *parent = nullptr);

signals:

public:
    TS7Client* m_client;
    QList<AlramListType> AlramList;
    load_config Config;
public:
    void ScanAlram();
    void FitAlramLog(int Length , int bit);
    void LoadAlramList(QString path);
    void CancleFlag(int Length , int bit);
};

#endif // SNAP7HELPER_H

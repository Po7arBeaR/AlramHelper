
#ifndef LOAD_CONFIG_H
#define LOAD_CONFIG_H


#include <QObject>
#include <QSettings>
#include <QFile>
struct Config
{
    Config() {}
    QString Ip;
    int DB;
    int length;
    QString Path;
};
class load_config : public QObject
{
    Q_OBJECT
public:
    explicit load_config(QObject *parent = nullptr);
    ~load_config();
signals:

public:
    Config config;
private:
    QSettings *setting;

};

#endif // LOAD_CONFIG_H

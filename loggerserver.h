
#ifndef LOGGERSERVER_H
#define LOGGERSERVER_H


#include <QObject>
#include <QSemaphore>

class LoggerServer : public QObject
{
    Q_OBJECT
public:
    explicit LoggerServer(QObject *parent = nullptr);

    static LoggerServer* getInstance();

    static void releaseInstances ()
    {
        if(m_instance!=NULL)
        {
            LoggerServer* tmp = m_instance;
            m_instance= NULL;
            delete tmp;
        }
    }
public:
private:
    QString m_fileName;
    QSemaphore m_mutex;

signals:
    void SendMeg(QString message);
    void logRecevied( QString message);
public slots:
    void log(const QString& message);
private:
    static LoggerServer* m_instance;

    class CHelper
    {
    public:
        CHelper()
        {
            LoggerServer::getInstance();
        }
        ~CHelper()
        {
            LoggerServer::releaseInstances();
        }
    };
    static CHelper m_helper;
};
extern LoggerServer pLogger;


#endif // LOGGERSERVER_H

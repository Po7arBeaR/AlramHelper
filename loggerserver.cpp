
#include "loggerserver.h"

#include "QDateTime"
#include <QFile>
#include <QTextStream>
LoggerServer::LoggerServer(QObject *parent)
    : QObject{parent}
{

}


LoggerServer* LoggerServer::m_instance;
LoggerServer::CHelper LoggerServer::m_helper;

LoggerServer* pclients = LoggerServer::getInstance();




LoggerServer *LoggerServer::getInstance()
{
    if (m_instance==NULL)
    {
        m_instance=new LoggerServer();

    }
    return  m_instance;
}

void LoggerServer::log(const QString& message)
{
    qDebug()<<message;//<<__FUNCTION__;
    if(message=="")return ;
    QString strFileName = QString("%1.txt").arg(QDateTime::currentDateTime().date().toString("yyyyMMdd"));
    QFile log_file("./log/"+strFileName);
    if(!log_file.open(QIODevice::Text| QIODevice::Append))
    {
        log_file.close();
        qDebug()<<"文件打开失败"<<__FUNCTION__;
        return;

    }
    QString msgtoWidget=QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss] ") +message;
    QTextStream out(&log_file);
    out << QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss] ") << message << Qt::endl;
    log_file.close();
   // emit this->logRecevied( msgtoWidget);
}



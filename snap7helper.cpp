#include "loggerserver.h"
#include "snap7helper.h"
#include <QDebug>
#include <QThread>
#include <QFile>
Snap7Helper::Snap7Helper(QObject *parent)
    : QObject{parent},
    m_client(new  TS7Client)
{
    LoadAlramList(this->Config.config.Path);
    qDebug()<<"正在连接PLC地址："<<this->Config.config.Ip;
    m_client->ConnectTo(this->Config.config.Ip.toStdString().c_str(),0,1);

    if(m_client->Connected())
    {
        qDebug()<<"连接成功，报警助手启动...";
        ScanAlram();
    }
    else
    {
        qDebug()<<this->Config.config.Ip<<"连接失败，请检测配置重新启动...";
    }
}

void Snap7Helper::ScanAlram()
{

    while(1){
        int length=0;
        for(length=0;length<Config.config.length;length++)
        {
        int reConnectTime=0;
        if(!m_client->Connected())
        {
            qDebug()<<"检测到连接失败,重新连接"<<"重连次数"<<reConnectTime+1<<"...";
             m_client->ConnectTo(this->Config.config.Ip.toStdString().c_str(),0,1);
            reConnectTime++;
             if(reConnectTime>3)
            {
                qDebug()<<"重连失败,已退出程序";
            }
            QThread::msleep(3000);
            if(m_client->Connected())
            {
                continue;
            }
        }
    byte w;
    m_client->DBRead(Config.config.DB,length,1,(void*)&w);
    //qDebug()<<"DB."<<length<<(short)w;
    int bitList[8];
    for(int i=0;i<8;i++)
    {
        int nTmp=(1<<i);
        bitList[i]=((w&nTmp)==nTmp)?1:0;
    }

    for(int i=0;i<8;i++)
    {
        //qDebug()<<"DB."<<length<<"."<<i<<":"<<bitList[i];
        if(bitList[i]==1)
        {
            FitAlramLog(length,i);
        }
        else
        {
            CancleFlag(length,i);
        }
    }
//    length++;
//    if(length>Config.config.length)
//    {
//        length=0;
//    }

    }
        QThread::msleep(1000);
    }
}

void Snap7Helper::FitAlramLog(int Length, int bit)
{
    int SearchNumb=(Length*8)+bit;
    if(AlramList.count()<=SearchNumb)
    {
        qDebug()<<"报警条目与BYTE长度不一致"<<"报警条目最大长度:"<<AlramList.count()<<"检索条目:"<<SearchNumb+1;
        return ;
    }
    if(AlramList.count()>=SearchNumb&&!AlramList[SearchNumb].isLoged)
    {
     //   qDebug()<<SearchNumb<<":"<<AlramList.count();
  //  qDebug()<<AlramList[SearchNumb];
    LoggerServer::getInstance()->log(AlramList[SearchNumb].AlramText);
    AlramList[SearchNumb].isLoged=true;
    }

}

void Snap7Helper::LoadAlramList(QString path)
{
    //AlramList.append();
    QFile file(path);
    bool bopen=file.open(QIODevice::ReadOnly|QIODevice::Text);
    if(!bopen)
    {
    qDebug()<<path<<"打开失败";
    if(file.isOpen())file.close();
    return ;
    }
    else
    {
    while(!file.atEnd())
    {
        AlramListType Alram;
        Alram.AlramText=file.readLine();
        AlramList.append(Alram);
    }

    qDebug()<<"从"<<path<<"加载完成"<<",条目["<<AlramList.count()<<"]";
    }
    if(file.isOpen())file.close();
}

void Snap7Helper::CancleFlag(int Length, int bit)
{
    int SearchNumb=(Length*8)+bit;
    if(AlramList.count()<SearchNumb)
    {
    qDebug()<<"报警条目与BYTE长度不一致"<<"报警条目最大长度:"<<AlramList.count()<<"检索条目:"<<SearchNumb+1;
    return ;
    }
    if(AlramList.count()>=SearchNumb&&AlramList[SearchNumb].isLoged)
    {
    //  qDebug()<<AlramList[SearchNumb];
    AlramList[SearchNumb].isLoged=false;
    }
}



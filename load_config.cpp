
#include "load_config.h"

load_config::load_config(QObject *parent)
    : QObject{parent}
{

    setting = new QSettings("./setting.ini",QSettings::IniFormat);
    if(!QFile::exists("./setting.ini"))
      {
            setting->setValue("IPAddress","0.0.0.0");
            setting->setValue("Path","./AlramList.csv");
            setting->setValue("DB",100);
            setting->setValue("DBAddress",0);
      }
      config.Ip= setting->value("IPAddress","0.0.0.0").toString();
      config.Path=setting->value("Path","./AlramList.csv").toString();
      config.DB=setting->value("DB",100).toInt();
      config.length=setting->value("DBAddress",0).toInt();
      qDebug()<<"已加载配置文件";

}

load_config::~load_config()
{
      qDebug()<<"配置已卸载";
      delete setting;
}




﻿#include "pceggsdatabase.h"
#include <QMessageBox>
#include <QDebug>
PCeggsDataBase::PCeggsDataBase(QObject *parent) : QObject(parent)
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(QString("127.0.0.1"));
    db.setDatabaseName(QString("pceggs.db"));
    /*db.setUserName(QString("superadmin"));
    db.setPassword(QString("admin"));*/

}
bool PCeggsDataBase::getData(QString LID)
{
    if(!db.open())
    {
        QMessageBox::critical(nullptr, QObject::tr("错误"),
            QObject::tr("无法连接到数据库！."
                        "点此退出."), QMessageBox::Cancel);
        return false;
        //qCritical() << db.lastError();
    }
    if(db.open())
    {
        //qDebug()<<"open";
        QSqlQuery query(db);
        //query.prepare("SELECT * FROM Login WHERE user=':user' and pwd=':pwd'"); //准备执行SQL查询
        //.bindValue(":user", user);   //在这定占位符上确定绑定的值
        //query.bindValue(":pwd", pwd);
        QString s=QString("SELECT * FROM pceggs WHERE LID='%1' ").arg(LID);
        query.exec(s);
        if(query.first())
        {
            //qDebug()<<query.at();
            //qDebug()<<query.record().count();
            return true;

        }

    }
    db.close();
    return false;
}

bool  PCeggsDataBase::createData(QString LID, QString issue,QString CTime, QString results,QString results1,QString results2,QString results3)
{

    if(db.open())
    {
        if(db.driver()->hasFeature(QSqlDriver::Transactions))
        {
            if(db.transaction())
                {
                    QSqlQuery query;
                    QString s1=QString("INSERT INTO data VALUES('%1', '%2', '%3', '%4','%5','%6','%7')").arg(LID.toInt()).arg(issue.toInt()).arg(CTime.toInt()).arg(results.toInt()).arg(results1.toInt()).arg(results2.toInt()).arg(results3.toInt());
                        if(query.exec(s1))
                        {
                            if(!db.commit())
                            {
                                if(!db.rollback())
                                {
                                    qDebug()<<"cannot rollback";
                                    return false;
                                }
                                else
                                    qDebug()<<"cannot commit";
                            }
                            else
                            {
                                qDebug()<<"success";
                                return true;
                            }

                        }
                        else
                            qDebug()<<"cannot insert";
                }
            else
                qDebug()<<"transaction error";

         }
         else
             qDebug()<<"tf error";
    }
    else
        qDebug()<<"open fail";

 db.close();
 return false;
 //query.prepare("INSERT INTO pceggs  VALUES (A123, A123)"); //准备执行SQL查询
 //query.bindValue(":user", user);   //在这定占位符上确定绑定的值
 //query.bindValue(":pwd", pwd);
}
bool PCeggsDataBase::createTable()
{
    if(!db.open())
    {
        qDebug()<<"openfail";
    }
    if(db.open())
    {
          QSqlQuery query(db);
          QString s=QString("CREATE TABLE data(LID int primary key not null,issue int not null,CTime int not null,results int not null,results1 int not null,results2 int not null,results3 int not null)");
          if(query.exec(s))return true;
          else
              return false;
    }
    db.close();

}

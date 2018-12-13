#include <QApplication>
#include <QDesktopWidget>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QVariantList>
#include "mainwindow.h"
#include "interface.h"
#include <iostream>
#include <QProcess>
#include <QDesktopServices>
#include <QUrl>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QDesktopServices::openUrl(QUrl("file:///C:/ethereum/Qt/WormServer1_1/GethJavaScriptConsole.bat"));
    QDesktopWidget* deskWidget = a.desktop();
    QRect screenRect  = deskWidget->screenGeometry();
    screen_width = screenRect.width();
    screen_height = screenRect.height();
    //数据库创建
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("userData.db");
    if(database.open())
    {
        qDebug()<<"Database Opened";
        QSqlQuery sql_query;
        QString create_sql = "create table appPath (name varchar(30) PRIMARY KEY, path varchar(30))"; //创建数据表
        QString selectsql ="select * from sqlite_master where name='appPath'" ;//是否已经存在表car_bayonet_info
        sql_query.exec(selectsql);
        if(!sql_query.next())
        {
            sql_query.prepare(create_sql); //创建表

            if(!sql_query.exec()) //查看创建表是否成功
            {
                qDebug()<<QObject::tr("Table Create failed");
                qDebug()<<sql_query.lastError();
                return 0;
            }
            qDebug()<< "Table Created" ;

        }
    }
   // database.close();
    MainWindow w;
    w.show();
    return a.exec();
}

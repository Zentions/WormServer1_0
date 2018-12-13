#include "workpanel.h"
#include "ui_workpanel.h"
#include <QMessageBox>
#include <QDateTime>
WorkPanel::WorkPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkPanel)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    ui->listWidget->setStyleSheet("QListWidget{border:1px solid gray; color:black;}"
                               "QListWidget::Item{padding-top:10px; padding-bottom:10px; }"
                               "QListWidget::Item:hover{background:skyblue; }"
                               "QListWidget::item:selected{background:lightgray; color:red; }"
                               "QListWidget::item:selected:!active{border-width:0px; background:lightgreen; }"
                               );
    QFont list_font;
    list_font.setPointSize(12);
    list_font.setBold(true);
    list_font.setWeight(50);
    ui->listWidget->setFont(list_font);
    QString select_all_sql = "select * from appPath";
    //查询所有记录
    if(!sql_query.exec(select_all_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        int count=0;
        while(sql_query.next())
        {

            QString name = sql_query.value(0).toString();
            QString path = sql_query.value(1).toString();
            QListWidgetItem *item = new QListWidgetItem(name, ui->listWidget);
            if(count%2==0)item->setIcon(QIcon(".//imgs//app1.png"));
            else item->setIcon(QIcon(".//imgs//app2.png"));
            map.insert(name,path);
            count++;
        }
    }

}

WorkPanel::~WorkPanel()
{
    delete ui;
}

void WorkPanel::on_pushButton_clicked()
{
    QString name = ui->listWidget->currentItem()->text();
    if(name!=NULL && name.length()>0)
    {
        QStringList strList;//参数list
        QProcess::startDetached(map.value(name), strList);
    }
}





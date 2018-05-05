#include "appmanagedialog.h"
#include "ui_appmanagedialog.h"

AppManageDialog::AppManageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppManageDialog)
{
    ui->setupUi(this);
    root = new QTreeWidgetItem(ui->treeWidget);
    root->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    root->setText(0,"应用名称");
    root->setText(1,"路径");
    root->setCheckState(0,Qt::Unchecked);
    ui->treeWidget->setColumnWidth(0,300);
    isSuccess=false;
    connect(ui->treeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(treeItemChanged(QTreeWidgetItem*,int)));
    QString select_all_sql = "select * from appPath";
    //查询所有记录
    if(!sql_query.exec(select_all_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {

            QString name = sql_query.value(0).toString();
            QString path = sql_query.value(1).toString();
            QTreeWidgetItem* subItem = new QTreeWidgetItem(root);
            subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            subItem->setText(0,name);
            subItem->setText(1,path);
            subItem->setCheckState(0,Qt::Unchecked);
        }
    }

}


AppManageDialog::~AppManageDialog()
{
    delete ui;
}

void AppManageDialog::on_addButton_clicked()
{
    QString name = ui->nameEdit->text().trimmed();
    QString path = ui->pathEdit->text().trimmed();
    if(name!=NULL && path!=NULL )
    {
        sql_query.clear();
        QString insert = "insert into appPath values(?,?)";
        sql_query.prepare(insert);
        sql_query.bindValue(0,name);
        sql_query.bindValue(1,path);
        isSuccess= sql_query.exec();
        if(!isSuccess)
        {
            qDebug()<<sql_query.lastError();
            return;
        }
        QTreeWidgetItem* subItem = new QTreeWidgetItem(root);
        subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem->setText(0,name);
        subItem->setText(1,path);
        subItem->setCheckState(0,Qt::Unchecked);
    }
}

void AppManageDialog::on_delButton_clicked()
{
    sql_query.clear();
    QString del = "delete from appPath where name = ?";
    sql_query.prepare(del);
    int count = root->childCount();
    for(int i=0;i<count;i++)
    {
        if(root->child(i)->checkState(0)==Qt::Checked)
        {
            sql_query.bindValue(0,root->child(i)->text(0));
            sql_query.exec();
            root->removeChild(root->child(i));
            i--;
            count--;
        }
    }


}
void AppManageDialog::treeItemChanged(QTreeWidgetItem* item, int column)
{
    //QString itemText = item->text(0);
    if(Qt::Checked == item->checkState(0))
    {
       // QTreeWidgetItem* parent = item->parent();
        int count = item->childCount(); //返回子项的个数
        if(count >0)
        {
            for(int i=0; i<count; i++)
            {
                item->child(i)->setCheckState(0,Qt::Checked);
            }
        }
     }
    else if(Qt::Unchecked == item->checkState(0))
    {
        int count = item->childCount();
        if(count > 0)
        {
            for(int i=0; i<count; i++)
            {
                item->child(i)->setCheckState(0,Qt::Unchecked);
            }
        }
    }
    updateParentItem(item);
}
void AppManageDialog::updateParentItem(QTreeWidgetItem* item)
{

    QTreeWidgetItem *parent = item->parent();
    if(parent == NULL)
    {
        return ;
    }
    int selectedCount = 0;
    int childCount = parent->childCount();
    for(int i=0; i<childCount; i++) //判断有多少个子项被选中
    {
        QTreeWidgetItem* childItem = parent->child(i);
        if(childItem->checkState(0) == Qt::Checked)
        {
            selectedCount++;
        }
    }
    if(selectedCount <= 0)  //如果没有子项被选中，父项设置为未选中状态
    {
        parent->setCheckState(0,Qt::Unchecked);
    }
    else if(selectedCount>0 && selectedCount<childCount)    //如果有部分子项被选中，父项设置为部分选中状态，即用灰色显示
    {
        parent->setCheckState(0,Qt::PartiallyChecked);
    }
    else if(selectedCount == childCount)    //如果子项全部被选中，父项则设置为选中状态
    {
        parent->setCheckState(0,Qt::Checked);
    }
}

void AppManageDialog::on_addButton_2_clicked()
{
    int count = root->childCount();
    for(int i=0;i<count;i++)
    {
        if(root->child(i)->checkState(0)==Qt::Checked)
        {
            QStringList strList;//参数list
            QProcess::startDetached(root->child(i)->text(1).trimmed(), strList);
            break;
        }
    }
}

#ifndef APPMANAGEDIALOG_H
#define APPMANAGEDIALOG_H
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QVariantList>
#include <QDialog>
#include <QTreeWidgetItem>
#include <QProcess>

namespace Ui {
class AppManageDialog;
}

class AppManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AppManageDialog(QWidget *parent = 0);
    ~AppManageDialog();
private:
    void updateParentItem(QTreeWidgetItem* item);

private slots:
    void on_addButton_clicked();

    void on_delButton_clicked();
    void treeItemChanged(QTreeWidgetItem* item, int column);

    void on_addButton_2_clicked();

private:
    Ui::AppManageDialog *ui;
    QSqlQuery sql_query;
    bool isSuccess;
    QTreeWidgetItem * root;
};

#endif // APPMANAGEDIALOG_H

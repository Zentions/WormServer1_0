#ifndef WORKPANEL_H
#define WORKPANEL_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMap>
#include <QDebug>
#include <QTimer>
#include <QProcess>
namespace Ui {
class WorkPanel;
}

class WorkPanel : public QDialog
{
    Q_OBJECT

public:
    explicit WorkPanel(QWidget *parent = 0);
    ~WorkPanel();
//protected:
//   void closeEvent(QCloseEvent *);
private slots:
    void on_pushButton_clicked();

private:
    Ui::WorkPanel *ui;
    QSqlQuery sql_query;
    QMap<QString,QString> map;
    int last;
    int now;
};

#endif // WORKPANEL_H

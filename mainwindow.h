#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QUdpSocket>
#include <QMainWindow>
#define TRAN_SIZE 1024;
#include "interface.h"
#include "mapthread.h"
#include "cmdthread.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
#include <QObject>
#include <QVector>
#include "workpanel.h"
#include "appmanagedialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
//    void newMapClient(QString);
    void newCmdClient();
    void someSocketDisconnected();
//    void endMapClient();

private slots:
    void on_connectBtn_clicked();
 //   void handleTimeout();
    void on_disconnectBtn_clicked();
    void on_disconnectBtn_2_clicked();
protected:
    void paintEvent(QPaintEvent *e);
//signals:
//     void startMap(QString);
//     void endMap();
private:
    Ui::MainWindow *ui;
    QTcpServer* pCmdServer;
    QTcpSocket* clientCmdSocket;
    CmdThread* cmdThread;
    bool hasConnect;
    WorkPanel *workFrame;
 //   QTimer *m_pTimer;
    QString address;//客户ip
public:
    const static int DATA_HEARER_MAP = 1;    //图像数据
    const static int DATA_HEADER_CMD = 2;    //命令数据
    const static int DATA_HEARER_RES = 3;    //命令结果数据

    const static int MAP_SERVER_PORT = 5648;
    const static int CMD_SERVER_PORT = 5649;
};

#endif // MAINWINDOW_H



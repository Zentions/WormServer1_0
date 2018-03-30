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
    void newMapClient();
    void newCmdClient();
    void someSocketDisconnected();
private slots:
    void on_connectBtn_clicked();

    void on_disconnectBtn_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *m_udpSocket;
    QTcpServer* pCmdServer;
    QTcpServer* pMapServer;
    QTcpSocket* clientCmdSocket;
    CmdThread* cmdThread;
    bool hasConnect;
public:
    const static int DATA_HEARER_MAP = 1;    //图像数据
    const static int DATA_HEADER_CMD = 2;    //命令数据
    const static int DATA_HEARER_RES = 3;    //命令结果数据

    const static int MAP_SERVER_PORT = 5648;
    const static int CMD_SERVER_PORT = 5649;
};

#endif // MAINWINDOW_H



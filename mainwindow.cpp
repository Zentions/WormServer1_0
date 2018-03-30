#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkInterface>
#include <QHostAddress>
#include <QHostInfo>
#include <string>
#include <QDesktopWidget>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString localHostName = QHostInfo::localHostName();
    ui->serverHostName->setText(localHostName);
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> listAddress = hostInfo.addresses();
    QHostAddress tempAdd;
    foreach (tempAdd, listAddress) {
        if(tempAdd.toString().contains("172.")){
            ui->serverIPAddress->setText(tempAdd.toString());
        }
    }
    //m_udpSocket = new QUdpSocket(this);
    vec = new QVector<SocketAndThread>;
//    pMapServer = new QTcpServer;
//    pMapServer->listen(QHostAddress::Any, MAP_SERVER_PORT);
//    qDebug()<<"map server listening"<<endl;
//    connect(pMapServer, SIGNAL(newConnection()), this, SLOT(newMapClient()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectBtn_clicked()
{
    pCmdServer = new QTcpServer;
    pCmdServer->listen(QHostAddress::Any, CMD_SERVER_PORT);
    qDebug()<<"cmd server listening"<<endl;
    connect(pCmdServer, SIGNAL(newConnection()), this, SLOT(newCmdClient()));

}

void MainWindow::on_disconnectBtn_clicked()
{

}

/**
  *每当有一个新连接时，启动一个线程单独为之服务
  */
void MainWindow::newMapClient()
{
    QTcpSocket* clientMapSocket = pMapServer->nextPendingConnection();
    qDebug()<<"new map connection:"<<clientMapSocket->peerAddress().toString()<<endl;

    MapThread* mapThread = new MapThread(clientMapSocket);
    connect(clientMapSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));

    SocketAndThread st = {clientMapSocket, mapThread};
    vec->append(st);

    mapThread->start();
}

void MainWindow::newCmdClient()
{
    QTcpSocket* clientCmdSocket = pCmdServer->nextPendingConnection();
    qDebug()<<"new cmd connection:"<<clientCmdSocket->peerAddress().toString()<<endl;

    CmdThread* cmdThread = new CmdThread(clientCmdSocket);
    connect(clientCmdSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));

    SocketAndThread st = {clientCmdSocket, cmdThread};
    vec->append(st);

    cmdThread->start();
}

void MainWindow::someSocketDisconnected()
{
    qDebug()<<"cancel connect";
    for(int i = 0; i < vec->size(); i ++)
    {
        if(vec->at(i).socket->state() == QAbstractSocket::UnconnectedState)
        {
            if(vec->at(i).socket->isOpen())
                vec->at(i).socket->close();
            vec->at(i).thread->quit();
            connect(vec->at(i).thread, SIGNAL(finished()), vec->at(i).thread, SLOT(deleteLater()));
            vec->remove(i);
            i --;
        }
    }
}

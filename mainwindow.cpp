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
    hasConnect = false;
    connect(this, SIGNAL(startMap(QString)), this, SLOT(newMapClient(QString)));
    connect(this, SIGNAL(endMap()), this, SLOT(endMapClient()));
    ui->disconnectBtn->setEnabled(false);
    pCmdServer = new QTcpServer;
    clientCmdSocket = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectBtn_clicked()
{

    pCmdServer->listen(QHostAddress::Any, CMD_SERVER_PORT);
    qDebug()<<"cmd server listening"<<endl;
    connect(pCmdServer, SIGNAL(newConnection()), this, SLOT(newCmdClient()));
    this->ui->connectBtn->setEnabled(false);
    this->ui->disconnectBtn->setEnabled(true);
}

void MainWindow::on_disconnectBtn_clicked()
{
   qDebug()<<"cmd server stop"<<endl;
   if(pCmdServer->isListening())
   {
       pCmdServer->close();
       someSocketDisconnected();
   }
   this->ui->connectBtn->setEnabled(true);
   this->ui->disconnectBtn->setEnabled(false);
}

/**
  *每当有一个新连接时，启动一个线程单独为之服务
  */
void MainWindow::newMapClient(QString add)
{
//    QTcpSocket* clientMapSocket = pMapServer->nextPendingConnection();
//    qDebug()<<"new map connection:"<<clientMapSocket->peerAddress().toString()<<endl;

    mapThread = new MapThread(add);
    mapThread->start();
   // connect(clientMapSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));

}

void MainWindow::newCmdClient()
{
    if(hasConnect)return;
    clientCmdSocket = pCmdServer->nextPendingConnection();   
    QString address  = clientCmdSocket->peerAddress().toString();
    qDebug()<<"new cmd connection:"<<address;
    emit startMap(address);
    cmdThread = new CmdThread(clientCmdSocket);
    hasConnect = true;
    connect(clientCmdSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));
    this->hide();
    workFrame = new Form();
    workFrame->show();

}

void MainWindow::someSocketDisconnected()
{
    qDebug()<<"cancel connect";

    if(clientCmdSocket!=0 && clientCmdSocket->isOpen())
    {
       clientCmdSocket->close();
       emit endMap();
       this->show();
       workFrame->close();
    }
    hasConnect = false;

}
void MainWindow::endMapClient()
{
    qDebug()<<"end map";
    mapThread->requestInterruption();
    mapThread->quit();
    mapThread->wait();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkInterface>
#include <QHostAddress>
#include <QHostInfo>
#include <string>
#include <QDesktopWidget>
#include <QFile>
#include "workpanel.h"
#include <QApplication>
#include <QImage>
#include<QDebug>
#include <QProcess>
#include <QPainter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString localHostName = QHostInfo::localHostName();
    ui->serverHostName->setText(localHostName);
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
//    QList<QHostAddress> listAddress = hostInfo.addresses();
//    QHostAddress tempAdd;
//    foreach (tempAdd, listAddress) {
//        if(tempAdd.toString().contains("172.")){
//            ui->serverIPAddress->setText(tempAdd.toString());
//        }
//    }
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.count();
    for (int i = 0; i < nListSize; i++)
    {
        strIpAddress = ipAddressesList.at(i).toString();
        if(strIpAddress.contains("192.168.1")){
            break;
        }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())
     {
         strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
     }

    ui->serverIPAddress->setText(strIpAddress);
    hasConnect = false;
    //connect(this, SIGNAL(startMap(QString)), this, SLOT(newMapClient(QString)));
    //connect(this, SIGNAL(endMap()), this, SLOT(endMapClient()));
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
//void MainWindow::newMapClient(QString add)
//{
//    QTcpSocket* clientMapSocket = pMapServer->nextPendingConnection();
//    qDebug()<<"new map connection:"<<clientMapSocket->peerAddress().toString()<<endl;

   // connect(clientMapSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));

//}

void MainWindow::newCmdClient()
{
    if(hasConnect)return;
    clientCmdSocket = pCmdServer->nextPendingConnection();   
//    address  = clientCmdSocket->peerAddress().toString();
//    qDebug()<<"new cmd connection:"<<address;
    cmdThread = new CmdThread(clientCmdSocket);
    hasConnect = true;
    connect(clientCmdSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));
    this->hide();
    workFrame = new WorkPanel();
    workFrame->show();
    //emit startMap(address);
//    m_pTimer = new QTimer(this);
//    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
//    m_pTimer->start(100);

}

void MainWindow::someSocketDisconnected()
{
    qDebug()<<"cancel connect";

    if(clientCmdSocket!=0 && clientCmdSocket->isOpen())
    {
       clientCmdSocket->close();
       //emit endMap();
       this->show();
       workFrame->close();
    }
    delete cmdThread;
    hasConnect = false;
}
//void MainWindow::endMapClient()
//{
//    qDebug()<<"end map";
//}



void MainWindow::on_disconnectBtn_2_clicked()
{
    AppManageDialog *dia = new AppManageDialog;
    dia->exec();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QImage *image = new QImage("./imgs/3.bmp");
    if(image != 0)
    {
        QPainter p(this);
        p.drawImage(QRect(0, -20, 600, 380), *image);
    }
    QWidget::paintEvent(e);
}


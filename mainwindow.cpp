#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkInterface>
#include <QHostAddress>
#include <QHostInfo>
#include <string>
#include <QDesktopWidget>
#include <QFile>
#include "workpanel.h"
#ifndef HH_H
#define HH_H
#include <QApplication>
#include <Windows.h>
#include "Winuser.h"

#include<QDebug>
#include <QProcess>
HHOOK keyHook=NULL;
HHOOK mouseHook=NULL;
//声明卸载函数,以便调用
void unHook();
//键盘钩子过程
LRESULT CALLBACK keyProc(int nCode,WPARAM wParam,LPARAM lParam )
{
    //在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
    if(pkbhs->vkCode==VK_F12)
    {
       // pkbhs-
        unHook();
        qApp->quit();
    }
    else return ::CallNextHookEx(keyHook,nCode,wParam,lParam);

}
//鼠标钩子过程
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )
{
    MOUSEHOOKSTRUCT *pkbhs = (MOUSEHOOKSTRUCT *) lParam;
    HWND hwnd = ::GetForegroundWindow();
    RECT lpRect;
    ::GetWindowRect(hwnd,&lpRect);
    int x = pkbhs->pt.x;
    int y = pkbhs->pt.y;
    int left = lpRect.left;
    int right = lpRect.right;
    int top = lpRect.top;
    int bottom = lpRect.bottom;
    if(x>= (left+10) && x<= (right-10) && y>= (top+10) && y<= (bottom-10))
    {

        return ::CallNextHookEx(mouseHook,nCode,wParam,lParam);
    }
    else QCursor::setPos((left+right)/2, (top+bottom)/2);

//MOUSEHOOKSTRUCT
}
//卸载钩子
void unHook()
{
    UnhookWindowsHookEx(keyHook);
    UnhookWindowsHookEx(mouseHook);

}
//安装钩子,调用该函数即安装钩子
void setHook()
{
    //这两个底层钩子,不要DLL就可以全局
    //                         底层键盘钩子
    keyHook =SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);
    //                          底层鼠标钩子
    mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
}
#endif
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
    address  = clientCmdSocket->peerAddress().toString();
    qDebug()<<"new cmd connection:"<<address;
    cmdThread = new CmdThread(clientCmdSocket);
    hasConnect = true;
    connect(clientCmdSocket, SIGNAL(disconnected()), this, SLOT(someSocketDisconnected()));
    this->hide();
    workFrame = new WorkPanel();
    workFrame->show();
    setHook();
    emit startMap(address);
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
       emit endMap();
       this->show();
       unHook();
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



void MainWindow::on_disconnectBtn_2_clicked()
{
    AppManageDialog *dia = new AppManageDialog;
    dia->exec();
}

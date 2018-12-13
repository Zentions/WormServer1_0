#include "mapthread.h"
#include "interface.h"
#include "algo.h"
#include "consts.h"
#include <QFile>
#include <QTime>
#include<cstring>
/**
  *图像传输线程
  *建立一个双通道的tcp socket
  *启动一个定时器
  */
MapThread::MapThread(QString address, QObject *parent) :
    QThread(parent)
{

    this->ip = address;

   // connect(mapSocket, SIGNAL(readyRead()), this, SLOT(newData()));


}
void MapThread::run()
{
    qDebug()<<"start map";
    this->sendFrame();
}
void MapThread::sendFrame()
{

    while(!QThread::currentThread()->isInterruptionRequested())
    {
        QScreen * screen = QGuiApplication::primaryScreen();
        QPixmap screenShot = QPixmap();
        screenShot = screen->grabWindow(QApplication::desktop()->winId());
        screenShot = screenShot.scaled(QSize(1000,600),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        screenShot.save("./a.jpg");
        //delete screen;
        this->socket = new QUdpSocket;
        QFile file("./a.jpg");
        if (!file.open(QIODevice::ReadOnly))
                    return;
        char m_sendBuf[1024];

        int size = file.size();
        int num = 0;
        int count = 0;
        int endSize = size%996;
        if (endSize == 0) {
            num = size/996;
        }
        else {
            num = size/996+1;
        }
        while (count < num) {
            memset(m_sendBuf, 0, 1024);

            ImageFrameHead mes;
            mes.funCode = 24;
            mes.uTransFrameHdrSize = sizeof(ImageFrameHead);
            if ((count+1) != num) {
                mes.uTransFrameSize = 996;
            }
            else {
                mes.uTransFrameSize = endSize;
            }

            mes.uDataFrameSize = size;
            mes.uDataFrameTotal = num;
            mes.uDataFrameCurr = count+1;
            mes.uDataInFrameOffset = count*(1024 - sizeof(ImageFrameHead));
            memcpy(m_sendBuf, &mes, sizeof(ImageFrameHead));
            file.read(m_sendBuf+sizeof(ImageFrameHead), 1024-sizeof(ImageFrameHead));
            //qDebug()<<QString(m_sendBuf+sizeof(ImageFrameHead));

          // qDebug()<<QString(m_sendBuf+sizeof(ImageFrameHead));

           socket->writeDatagram(m_sendBuf, mes.uTransFrameSize+mes.uTransFrameHdrSize, QHostAddress("172.26.99.77"), 5648);
//            QTime dieTime = QTime::currentTime().addMSecs(1);
//            while( QTime::currentTime() < dieTime )
//                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            count++;
        }
        file.close();
        QThread::sleep(1);
//        QTime dieTime = QTime::currentTime().addMSecs(10);
//            while( QTime::currentTime() < dieTime )
//                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    this->socket->close();

}
MapThread::~MapThread()
{
    if(socket->isOpen())socket->close();
}

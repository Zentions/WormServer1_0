#ifndef MAPTHREAD_H
#define MAPTHREAD_H

#include <QThread>
#include <QUdpSocket>
#include <QTimer>
#include <QColor>
#include <QImage>
#include <QPixmap>
struct ImageFrameHead {
    int funCode;                        //功能码
    unsigned int uTransFrameHdrSize;    //sizeof(WIFI_FRAME_HEADER)
    unsigned int uTransFrameSize;       //sizeof(WIFI_FRAME_HEADER) + Data Size

    //数据帧变量
    unsigned int uDataFrameSize;        //数据帧的总大小
    unsigned int uDataFrameTotal;       //一帧数据被分成传输帧的个数
    unsigned int uDataFrameCurr;        //数据帧当前的帧号
    unsigned int uDataInFrameOffset;    //数据帧在整帧的偏移
};

class MapThread : public QThread
{
    Q_OBJECT

private:
    QUdpSocket *socket;
    QString ip;


public:
    MapThread(QString address, QObject *parent = 0);
    ~MapThread();
protected:
    void run();

public slots:
    void sendFrame();



};

#endif // MAPTHREAD_H

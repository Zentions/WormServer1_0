#ifndef CMDTHREAD_H
#define CMDTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "mapthread.h"
class CmdThread : public QObject
{
    Q_OBJECT

private:
    QTcpSocket*  cmdSocket;
    int   cmd_buf_fill;
    uchar cmd_buf[16];             //每条命令占16字节
    MapThread *mapThread;
public:
    explicit CmdThread(QTcpSocket* socket, QObject *parent = 0);
    ~CmdThread();
signals:

public slots:
    void newData();
    void newCommand();

    void cmdMouseMoveTo();
    void cmdMouseLeftDown();
    void cmdMouseLeftUp();
    void cmdMouseRightDown();
    void cmdMouseRightUp();
    void cmdMouseWheel();
    void cmdScreenSize();
    void cmdMouseDoubleClick();

    void cmdKeyPressed();
    void cmdKeyReleased();

};

#endif // CMDTHREAD_H

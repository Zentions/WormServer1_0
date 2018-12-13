#ifndef ALGO_H
#define ALGO_H

#include <QTcpSocket>

void writeAndBlock(QTcpSocket* socket, uchar* buf, int len);
void readAndBlock(QTcpSocket* socket, uchar* buf, int len);

int min(int, int);

#endif // ALGO_H

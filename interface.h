#ifndef INTERFACE_H
#define INTERFACE_H



#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QCursor>
#include <QPoint>


extern int screen_width;
extern int screen_height;


class Interface : public QObject
{
    Q_OBJECT
public:
    //static QPoint currentCursorPos;
    explicit Interface(QObject *parent = nullptr);
    static void mouseMoveTo(int x, int y);
    static void mouseLeftDown(int x = -1, int y = -1);
    static void mouseLeftUp(int x = -1, int y = -1);
    static void mouseRightDown(int x = -1, int y = -1);
    static void mouseRightUp(int x = -1, int y = -1);
    static void mouseWheel(int delta, int x = -1, int y = -1);

    static void keyPressed(uchar key);
    static void keyReleased(uchar key);
    static QPoint getCursorPos();
    static void setCursorPos(int, int);
    static QPixmap grapScreen();

    static QPoint transformCoordinate(QPoint);
};

#endif // INTERFACE_H

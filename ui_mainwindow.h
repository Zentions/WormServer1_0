/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *serverIPAddress;
    QLabel *label_2;
    QLineEdit *serverHostName;
    QPushButton *connectBtn;
    QPushButton *disconnectBtn;
    QPushButton *disconnectBtn_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(607, 324);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        serverIPAddress = new QLineEdit(centralWidget);
        serverIPAddress->setObjectName(QStringLiteral("serverIPAddress"));
        serverIPAddress->setGeometry(QRect(160, 60, 141, 21));
        serverIPAddress->setReadOnly(true);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 60, 41, 21));
        serverHostName = new QLineEdit(centralWidget);
        serverHostName->setObjectName(QStringLiteral("serverHostName"));
        serverHostName->setGeometry(QRect(330, 60, 141, 21));
        serverHostName->setReadOnly(true);
        connectBtn = new QPushButton(centralWidget);
        connectBtn->setObjectName(QStringLiteral("connectBtn"));
        connectBtn->setGeometry(QRect(90, 120, 111, 41));
        disconnectBtn = new QPushButton(centralWidget);
        disconnectBtn->setObjectName(QStringLiteral("disconnectBtn"));
        disconnectBtn->setGeometry(QRect(230, 120, 121, 41));
        disconnectBtn_2 = new QPushButton(centralWidget);
        disconnectBtn_2->setObjectName(QStringLiteral("disconnectBtn_2"));
        disconnectBtn_2->setGeometry(QRect(370, 120, 121, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 607, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        serverIPAddress->setText(QApplication::translate("MainWindow", "IP Address", 0));
        label_2->setText(QApplication::translate("MainWindow", "\346\234\254\346\234\272IP", 0));
        serverHostName->setText(QApplication::translate("MainWindow", "Host Name", 0));
        connectBtn->setText(QApplication::translate("MainWindow", "\345\220\257\347\224\250", 0));
        disconnectBtn->setText(QApplication::translate("MainWindow", "\345\201\234\347\224\250", 0));
        disconnectBtn_2->setText(QApplication::translate("MainWindow", "\347\256\241\347\220\206\345\205\261\344\272\253\345\272\224\347\224\250", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

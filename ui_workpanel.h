/********************************************************************************
** Form generated from reading UI file 'workpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKPANEL_H
#define UI_WORKPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WorkPanel
{
public:
    QListWidget *listWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *WorkPanel)
    {
        if (WorkPanel->objectName().isEmpty())
            WorkPanel->setObjectName(QStringLiteral("WorkPanel"));
        WorkPanel->resize(518, 413);
        listWidget = new QListWidget(WorkPanel);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(30, 30, 451, 311));
        listWidget->setStyleSheet(QStringLiteral("alternate-background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.1 rgba(255, 255, 255, 255), stop:0.2 rgba(255, 176, 176, 167), stop:0.3 rgba(255, 151, 151, 92), stop:0.4 rgba(255, 125, 125, 51), stop:0.5 rgba(255, 76, 76, 205), stop:0.52 rgba(255, 76, 76, 205), stop:0.6 rgba(255, 180, 180, 84), stop:1 rgba(255, 255, 255, 0));"));
        pushButton = new QPushButton(WorkPanel);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(200, 360, 75, 31));

        retranslateUi(WorkPanel);

        QMetaObject::connectSlotsByName(WorkPanel);
    } // setupUi

    void retranslateUi(QDialog *WorkPanel)
    {
        WorkPanel->setWindowTitle(QApplication::translate("WorkPanel", "Dialog", 0));
        pushButton->setText(QApplication::translate("WorkPanel", "\345\220\257\345\212\250", 0));
    } // retranslateUi

};

namespace Ui {
    class WorkPanel: public Ui_WorkPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKPANEL_H

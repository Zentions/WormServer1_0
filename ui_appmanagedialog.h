/********************************************************************************
** Form generated from reading UI file 'appmanagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPMANAGEDIALOG_H
#define UI_APPMANAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_AppManageDialog
{
public:
    QTreeWidget *treeWidget;
    QPushButton *addButton;
    QLineEdit *nameEdit;
    QLineEdit *pathEdit;
    QPushButton *delButton;
    QPushButton *addButton_2;

    void setupUi(QDialog *AppManageDialog)
    {
        if (AppManageDialog->objectName().isEmpty())
            AppManageDialog->setObjectName(QStringLiteral("AppManageDialog"));
        AppManageDialog->resize(731, 438);
        treeWidget = new QTreeWidget(AppManageDialog);
        treeWidget->headerItem()->setText(1, QString());
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(40, 20, 651, 331));
        addButton = new QPushButton(AppManageDialog);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setGeometry(QRect(460, 380, 61, 31));
        nameEdit = new QLineEdit(AppManageDialog);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));
        nameEdit->setGeometry(QRect(40, 380, 141, 31));
        pathEdit = new QLineEdit(AppManageDialog);
        pathEdit->setObjectName(QStringLiteral("pathEdit"));
        pathEdit->setGeometry(QRect(190, 380, 261, 31));
        delButton = new QPushButton(AppManageDialog);
        delButton->setObjectName(QStringLiteral("delButton"));
        delButton->setGeometry(QRect(540, 380, 71, 31));
        addButton_2 = new QPushButton(AppManageDialog);
        addButton_2->setObjectName(QStringLiteral("addButton_2"));
        addButton_2->setGeometry(QRect(630, 380, 61, 31));

        retranslateUi(AppManageDialog);

        QMetaObject::connectSlotsByName(AppManageDialog);
    } // setupUi

    void retranslateUi(QDialog *AppManageDialog)
    {
        AppManageDialog->setWindowTitle(QApplication::translate("AppManageDialog", "Dialog", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("AppManageDialog", "\345\210\206\344\272\253\345\272\224\347\224\250\345\210\227\350\241\250", 0));
        addButton->setText(QApplication::translate("AppManageDialog", "\346\267\273\345\212\240\345\272\224\347\224\250", 0));
        delButton->setText(QApplication::translate("AppManageDialog", "\345\210\240\351\231\244\345\272\224\347\224\250", 0));
        addButton_2->setText(QApplication::translate("AppManageDialog", "\345\220\257\345\212\250\345\272\224\347\224\250", 0));
    } // retranslateUi

};

namespace Ui {
    class AppManageDialog: public Ui_AppManageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPMANAGEDIALOG_H

/********************************************************************************
** Form generated from reading UI file 'AboutDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QLabel *labelAbout;
    QPushButton *buttonBoxOk;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QString::fromUtf8("AboutDialog"));
        AboutDialog->resize(400, 300);
        labelAbout = new QLabel(AboutDialog);
        labelAbout->setObjectName(QString::fromUtf8("labelAbout"));
        labelAbout->setGeometry(QRect(120, 20, 201, 161));
        buttonBoxOk = new QPushButton(AboutDialog);
        buttonBoxOk->setObjectName(QString::fromUtf8("buttonBoxOk"));
        buttonBoxOk->setGeometry(QRect(150, 260, 80, 24));

        retranslateUi(AboutDialog);

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QCoreApplication::translate("AboutDialog", "Dialog", nullptr));
        labelAbout->setText(QCoreApplication::translate("AboutDialog", "<html><head/><body><p><span style=\" font-weight:600;\">Galaxy Calculator</span></p><p>Written by <span style=\" font-style:italic;\">Jeffrey Scott Flesher</span></p></body></html>", nullptr));
        buttonBoxOk->setText(QCoreApplication::translate("AboutDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H

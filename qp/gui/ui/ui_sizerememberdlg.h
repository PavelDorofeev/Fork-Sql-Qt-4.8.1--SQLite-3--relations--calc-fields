/********************************************************************************
** Form generated from reading UI file 'sizerememberdlg.ui'
**
** Created: Mon 14. Jul 18:10:45 2025
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIZEREMEMBERDLG_H
#define UI_SIZEREMEMBERDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SizeRememberDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *SizeRememberDlg)
    {
        if (SizeRememberDlg->objectName().isEmpty())
            SizeRememberDlg->setObjectName(QString::fromUtf8("SizeRememberDlg"));
        SizeRememberDlg->resize(480, 640);
        horizontalLayout = new QHBoxLayout(SizeRememberDlg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(SizeRememberDlg);

        QMetaObject::connectSlotsByName(SizeRememberDlg);
    } // setupUi

    void retranslateUi(QDialog *SizeRememberDlg)
    {
        SizeRememberDlg->setWindowTitle(QApplication::translate("SizeRememberDlg", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SizeRememberDlg: public Ui_SizeRememberDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIZEREMEMBERDLG_H

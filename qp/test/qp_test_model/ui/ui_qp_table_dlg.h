/********************************************************************************
** Form generated from reading UI file 'qp_table_dlg.ui'
**
** Created: Tue 1. Jul 11:55:31 2025
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QP_TABLE_DLG_H
#define UI_QP_TABLE_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QpTableDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *dialogTopFrame;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *for_table_lo;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_close;

    void setupUi(QDialog *QpTableDlg)
    {
        if (QpTableDlg->objectName().isEmpty())
            QpTableDlg->setObjectName(QString::fromUtf8("QpTableDlg"));
        QpTableDlg->resize(744, 444);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QpTableDlg->sizePolicy().hasHeightForWidth());
        QpTableDlg->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(QpTableDlg);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        dialogTopFrame = new QFrame(QpTableDlg);
        dialogTopFrame->setObjectName(QString::fromUtf8("dialogTopFrame"));
        verticalLayout = new QVBoxLayout(dialogTopFrame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        for_table_lo = new QVBoxLayout();
        for_table_lo->setObjectName(QString::fromUtf8("for_table_lo"));

        verticalLayout->addLayout(for_table_lo);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_close = new QPushButton(dialogTopFrame);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setAutoDefault(false);

        horizontalLayout->addWidget(btn_close);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        verticalLayout_2->addWidget(dialogTopFrame);


        retranslateUi(QpTableDlg);

        QMetaObject::connectSlotsByName(QpTableDlg);
    } // setupUi

    void retranslateUi(QDialog *QpTableDlg)
    {
        QpTableDlg->setWindowTitle(QApplication::translate("QpTableDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        btn_close->setText(QApplication::translate("QpTableDlg", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QpTableDlg: public Ui_QpTableDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QP_TABLE_DLG_H

/********************************************************************************
** Form generated from reading UI file 'table_dlg.ui'
**
** Created: Mon 19. Dec 13:07:12 2022
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLE_DLG_H
#define UI_TABLE_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Table_Dlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *for_table_lo;

    void setupUi(QDialog *Table_Dlg)
    {
        if (Table_Dlg->objectName().isEmpty())
            Table_Dlg->setObjectName(QString::fromUtf8("Table_Dlg"));
        Table_Dlg->resize(503, 334);
        verticalLayout_2 = new QVBoxLayout(Table_Dlg);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        for_table_lo = new QVBoxLayout();
        for_table_lo->setContentsMargins(10, 10, 10, 10);
        for_table_lo->setObjectName(QString::fromUtf8("for_table_lo"));

        verticalLayout_2->addLayout(for_table_lo);


        retranslateUi(Table_Dlg);

        QMetaObject::connectSlotsByName(Table_Dlg);
    } // setupUi

    void retranslateUi(QDialog *Table_Dlg)
    {
        Table_Dlg->setWindowTitle(QApplication::translate("Table_Dlg", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Table_Dlg: public Ui_Table_Dlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLE_DLG_H

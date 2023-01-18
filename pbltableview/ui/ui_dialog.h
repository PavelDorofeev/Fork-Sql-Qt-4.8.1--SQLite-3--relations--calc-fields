/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Mon 19. Dec 12:41:29 2022
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *mainLo;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *cmb_Language;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QToolButton *btn_goods;
    QToolButton *btn_checks;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_logView;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *tableViewLO;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_save;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btn_Close;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(525, 532);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mainLo = new QVBoxLayout();
        mainLo->setSpacing(6);
        mainLo->setContentsMargins(10, 10, 10, 10);
        mainLo->setObjectName(QString::fromUtf8("mainLo"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cmb_Language = new QComboBox(Dialog);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/img/countries/english-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmb_Language->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/img/countries/russian-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmb_Language->addItem(icon1, QString());
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/img/countries/china-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmb_Language->addItem(icon2, QString());
        cmb_Language->setObjectName(QString::fromUtf8("cmb_Language"));

        horizontalLayout_3->addWidget(cmb_Language);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        mainLo->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_goods = new QToolButton(Dialog);
        btn_goods->setObjectName(QString::fromUtf8("btn_goods"));

        horizontalLayout->addWidget(btn_goods);

        btn_checks = new QToolButton(Dialog);
        btn_checks->setObjectName(QString::fromUtf8("btn_checks"));

        horizontalLayout->addWidget(btn_checks);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_logView = new QPushButton(Dialog);
        btn_logView->setObjectName(QString::fromUtf8("btn_logView"));
        btn_logView->setAutoDefault(false);

        horizontalLayout->addWidget(btn_logView);


        mainLo->addLayout(horizontalLayout);

        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableViewLO = new QVBoxLayout();
        tableViewLO->setSpacing(6);
        tableViewLO->setContentsMargins(10, 10, 10, 10);
        tableViewLO->setObjectName(QString::fromUtf8("tableViewLO"));

        verticalLayout_2->addLayout(tableViewLO);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btn_save = new QPushButton(groupBox);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setAutoDefault(false);

        horizontalLayout_2->addWidget(btn_save);


        verticalLayout_2->addLayout(horizontalLayout_2);


        mainLo->addWidget(groupBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btn_Close = new QPushButton(Dialog);
        btn_Close->setObjectName(QString::fromUtf8("btn_Close"));
        btn_Close->setAutoDefault(false);

        horizontalLayout_4->addWidget(btn_Close);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        mainLo->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(mainLo);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Test fork PblSqlRelationalTableModel", 0, QApplication::UnicodeUTF8));
        cmb_Language->setItemText(0, QApplication::translate("Dialog", "en", 0, QApplication::UnicodeUTF8));
        cmb_Language->setItemText(1, QApplication::translate("Dialog", "ru", 0, QApplication::UnicodeUTF8));
        cmb_Language->setItemText(2, QApplication::translate("Dialog", "zh", 0, QApplication::UnicodeUTF8));

        btn_goods->setText(QApplication::translate("Dialog", "goods", 0, QApplication::UnicodeUTF8));
        btn_checks->setText(QApplication::translate("Dialog", "checks", 0, QApplication::UnicodeUTF8));
        btn_logView->setText(QApplication::translate("Dialog", "view log", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Dialog", "document", 0, QApplication::UnicodeUTF8));
        btn_save->setText(QApplication::translate("Dialog", "SAVE", 0, QApplication::UnicodeUTF8));
        btn_Close->setText(QApplication::translate("Dialog", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H

/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Tue 1. Jul 11:56:55 2025
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
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
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
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btn_test;
    QPushButton *btn_goods;
    QPushButton *btn_checks;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_font;
    QPushButton *btn_logView;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *tableViewLO;
    QHBoxLayout *horizontalLayout_5;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *lbl_sum;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btn_save;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btn_Close;
    QPushButton *btn_resizeColumnsToContents;
    QPushButton *btn_resizeRowsToContents;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(803, 387);
        Dialog->setMinimumSize(QSize(803, 387));
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mainLo = new QVBoxLayout();
        mainLo->setSpacing(6);
        mainLo->setObjectName(QString::fromUtf8("mainLo"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cmb_Language = new QComboBox(Dialog);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/view/img/countries/english-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmb_Language->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/view/img/countries/russian-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmb_Language->addItem(icon1, QString());
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/view/img/countries/china-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmb_Language->addItem(icon2, QString());
        cmb_Language->setObjectName(QString::fromUtf8("cmb_Language"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmb_Language->sizePolicy().hasHeightForWidth());
        cmb_Language->setSizePolicy(sizePolicy);
        cmb_Language->setMaxCount(10);
        cmb_Language->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_3->addWidget(cmb_Language);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_2);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        btn_test = new QPushButton(groupBox_2);
        btn_test->setObjectName(QString::fromUtf8("btn_test"));
        btn_test->setAutoDefault(false);

        horizontalLayout_6->addWidget(btn_test);

        btn_goods = new QPushButton(groupBox_2);
        btn_goods->setObjectName(QString::fromUtf8("btn_goods"));
        btn_goods->setAutoDefault(false);

        horizontalLayout_6->addWidget(btn_goods);

        btn_checks = new QPushButton(groupBox_2);
        btn_checks->setObjectName(QString::fromUtf8("btn_checks"));
        btn_checks->setAutoDefault(false);

        horizontalLayout_6->addWidget(btn_checks);


        horizontalLayout_3->addWidget(groupBox_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        btn_font = new QPushButton(Dialog);
        btn_font->setObjectName(QString::fromUtf8("btn_font"));
        btn_font->setAutoDefault(false);

        horizontalLayout_3->addWidget(btn_font);

        btn_logView = new QPushButton(Dialog);
        btn_logView->setObjectName(QString::fromUtf8("btn_logView"));
        btn_logView->setAutoDefault(false);

        horizontalLayout_3->addWidget(btn_logView);


        mainLo->addLayout(horizontalLayout_3);

        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableViewLO = new QVBoxLayout();
        tableViewLO->setSpacing(6);
        tableViewLO->setObjectName(QString::fromUtf8("tableViewLO"));

        verticalLayout_2->addLayout(tableViewLO);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lbl_sum = new QLabel(groupBox);
        lbl_sum->setObjectName(QString::fromUtf8("lbl_sum"));
        lbl_sum->setMidLineWidth(0);

        formLayout->setWidget(0, QFormLayout::FieldRole, lbl_sum);


        horizontalLayout_5->addLayout(formLayout);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        btn_save = new QPushButton(groupBox);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setAutoDefault(false);

        horizontalLayout_5->addWidget(btn_save);


        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalLayout_2->setStretch(0, 1);

        mainLo->addWidget(groupBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btn_Close = new QPushButton(Dialog);
        btn_Close->setObjectName(QString::fromUtf8("btn_Close"));
        btn_Close->setAutoDefault(false);

        horizontalLayout_4->addWidget(btn_Close);

        btn_resizeColumnsToContents = new QPushButton(Dialog);
        btn_resizeColumnsToContents->setObjectName(QString::fromUtf8("btn_resizeColumnsToContents"));
        btn_resizeColumnsToContents->setAutoDefault(false);

        horizontalLayout_4->addWidget(btn_resizeColumnsToContents);

        btn_resizeRowsToContents = new QPushButton(Dialog);
        btn_resizeRowsToContents->setObjectName(QString::fromUtf8("btn_resizeRowsToContents"));
        btn_resizeRowsToContents->setAutoDefault(false);

        horizontalLayout_4->addWidget(btn_resizeRowsToContents);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        mainLo->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(mainLo);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Test QpSqlTableModel ", 0, QApplication::UnicodeUTF8));
        cmb_Language->setItemText(0, QApplication::translate("Dialog", "en", 0, QApplication::UnicodeUTF8));
        cmb_Language->setItemText(1, QApplication::translate("Dialog", "ru", 0, QApplication::UnicodeUTF8));
        cmb_Language->setItemText(2, QApplication::translate("Dialog", "zh", 0, QApplication::UnicodeUTF8));

        groupBox_2->setTitle(QApplication::translate("Dialog", "books", 0, QApplication::UnicodeUTF8));
        btn_test->setText(QApplication::translate("Dialog", "test", 0, QApplication::UnicodeUTF8));
        btn_goods->setText(QApplication::translate("Dialog", "goods", 0, QApplication::UnicodeUTF8));
        btn_checks->setText(QApplication::translate("Dialog", "checks", 0, QApplication::UnicodeUTF8));
        btn_font->setText(QApplication::translate("Dialog", "font size", 0, QApplication::UnicodeUTF8));
        btn_logView->setText(QApplication::translate("Dialog", "view log", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Dialog", "document", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "Sum", 0, QApplication::UnicodeUTF8));
        lbl_sum->setText(QApplication::translate("Dialog", "...", 0, QApplication::UnicodeUTF8));
        btn_save->setText(QApplication::translate("Dialog", "SAVE DOCUMENT", 0, QApplication::UnicodeUTF8));
        btn_Close->setText(QApplication::translate("Dialog", "Close App", 0, QApplication::UnicodeUTF8));
        btn_resizeColumnsToContents->setText(QApplication::translate("Dialog", "resizeColumnsToContents", 0, QApplication::UnicodeUTF8));
        btn_resizeRowsToContents->setText(QApplication::translate("Dialog", "resizeRowsToContents", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H

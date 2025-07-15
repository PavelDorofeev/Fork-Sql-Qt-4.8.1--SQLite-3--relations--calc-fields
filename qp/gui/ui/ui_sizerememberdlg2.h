/********************************************************************************
** Form generated from reading UI file 'sizerememberdlg2.ui'
**
** Created: Mon 14. Jul 18:10:45 2025
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIZEREMEMBERDLG2_H
#define UI_SIZEREMEMBERDLG2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SizeRememberDlg2
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame11;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton;
    QCheckBox *checkBox;
    QPushButton *pushButton;

    void setupUi(QDialog *SizeRememberDlg2)
    {
        if (SizeRememberDlg2->objectName().isEmpty())
            SizeRememberDlg2->setObjectName(QString::fromUtf8("SizeRememberDlg2"));
        SizeRememberDlg2->resize(443, 377);
        SizeRememberDlg2->setMinimumSize(QSize(443, 377));
        SizeRememberDlg2->setSizeGripEnabled(true);
        verticalLayout = new QVBoxLayout(SizeRememberDlg2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame11 = new QFrame(SizeRememberDlg2);
        frame11->setObjectName(QString::fromUtf8("frame11"));
        frame11->setAutoFillBackground(false);
        frame11->setStyleSheet(QString::fromUtf8("background-color: rgb(165, 183, 238);"));
        verticalLayout_2 = new QVBoxLayout(frame11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        radioButton = new QRadioButton(frame11);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout_3->addWidget(radioButton);

        checkBox = new QCheckBox(frame11);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout_3->addWidget(checkBox);

        pushButton = new QPushButton(frame11);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_3->addWidget(pushButton);


        verticalLayout_2->addLayout(verticalLayout_3);


        verticalLayout->addWidget(frame11);


        retranslateUi(SizeRememberDlg2);

        QMetaObject::connectSlotsByName(SizeRememberDlg2);
    } // setupUi

    void retranslateUi(QDialog *SizeRememberDlg2)
    {
        SizeRememberDlg2->setWindowTitle(QApplication::translate("SizeRememberDlg2", "Dialog", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("SizeRememberDlg2", "RadioButton", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("SizeRememberDlg2", "CheckBox", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("SizeRememberDlg2", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SizeRememberDlg2: public Ui_SizeRememberDlg2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIZEREMEMBERDLG2_H

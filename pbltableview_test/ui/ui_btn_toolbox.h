/********************************************************************************
** Form generated from reading UI file 'btn_toolbox.ui'
**
** Created: Mon 19. Dec 13:07:12 2022
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BTN_TOOLBOX_H
#define UI_BTN_TOOLBOX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Btn_ToolBox
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *btn_insert;
    QToolButton *btn_copy;
    QToolButton *btn_edit;
    QToolButton *btn_delete;
    QLineEdit *ledt_filter;
    QToolButton *btn_searchInTable;
    QToolButton *btn_find;
    QToolButton *btn_selectByValue;
    QToolButton *btn_sortEnabled;
    QComboBox *cmb_Strategy;
    QPushButton *btn_submitAll;
    QCheckBox *chk_editable;
    QCheckBox *chk_exColumnsVisible;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *Btn_ToolBox)
    {
        if (Btn_ToolBox->objectName().isEmpty())
            Btn_ToolBox->setObjectName(QString::fromUtf8("Btn_ToolBox"));
        Btn_ToolBox->resize(863, 42);
        horizontalLayout_2 = new QHBoxLayout(Btn_ToolBox);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        btn_insert = new QToolButton(Btn_ToolBox);
        btn_insert->setObjectName(QString::fromUtf8("btn_insert"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/img/btn-db/insert-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_insert->setIcon(icon);
        btn_insert->setAutoRaise(false);

        horizontalLayout->addWidget(btn_insert);

        btn_copy = new QToolButton(Btn_ToolBox);
        btn_copy->setObjectName(QString::fromUtf8("btn_copy"));
        btn_copy->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/img/btn-db/copy-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_copy->setIcon(icon1);
        btn_copy->setCheckable(false);
        btn_copy->setAutoRepeatInterval(100);

        horizontalLayout->addWidget(btn_copy);

        btn_edit = new QToolButton(Btn_ToolBox);
        btn_edit->setObjectName(QString::fromUtf8("btn_edit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/img/btn-db/edit-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_edit->setIcon(icon2);

        horizontalLayout->addWidget(btn_edit);

        btn_delete = new QToolButton(Btn_ToolBox);
        btn_delete->setObjectName(QString::fromUtf8("btn_delete"));
        btn_delete->setStyleSheet(QString::fromUtf8(""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/img/btn-db/delete-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_delete->setIcon(icon3);
        btn_delete->setCheckable(false);
        btn_delete->setAutoRepeatInterval(100);

        horizontalLayout->addWidget(btn_delete);

        ledt_filter = new QLineEdit(Btn_ToolBox);
        ledt_filter->setObjectName(QString::fromUtf8("ledt_filter"));

        horizontalLayout->addWidget(ledt_filter);

        btn_searchInTable = new QToolButton(Btn_ToolBox);
        btn_searchInTable->setObjectName(QString::fromUtf8("btn_searchInTable"));
        btn_searchInTable->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/img/btn-db/text-find-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/icon/img/btn-db/text-find-100x100-disabled.png"), QSize(), QIcon::Disabled, QIcon::On);
        btn_searchInTable->setIcon(icon4);

        horizontalLayout->addWidget(btn_searchInTable);

        btn_find = new QToolButton(Btn_ToolBox);
        btn_find->setObjectName(QString::fromUtf8("btn_find"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/img/btn-db/find-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_find->setIcon(icon5);

        horizontalLayout->addWidget(btn_find);

        btn_selectByValue = new QToolButton(Btn_ToolBox);
        btn_selectByValue->setObjectName(QString::fromUtf8("btn_selectByValue"));
        btn_selectByValue->setEnabled(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/img/btn-db/select-by-value-1-100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/icon/img/btn-db/select-by-value-2-100x100.png"), QSize(), QIcon::Normal, QIcon::On);
        btn_selectByValue->setIcon(icon6);
        btn_selectByValue->setCheckable(true);
        btn_selectByValue->setPopupMode(QToolButton::DelayedPopup);
        btn_selectByValue->setAutoRaise(true);
        btn_selectByValue->setArrowType(Qt::NoArrow);

        horizontalLayout->addWidget(btn_selectByValue);

        btn_sortEnabled = new QToolButton(Btn_ToolBox);
        btn_sortEnabled->setObjectName(QString::fromUtf8("btn_sortEnabled"));
        btn_sortEnabled->setEnabled(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/img/btn-db/sort-100x100-disabled.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/icon/img/btn-db/sort-100x100.png"), QSize(), QIcon::Normal, QIcon::On);
        btn_sortEnabled->setIcon(icon7);
        btn_sortEnabled->setCheckable(true);
        btn_sortEnabled->setChecked(false);
        btn_sortEnabled->setAutoRaise(true);

        horizontalLayout->addWidget(btn_sortEnabled);

        cmb_Strategy = new QComboBox(Btn_ToolBox);
        cmb_Strategy->setObjectName(QString::fromUtf8("cmb_Strategy"));

        horizontalLayout->addWidget(cmb_Strategy);

        btn_submitAll = new QPushButton(Btn_ToolBox);
        btn_submitAll->setObjectName(QString::fromUtf8("btn_submitAll"));

        horizontalLayout->addWidget(btn_submitAll);

        chk_editable = new QCheckBox(Btn_ToolBox);
        chk_editable->setObjectName(QString::fromUtf8("chk_editable"));

        horizontalLayout->addWidget(chk_editable);

        chk_exColumnsVisible = new QCheckBox(Btn_ToolBox);
        chk_exColumnsVisible->setObjectName(QString::fromUtf8("chk_exColumnsVisible"));

        horizontalLayout->addWidget(chk_exColumnsVisible);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Btn_ToolBox);

        QMetaObject::connectSlotsByName(Btn_ToolBox);
    } // setupUi

    void retranslateUi(QWidget *Btn_ToolBox)
    {
        Btn_ToolBox->setWindowTitle(QApplication::translate("Btn_ToolBox", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_insert->setToolTip(QApplication::translate("Btn_ToolBox", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.5pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; color:#049027;\">insert row [INS]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_insert->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_copy->setToolTip(QApplication::translate("Btn_ToolBox", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.5pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; color:#ffaa00;\">copy row [F9]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_copy->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_edit->setToolTip(QApplication::translate("Btn_ToolBox", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.5pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; color:#0000ff;\">edit row [F4]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_edit->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_delete->setToolTip(QApplication::translate("Btn_ToolBox", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.5pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; color:#ff0000;\">remove row [DEL]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_delete->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ledt_filter->setToolTip(QApplication::translate("Btn_ToolBox", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.5pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; color:#3b3b3b;\">press any symbols for searching add last press [ENTER] key</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ledt_filter->setPlaceholderText(QString());
        btn_searchInTable->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
        btn_find->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
        btn_selectByValue->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
        btn_sortEnabled->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
        cmb_Strategy->clear();
        cmb_Strategy->insertItems(0, QStringList()
         << QApplication::translate("Btn_ToolBox", "OnFieldChange", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Btn_ToolBox", "OnRowChange", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Btn_ToolBox", "OnManulaSubmit", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        cmb_Strategy->setToolTip(QApplication::translate("Btn_ToolBox", "select edit strategy", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_submitAll->setText(QApplication::translate("Btn_ToolBox", "submitAll", 0, QApplication::UnicodeUTF8));
        chk_editable->setText(QApplication::translate("Btn_ToolBox", "edit", 0, QApplication::UnicodeUTF8));
        chk_exColumnsVisible->setText(QApplication::translate("Btn_ToolBox", "show rel id columns", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Btn_ToolBox: public Ui_Btn_ToolBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BTN_TOOLBOX_H

/********************************************************************************
** Form generated from reading UI file 'btn_toolbox.ui'
**
** Created: Tue 1. Jul 11:05:59 2025
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
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include "qp/sql/view/buttoniconautoresize.h"

QT_BEGIN_NAMESPACE

class Ui_Btn_ToolBox
{
public:
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *chk_editable;
    ButtonIconAutoResize *btn_insert;
    ButtonIconAutoResize *btn_copy;
    ButtonIconAutoResize *btn_edit;
    ButtonIconAutoResize *btn_delete;
    ButtonIconAutoResize *btn_view;
    QWidget *wgt_search_block;
    QHBoxLayout *wgt_search;
    QFrame *LineEdit;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *ledt_filter;
    QToolButton *btn_clear_seached_text;
    ButtonIconAutoResize *btn_search_settings;
    ButtonIconAutoResize *btn_selectByValue;
    ButtonIconAutoResize *btn_sortEnabled;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *cmb_Strategy;
    QPushButton *btn_submitAll;
    QCheckBox *chk_showRelExColumns;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *Btn_ToolBox)
    {
        if (Btn_ToolBox->objectName().isEmpty())
            Btn_ToolBox->setObjectName(QString::fromUtf8("Btn_ToolBox"));
        Btn_ToolBox->resize(991, 62);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Btn_ToolBox->sizePolicy().hasHeightForWidth());
        Btn_ToolBox->setSizePolicy(sizePolicy);
        Btn_ToolBox->setInputMethodHints(Qt::ImhHiddenText);
        horizontalLayout = new QHBoxLayout(Btn_ToolBox);
        horizontalLayout->setContentsMargins(7, 7, 7, 7);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_3->setContentsMargins(10, 2, 10, 2);
        chk_editable = new QCheckBox(Btn_ToolBox);
        chk_editable->setObjectName(QString::fromUtf8("chk_editable"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(chk_editable->sizePolicy().hasHeightForWidth());
        chk_editable->setSizePolicy(sizePolicy1);
        chk_editable->setIconSize(QSize(10, 10));
        chk_editable->setChecked(false);

        horizontalLayout_3->addWidget(chk_editable);

        btn_insert = new ButtonIconAutoResize(Btn_ToolBox);
        btn_insert->setObjectName(QString::fromUtf8("btn_insert"));
        btn_insert->setEnabled(false);
        sizePolicy1.setHeightForWidth(btn_insert->sizePolicy().hasHeightForWidth());
        btn_insert->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/view/img/btn-db/insert.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btn_insert->setIcon(icon);
        btn_insert->setAutoRaise(false);

        horizontalLayout_3->addWidget(btn_insert);

        btn_copy = new ButtonIconAutoResize(Btn_ToolBox);
        btn_copy->setObjectName(QString::fromUtf8("btn_copy"));
        btn_copy->setEnabled(false);
        sizePolicy1.setHeightForWidth(btn_copy->sizePolicy().hasHeightForWidth());
        btn_copy->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/view/img/btn-db/copy.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btn_copy->setIcon(icon1);
        btn_copy->setCheckable(false);
        btn_copy->setAutoRepeatInterval(100);

        horizontalLayout_3->addWidget(btn_copy);

        btn_edit = new ButtonIconAutoResize(Btn_ToolBox);
        btn_edit->setObjectName(QString::fromUtf8("btn_edit"));
        btn_edit->setEnabled(false);
        sizePolicy1.setHeightForWidth(btn_edit->sizePolicy().hasHeightForWidth());
        btn_edit->setSizePolicy(sizePolicy1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/view/img/btn-db/edit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btn_edit->setIcon(icon2);

        horizontalLayout_3->addWidget(btn_edit);

        btn_delete = new ButtonIconAutoResize(Btn_ToolBox);
        btn_delete->setObjectName(QString::fromUtf8("btn_delete"));
        btn_delete->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_delete->sizePolicy().hasHeightForWidth());
        btn_delete->setSizePolicy(sizePolicy2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/view/img/btn-db/remove.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btn_delete->setIcon(icon3);
        btn_delete->setCheckable(false);
        btn_delete->setAutoRepeatInterval(100);

        horizontalLayout_3->addWidget(btn_delete);

        btn_view = new ButtonIconAutoResize(Btn_ToolBox);
        btn_view->setObjectName(QString::fromUtf8("btn_view"));
        sizePolicy2.setHeightForWidth(btn_view->sizePolicy().hasHeightForWidth());
        btn_view->setSizePolicy(sizePolicy2);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/view/img/btn-db/view.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btn_view->setIcon(icon4);

        horizontalLayout_3->addWidget(btn_view);


        horizontalLayout->addLayout(horizontalLayout_3);

        wgt_search_block = new QWidget(Btn_ToolBox);
        wgt_search_block->setObjectName(QString::fromUtf8("wgt_search_block"));
        wgt_search = new QHBoxLayout(wgt_search_block);
        wgt_search->setObjectName(QString::fromUtf8("wgt_search"));
        LineEdit = new QFrame(wgt_search_block);
        LineEdit->setObjectName(QString::fromUtf8("LineEdit"));
        LineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        LineEdit->setFrameShape(QFrame::Box);
        LineEdit->setFrameShadow(QFrame::Plain);
        horizontalLayout_10 = new QHBoxLayout(LineEdit);
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        ledt_filter = new QLineEdit(LineEdit);
        ledt_filter->setObjectName(QString::fromUtf8("ledt_filter"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ledt_filter->sizePolicy().hasHeightForWidth());
        ledt_filter->setSizePolicy(sizePolicy3);
#ifndef QT_NO_TOOLTIP
        ledt_filter->setToolTip(QString::fromUtf8(""));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        ledt_filter->setStatusTip(QString::fromUtf8(""));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        ledt_filter->setWhatsThis(QString::fromUtf8(""));
#endif // QT_NO_WHATSTHIS
        ledt_filter->setStyleSheet(QString::fromUtf8(""));
        ledt_filter->setInputMask(QString::fromUtf8(""));
        ledt_filter->setText(QString::fromUtf8(""));
        ledt_filter->setMaxLength(50);
        ledt_filter->setFrame(false);

        horizontalLayout_10->addWidget(ledt_filter);

        btn_clear_seached_text = new QToolButton(LineEdit);
        btn_clear_seached_text->setObjectName(QString::fromUtf8("btn_clear_seached_text"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btn_clear_seached_text->sizePolicy().hasHeightForWidth());
        btn_clear_seached_text->setSizePolicy(sizePolicy4);
        btn_clear_seached_text->setAutoFillBackground(false);
        btn_clear_seached_text->setText(QString::fromUtf8("\321\205"));
        btn_clear_seached_text->setIconSize(QSize(30, 30));
        btn_clear_seached_text->setShortcut(QString::fromUtf8(""));
        btn_clear_seached_text->setPopupMode(QToolButton::DelayedPopup);
        btn_clear_seached_text->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btn_clear_seached_text->setAutoRaise(true);
        btn_clear_seached_text->setArrowType(Qt::NoArrow);

        horizontalLayout_10->addWidget(btn_clear_seached_text);

        horizontalLayout_10->setStretch(0, 1);

        wgt_search->addWidget(LineEdit);

        btn_search_settings = new ButtonIconAutoResize(wgt_search_block);
        btn_search_settings->setObjectName(QString::fromUtf8("btn_search_settings"));
        sizePolicy2.setHeightForWidth(btn_search_settings->sizePolicy().hasHeightForWidth());
        btn_search_settings->setSizePolicy(sizePolicy2);
#ifndef QT_NO_STATUSTIP
        btn_search_settings->setStatusTip(QString::fromUtf8(""));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btn_search_settings->setWhatsThis(QString::fromUtf8(""));
#endif // QT_NO_WHATSTHIS
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/view/img/btn-db/search.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btn_search_settings->setIcon(icon5);

        wgt_search->addWidget(btn_search_settings);


        horizontalLayout->addWidget(wgt_search_block);

        btn_selectByValue = new ButtonIconAutoResize(Btn_ToolBox);
        btn_selectByValue->setObjectName(QString::fromUtf8("btn_selectByValue"));
        btn_selectByValue->setEnabled(true);
        sizePolicy2.setHeightForWidth(btn_selectByValue->sizePolicy().hasHeightForWidth());
        btn_selectByValue->setSizePolicy(sizePolicy2);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/view/img/btn-db/search-settings.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btn_selectByValue->setIcon(icon6);
        btn_selectByValue->setCheckable(true);
        btn_selectByValue->setChecked(false);
        btn_selectByValue->setPopupMode(QToolButton::DelayedPopup);
        btn_selectByValue->setAutoRaise(true);
        btn_selectByValue->setArrowType(Qt::NoArrow);

        horizontalLayout->addWidget(btn_selectByValue);

        btn_sortEnabled = new ButtonIconAutoResize(Btn_ToolBox);
        btn_sortEnabled->setObjectName(QString::fromUtf8("btn_sortEnabled"));
        btn_sortEnabled->setEnabled(true);
        sizePolicy2.setHeightForWidth(btn_sortEnabled->sizePolicy().hasHeightForWidth());
        btn_sortEnabled->setSizePolicy(sizePolicy2);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/view/img/btn-db/sorting.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sortEnabled->setIcon(icon7);
        btn_sortEnabled->setCheckable(true);
        btn_sortEnabled->setChecked(false);
        btn_sortEnabled->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btn_sortEnabled->setAutoRaise(true);

        horizontalLayout->addWidget(btn_sortEnabled);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        cmb_Strategy = new QComboBox(Btn_ToolBox);
        cmb_Strategy->setObjectName(QString::fromUtf8("cmb_Strategy"));
        sizePolicy1.setHeightForWidth(cmb_Strategy->sizePolicy().hasHeightForWidth());
        cmb_Strategy->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(cmb_Strategy);

        btn_submitAll = new QPushButton(Btn_ToolBox);
        btn_submitAll->setObjectName(QString::fromUtf8("btn_submitAll"));
        btn_submitAll->setEnabled(false);
        sizePolicy1.setHeightForWidth(btn_submitAll->sizePolicy().hasHeightForWidth());
        btn_submitAll->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(btn_submitAll);

        chk_showRelExColumns = new QCheckBox(Btn_ToolBox);
        chk_showRelExColumns->setObjectName(QString::fromUtf8("chk_showRelExColumns"));
        sizePolicy1.setHeightForWidth(chk_showRelExColumns->sizePolicy().hasHeightForWidth());
        chk_showRelExColumns->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(chk_showRelExColumns);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        horizontalLayout->addLayout(horizontalLayout_5);


        retranslateUi(Btn_ToolBox);

        QMetaObject::connectSlotsByName(Btn_ToolBox);
    } // setupUi

    void retranslateUi(QWidget *Btn_ToolBox)
    {
        Btn_ToolBox->setWindowTitle(QApplication::translate("Btn_ToolBox", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        chk_editable->setToolTip(QApplication::translate("Btn_ToolBox", "toggled edit mode [F2]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chk_editable->setText(QApplication::translate("Btn_ToolBox", "edit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_insert->setToolTip(QApplication::translate("Btn_ToolBox", "insert row [INS]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_insert->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_copy->setToolTip(QApplication::translate("Btn_ToolBox", "copy row [F9]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_copy->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_edit->setToolTip(QApplication::translate("Btn_ToolBox", "edit row [F4]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_edit->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_delete->setToolTip(QApplication::translate("Btn_ToolBox", "remove row [DEL]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_delete->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_view->setToolTip(QApplication::translate("Btn_ToolBox", "view [F3]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_view->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
        ledt_filter->setPlaceholderText(QApplication::translate("Btn_ToolBox", "search", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_search_settings->setToolTip(QApplication::translate("Btn_ToolBox", "select field for seaching", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_search_settings->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn_selectByValue->setToolTip(QApplication::translate("Btn_ToolBox", "select by field value [F8]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_selectByValue->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btn_sortEnabled->setToolTip(QApplication::translate("Btn_ToolBox", "Sorting", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_sortEnabled->setText(QApplication::translate("Btn_ToolBox", "...", 0, QApplication::UnicodeUTF8));
        cmb_Strategy->clear();
        cmb_Strategy->insertItems(0, QStringList()
         << QApplication::translate("Btn_ToolBox", "OnFieldChange", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Btn_ToolBox", "OnRowChange", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Btn_ToolBox", "OnManulaSubmit", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        cmb_Strategy->setToolTip(QApplication::translate("Btn_ToolBox", "Edit strategy", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btn_submitAll->setToolTip(QApplication::translate("Btn_ToolBox", "save changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_submitAll->setText(QApplication::translate("Btn_ToolBox", "submitAll", 0, QApplication::UnicodeUTF8));
        chk_showRelExColumns->setText(QApplication::translate("Btn_ToolBox", "show all columns", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Btn_ToolBox: public Ui_Btn_ToolBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BTN_TOOLBOX_H

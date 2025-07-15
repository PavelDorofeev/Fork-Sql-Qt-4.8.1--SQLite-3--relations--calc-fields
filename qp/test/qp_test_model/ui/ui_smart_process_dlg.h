/********************************************************************************
** Form generated from reading UI file 'smart_process_dlg.ui'
**
** Created: Tue 1. Jul 11:55:31 2025
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMART_PROCESS_DLG_H
#define UI_SMART_PROCESS_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Smart_Process_Dlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *dialogTopFrame;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_header;
    QVBoxLayout *contentLayout;
    QLabel *lbl_text1;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *lbl_text2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_Close;
    QPushButton *btn_wait;

    void setupUi(QDialog *Smart_Process_Dlg)
    {
        if (Smart_Process_Dlg->objectName().isEmpty())
            Smart_Process_Dlg->setObjectName(QString::fromUtf8("Smart_Process_Dlg"));
        Smart_Process_Dlg->resize(537, 542);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(Smart_Process_Dlg->sizePolicy().hasHeightForWidth());
        Smart_Process_Dlg->setSizePolicy(sizePolicy);
        Smart_Process_Dlg->setMinimumSize(QSize(537, 542));
        QFont font;
        font.setPointSize(26);
        Smart_Process_Dlg->setFont(font);
        Smart_Process_Dlg->setWindowTitle(QString::fromUtf8("..."));
        Smart_Process_Dlg->setSizeGripEnabled(true);
        verticalLayout = new QVBoxLayout(Smart_Process_Dlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        dialogTopFrame = new QFrame(Smart_Process_Dlg);
        dialogTopFrame->setObjectName(QString::fromUtf8("dialogTopFrame"));
        sizePolicy.setHeightForWidth(dialogTopFrame->sizePolicy().hasHeightForWidth());
        dialogTopFrame->setSizePolicy(sizePolicy);
        dialogTopFrame->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(12);
        dialogTopFrame->setFont(font1);
        dialogTopFrame->setFrameShape(QFrame::StyledPanel);
        dialogTopFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_7 = new QVBoxLayout(dialogTopFrame);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        lbl_header = new QLabel(dialogTopFrame);
        lbl_header->setObjectName(QString::fromUtf8("lbl_header"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(lbl_header->sizePolicy().hasHeightForWidth());
        lbl_header->setSizePolicy(sizePolicy1);
        lbl_header->setFont(font);
        lbl_header->setTextFormat(Qt::RichText);
        lbl_header->setScaledContents(false);
        lbl_header->setAlignment(Qt::AlignCenter);
        lbl_header->setWordWrap(true);
        lbl_header->setOpenExternalLinks(true);

        verticalLayout_2->addWidget(lbl_header);


        verticalLayout_7->addLayout(verticalLayout_2);

        contentLayout = new QVBoxLayout();
        contentLayout->setObjectName(QString::fromUtf8("contentLayout"));
        lbl_text1 = new QLabel(dialogTopFrame);
        lbl_text1->setObjectName(QString::fromUtf8("lbl_text1"));
        sizePolicy1.setHeightForWidth(lbl_text1->sizePolicy().hasHeightForWidth());
        lbl_text1->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(24);
        lbl_text1->setFont(font2);
        lbl_text1->setFrameShadow(QFrame::Raised);
        lbl_text1->setTextFormat(Qt::RichText);
        lbl_text1->setWordWrap(true);

        contentLayout->addWidget(lbl_text1);


        verticalLayout_7->addLayout(contentLayout);

        scrollArea = new QScrollArea(dialogTopFrame);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 485, 324));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        lbl_text2 = new QLabel(scrollAreaWidgetContents);
        lbl_text2->setObjectName(QString::fromUtf8("lbl_text2"));
        sizePolicy1.setHeightForWidth(lbl_text2->sizePolicy().hasHeightForWidth());
        lbl_text2->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        lbl_text2->setFont(font3);
        lbl_text2->setFocusPolicy(Qt::StrongFocus);
        lbl_text2->setAutoFillBackground(false);
        lbl_text2->setFrameShadow(QFrame::Sunken);
        lbl_text2->setText(QString::fromUtf8(""));
        lbl_text2->setTextFormat(Qt::RichText);
        lbl_text2->setWordWrap(true);
        lbl_text2->setOpenExternalLinks(true);
        lbl_text2->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        verticalLayout_3->addWidget(lbl_text2);


        verticalLayout_5->addLayout(verticalLayout_3);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_7->addWidget(scrollArea);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_Close = new QPushButton(dialogTopFrame);
        btn_Close->setObjectName(QString::fromUtf8("btn_Close"));
        btn_Close->setDefault(true);

        horizontalLayout->addWidget(btn_Close);

        btn_wait = new QPushButton(dialogTopFrame);
        btn_wait->setObjectName(QString::fromUtf8("btn_wait"));

        horizontalLayout->addWidget(btn_wait);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_7->addLayout(verticalLayout_4);

        verticalLayout_7->setStretch(0, 1);
        verticalLayout_7->setStretch(1, 1);
        verticalLayout_7->setStretch(2, 11);
        verticalLayout_7->setStretch(3, 1);

        verticalLayout->addWidget(dialogTopFrame);


        retranslateUi(Smart_Process_Dlg);

        QMetaObject::connectSlotsByName(Smart_Process_Dlg);
    } // setupUi

    void retranslateUi(QDialog *Smart_Process_Dlg)
    {
        lbl_header->setText(QString());
        lbl_text1->setText(QString());
        btn_Close->setText(QApplication::translate("Smart_Process_Dlg", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btn_wait->setText(QApplication::translate("Smart_Process_Dlg", "\320\266\320\264\320\270\321\202\320\265...", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Smart_Process_Dlg);
    } // retranslateUi

};

namespace Ui {
    class Smart_Process_Dlg: public Ui_Smart_Process_Dlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMART_PROCESS_DLG_H

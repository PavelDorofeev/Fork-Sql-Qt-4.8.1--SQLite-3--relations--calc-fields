/********************************************************************************
** Form generated from reading UI file 'search_settings_dlg.ui'
**
** Created: Tue 15. Jul 17:01:54 2025
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCH_SETTINGS_DLG_H
#define UI_SEARCH_SETTINGS_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Search_Settings_Dlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *dialogTopFrame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *cmb_Fields;
    QCheckBox *chk_caseSensetive;
    QCheckBox *chk_exactly;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Search_Settings_Dlg)
    {
        if (Search_Settings_Dlg->objectName().isEmpty())
            Search_Settings_Dlg->setObjectName(QString::fromUtf8("Search_Settings_Dlg"));
        Search_Settings_Dlg->resize(388, 161);
        Search_Settings_Dlg->setMinimumSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/view/img/btn-db/search-settings.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Search_Settings_Dlg->setWindowIcon(icon);
        Search_Settings_Dlg->setSizeGripEnabled(true);
        verticalLayout_2 = new QVBoxLayout(Search_Settings_Dlg);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        dialogTopFrame = new QFrame(Search_Settings_Dlg);
        dialogTopFrame->setObjectName(QString::fromUtf8("dialogTopFrame"));
        verticalLayout = new QVBoxLayout(dialogTopFrame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(dialogTopFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        cmb_Fields = new QComboBox(dialogTopFrame);
        cmb_Fields->setObjectName(QString::fromUtf8("cmb_Fields"));

        horizontalLayout_2->addWidget(cmb_Fields);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        chk_caseSensetive = new QCheckBox(dialogTopFrame);
        chk_caseSensetive->setObjectName(QString::fromUtf8("chk_caseSensetive"));
        chk_caseSensetive->setMinimumSize(QSize(344, 21));

        verticalLayout->addWidget(chk_caseSensetive);

        chk_exactly = new QCheckBox(dialogTopFrame);
        chk_exactly->setObjectName(QString::fromUtf8("chk_exactly"));

        verticalLayout->addWidget(chk_exactly);

        buttonBox = new QDialogButtonBox(dialogTopFrame);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addWidget(dialogTopFrame);


        retranslateUi(Search_Settings_Dlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), Search_Settings_Dlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Search_Settings_Dlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(Search_Settings_Dlg);
    } // setupUi

    void retranslateUi(QDialog *Search_Settings_Dlg)
    {
        Search_Settings_Dlg->setWindowTitle(QApplication::translate("Search_Settings_Dlg", "setting: where to search text by fields", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Search_Settings_Dlg", "where to search : ", 0, QApplication::UnicodeUTF8));
        chk_caseSensetive->setText(QApplication::translate("Search_Settings_Dlg", "case sensible", 0, QApplication::UnicodeUTF8));
        chk_exactly->setText(QApplication::translate("Search_Settings_Dlg", "exactly", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Search_Settings_Dlg: public Ui_Search_Settings_Dlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_SETTINGS_DLG_H

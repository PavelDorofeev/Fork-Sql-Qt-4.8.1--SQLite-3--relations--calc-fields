#include "btn_toolbox.h"
#include "ui_btn_toolbox.h"
#include "pbltableview.h"
#include "pbltableview/pblsqlrelationaltablemodel.h"
#include "some_tests.h"
#include <QMessageBox>
#include "QSqlError"
#include <QDebug>
#include "PblTableView/my_sql.h"
#include "config.h"


Btn_ToolBox::Btn_ToolBox(PblTableView *view_,
                         PblSqlRelationalTableModel *mdl_) :
    QWidget((QWidget*)view_),
    ui(new Ui::Btn_ToolBox)
{
    ui->setupUi(this);

    mdl = mdl_;

    view = view_;

    ui->ledt_filter->setMaximumWidth(200);


   // setBtn_searchInTable(true, false);
   // setBtn_selectionByValue(true, true);

}


Ui::Btn_ToolBox *Btn_ToolBox::getUi()
{
    return ui;
}

Btn_ToolBox::~Btn_ToolBox()
{
    //qDebug("~Btn_ToolBox");
    delete ui;;
}


void Btn_ToolBox::on_btn_submitAll_clicked()
{
    if( ! mdl->submitAll())
    {
        QMessageBox::warning(this, mySql::error_ , tr("submitAll wrong : ")+mdl->lastError().text());
        qCritical(" ! submitAll");
    }
}


void Btn_ToolBox::on_btn_search_settings_clicked()
{
    Search_Settings_Dlg dlg(mdl , view,  this);

    dlg.setSettings(view->find_settings);

    dlg.exec();


    if(view->find_settings != dlg.find_settings)
    {
        view->find_settings = dlg.find_settings;
        on_ledt_filter_returnPressed();
    }
}

void Btn_ToolBox::on_ledt_filter_returnPressed()
{
    if ( view->slot_searchInTable(ui->ledt_filter->text().trimmed()))
    {
        if(ui->ledt_filter->text().isEmpty())
            ui->btn_searchInTable->setEnabled(false);
        else
            ui->btn_searchInTable->setEnabled(true);
    }
}


void Btn_ToolBox::on_btn_searchInTable_clicked(bool checked)
{

    if(! checked && ! ui->ledt_filter->text().isEmpty())
    {
        ui->ledt_filter->clear();
        on_ledt_filter_returnPressed();
    }
}

void Btn_ToolBox::on_btn_selectByValue_clicked(bool checked)
{
    view->slot_triggeredSelectByFieldValue(checked);

}

void Btn_ToolBox::setBtn_searchInTable(bool visible , bool enabled)
{

}

void Btn_ToolBox::setBtn_selectionByValue(bool visible , bool enabled)
{
    ui->btn_selectByValue->setVisible(visible);
    ui->btn_selectByValue->setEnabled(enabled);

}

void Btn_ToolBox::setBtn_selectByValue(bool visible, bool checked)
{
    ui->btn_selectByValue->setVisible(visible);
    ui->btn_selectByValue->setChecked(checked);
}

void Btn_ToolBox::on_btn_sortEnabled_clicked(bool checked)
{

    view->setSortingEnabled(checked);

}



void Btn_ToolBox::on_btn_view_clicked()
{

    if( ! view->currentIndex().isValid())
        return;

    view->slot_viewRowBtnClick();

}

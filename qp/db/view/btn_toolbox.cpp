#include "btn_toolbox.h"
#include "ui_btn_toolbox.h"
#include "qp_tableview_wrapper.h"
#include "qp/db/model/qp_sqltablemodel.h"
#include "some_tests.h"
#include <QMessageBox>
#include "QSqlError"
#include <QDebug>
#include "qp/db/model/my_sql.h"
#include "config.h"


Btn_ToolBox::Btn_ToolBox(QpTableViewWrapper *view_ ) :
    QWidget((QWidget*)view_),
    ui(new Ui::Btn_ToolBox)
{
    ui->setupUi(this);

    //    /mdl = mdl_;

    view = view_;

    ui->ledt_filter->setMaximumWidth(200);


    // setBtn_searchInTable(true, false);
    // setBtn_selectionByValue(true, true);


    ui->ledt_filter->setPlaceholderText(tr("search"));

}


Ui::Btn_ToolBox *Btn_ToolBox::getUi()
{
    return ui;
}

Btn_ToolBox::~Btn_ToolBox()
{
    //qDebug("~Btn_ToolBox");
    delete ui;
}


void Btn_ToolBox::on_btn_submitAll_clicked()
{
    if(ui->cmb_Strategy->currentIndex() == QSqlTableModel::OnManualSubmit)
    {
        if( ! view->Model()->submitAll())
        {
            QMessageBox::warning(this,
                                 qp::dbg::error_ ,
                                 tr("submitAll was wrong,\n error: %1").
                                 arg(view->Model()->lastError().text()));

            qCritical(" ! submitAll 578695987496");
        }
    }
    else
    {
        if( ! view->Model()->submit())
        {
            QMessageBox::warning(this,
                                 qp::dbg::error_ ,
                                 tr("submit was wrong,\n error: %1").
                                 arg(view->Model()->lastError().text()));

            qCritical(" ! submitAll 578695987496");
        }
    }
}


void Btn_ToolBox::on_btn_search_settings_clicked()
{
    Search_Settings_Dlg dlg(view->Model() , view,  this);

    dlg.setSettings(view->find_settings);

    if( dlg.exec() ==QDialog::Rejected )
        return;


    if(view->find_settings != dlg.find_settings)
    {
        view->find_settings = dlg.find_settings;

        on_ledt_filter_returnPressed();
    }
}

void Btn_ToolBox::on_ledt_filter_returnPressed()
{
    QString txt = ui->ledt_filter->text().trimmed();

    //    if(txt.isEmpty())
    //        return;

    if ( view->slot_searchInTable( txt) )
    {
    }
    //    qDebug() << " btn_searchInTable ";
    //    qDebug() << "isDown " << view->tlbx->ui->btn_searchInTable->isDown();
    //    qDebug() << "isCheckable " << view->tlbx->ui->btn_searchInTable->isCheckable();
    //    qDebug() << "isChecked " << view->tlbx->ui->btn_searchInTable->isChecked();

}


//void Btn_ToolBox::on_btn_searchInTable_clicked(bool checked)
//{

//    if(! checked && ! ui->ledt_filter->text().isEmpty())
//    {
//        ui->ledt_filter->clear();
//        on_ledt_filter_returnPressed();
//    }
//}

void Btn_ToolBox::on_btn_selectByValue_clicked( bool checked )
{
    //if( view->Model()->having.count() > 0 || ! view->Model()->filter().isEmpty())
    if( ! checked )
    {

        view->slot_selectByFieldValue_Triggered( false );

        view->act_selectByFieldValue->setChecked( false);

    }
    else
    {
        view->slot_selectByFieldValue_Triggered( true );

        view->act_selectByFieldValue->setChecked( true );
    }



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
    //view->tlbx->ui->btn_sortEnabled->setDown(checked);
    //view->tlbx->ui->btn_sortEnabled->setIcon();
    //view->tlbx->ui->btn_sortEnabled->icon()

    if(checked)
        view->tlbx->ui->btn_sortEnabled->setIcon(QIcon(":/view/img/btn-db/sorting.svg"));
    else
        view->tlbx->ui->btn_sortEnabled->setIcon(QIcon(":/view/img/btn-db/sorting_off.svg"));




}



void Btn_ToolBox::on_btn_view_clicked()
{

    if( ! view->currentIndex().isValid())
        return;

    view->slot_viewRowBtnClick();

}



void Btn_ToolBox::on_btn_clear_seached_text_clicked()
{
    ui->ledt_filter->clear();
    on_ledt_filter_returnPressed();
}



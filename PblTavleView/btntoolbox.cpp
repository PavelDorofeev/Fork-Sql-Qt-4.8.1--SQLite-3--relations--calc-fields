#include "btntoolbox.h"
#include "ui_btntoolbox.h"
#include "pbltableview.h"
#include "PblSqlRelationalTableModel.h"
#include <QMessageBox>
#include "QSqlError"


BtnToolBox::BtnToolBox(PblTableView *view_,
                       PblSqlRelationalTableModel *mdl_) :
    QWidget((QWidget*)view_),
    ui(new Ui::BtnToolBox)
{
    ui->setupUi(this);

    mdl = mdl_;

    view = view_;

    ui->ledt_filter->setMaximumWidth(200);

    connect(ui->btn_insert, SIGNAL(clicked()),
            view->act_InsertRow, SLOT( trigger() ));

    connect(ui->btn_edit, SIGNAL(clicked()),
            view->act_EditRow, SLOT( trigger() ));

    connect(ui->btn_delete, SIGNAL(clicked()),
            view->act_DeleteRow, SLOT( trigger()));

    connect(ui->btn_copy, SIGNAL(clicked()),
            view->act_CopyRow, SLOT( trigger() ));

    connect(ui->chk_editable, SIGNAL(clicked(bool)),
            this, SLOT( slot_setEditable(bool)));

    ui->cmb_Strategy->setCurrentIndex(mdl->editStrategy());

}


BtnToolBox::~BtnToolBox()
{
    //qDebug("~BtnToolBox");
    delete ui;;
}

void BtnToolBox::on_ledt_filter_returnPressed()
{
    view->slot_searchInTable(ui->ledt_filter->text());
}

void BtnToolBox::on_btn_find_clicked()
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



void BtnToolBox::on_cmb_Strategy_currentIndexChanged(int index)
{
    mdl->setEditStrategy((QSqlTableModel::EditStrategy)index);

    if(index == QSqlTableModel::OnFieldChange)
    {
        ui->btn_submitAll->setText("submit");
        ui->btn_submitAll->setEnabled(false);
    }
    else if(index == QSqlTableModel::OnRowChange)
    {
        ui->btn_submitAll->setText("submit");
        ui->btn_submitAll->setEnabled(true);
    }
    else if(index == QSqlTableModel::OnManualSubmit)
    {
        ui->btn_submitAll->setText("submitAll");
        ui->btn_submitAll->setEnabled(true);
    }

}

void BtnToolBox::on_btn_submitAll_clicked()
{
    if( ! mdl->submitAll())
    {
        QMessageBox::warning(this, "error" , tr("submitAll wrong : ")+mdl->lastError().text());
        qCritical(" ! submitAll");
    }
}

void BtnToolBox::setVisible_strategyBox(bool visible)
{
    ui->btn_submitAll->setVisible(visible);
    ui->cmb_Strategy->setVisible(visible);
}

void BtnToolBox::setVisible_searchBox(bool visible)
{
    ui->btn_find->setVisible(visible);
    ui->ledt_filter->setVisible(visible);
}

void BtnToolBox::setEnabled_actionBtns(bool enabled)
{
    ui->btn_insert->setEnabled(enabled);
    ui->btn_edit->setEnabled(enabled);
    ui->btn_copy->setEnabled(enabled);
    ui->btn_delete->setEnabled(enabled);

}

void BtnToolBox::setEditable(bool on)
{
    ui->chk_editable->setChecked(on);
    slot_setEditable(on);
}

void BtnToolBox::setSelectionByValue(bool on)
{
    if(on)
        ui->btn_selectByValue->setIcon( QIcon(":icon/img/btn-db/select-by-value-2-100x100.png"));
    else
        ui->btn_selectByValue->setIcon( QIcon(":icon/img/btn-db/select-by-value-1-100x100.png"));

}

void BtnToolBox::slot_setEditable(bool on)
{
    qDebug() << "BtnToolBox::slot_setEditable " << on;

    view->editable = on;

    if(on)
        view->setSelectionBehavior(QAbstractItemView::SelectItems);

    else
        view->setSelectionBehavior(QAbstractItemView::SelectRows);

    view->repaint();
}

/*void BtnToolBox::on_chk_editable_toggled(bool checked)
{
    qDebug() << "BtnToolBox::on_chk_editable_toggled " << checked;
    view->editable = checked;


    if(checked)
        view->setSelectionBehavior(QAbstractItemView::SelectItems);

    else
    {
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
        repaint();
    }
}
*/

void BtnToolBox::on_btn_selectByValue_clicked()
{
    setSelectionByValue(false);

    mdl->setFilter("");

    if ( ! mdl->select())
        QMessageBox::warning(this ,"error", "select return false");

}

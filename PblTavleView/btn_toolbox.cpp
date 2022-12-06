#include "btn_toolbox.h"
#include "ui_btn_toolbox.h"
#include "pbltableview.h"
#include "PblSqlRelationalTableModel.h"
#include "some_tests.h"
#include <QMessageBox>
#include "QSqlError"


Btn_ToolBox::Btn_ToolBox(PblTableView *view_,
                       PblSqlRelationalTableModel *mdl_) :
    QWidget((QWidget*)view_),
    ui(new Ui::Btn_ToolBox)
{
    ui->setupUi(this);

    mdl = mdl_;

    view = view_;

    ui->ledt_filter->setMaximumWidth(200);

    _CONNECT_(ui->btn_insert, SIGNAL(clicked()),
            view->act_InsertRow, SLOT( trigger() ));

    _CONNECT_(ui->btn_edit, SIGNAL(clicked()),
            view->act_EditRow, SLOT( trigger() ));

    _CONNECT_(ui->btn_delete, SIGNAL(clicked()),
            view->act_DeleteRow, SLOT( trigger()));

    _CONNECT_(ui->btn_copy, SIGNAL(clicked()),
            view->act_CopyRow, SLOT( trigger() ));

    _CONNECT_(ui->chk_editable, SIGNAL(clicked(bool)),
            this, SLOT( slot_setEditable(bool)));

    _CONNECT_(ui->chk_exColumnsVisible, SIGNAL(toggled(bool)),
            view, SLOT( slot_setVisibleExColumns(bool)));

    view->slot_setVisibleExColumns(true);


    ui->cmb_Strategy->setCurrentIndex(mdl->editStrategy());

}


Btn_ToolBox::~Btn_ToolBox()
{
    //qDebug("~Btn_ToolBox");
    delete ui;;
}

void Btn_ToolBox::on_ledt_filter_returnPressed()
{
    view->slot_searchInTable(ui->ledt_filter->text());
}

void Btn_ToolBox::on_btn_find_clicked()
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



void Btn_ToolBox::on_cmb_Strategy_currentIndexChanged(int index)
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

void Btn_ToolBox::on_btn_submitAll_clicked()
{
    if( ! mdl->submitAll())
    {
        QMessageBox::warning(this, "error" , tr("submitAll wrong : ")+mdl->lastError().text());
        qCritical(" ! submitAll");
    }
}

void Btn_ToolBox::setVisible_strategyBox(bool visible)
{
    ui->btn_submitAll->setVisible(visible);
    ui->cmb_Strategy->setVisible(visible);
}

void Btn_ToolBox::setVisible_searchBox(bool visible)
{
    ui->btn_find->setVisible(visible);
    ui->ledt_filter->setVisible(visible);
}

void Btn_ToolBox::setEnabled_actionBtns(bool enabled)
{
    ui->btn_insert->setEnabled(enabled);
    ui->btn_edit->setEnabled(enabled);
    ui->btn_copy->setEnabled(enabled);
    ui->btn_delete->setEnabled(enabled);

}

void Btn_ToolBox::setEditable(bool on)
{
    ui->chk_editable->setChecked(on);
    slot_setEditable(on);
}

void Btn_ToolBox::setSelectionByValue(bool on)
{
    if(on)
        ui->btn_selectByValue->setIcon( QIcon(":icon/img/btn-db/select-by-value-2-100x100.png"));
    else
        ui->btn_selectByValue->setIcon( QIcon(":icon/img/btn-db/select-by-value-1-100x100.png"));

}

void Btn_ToolBox::slot_setEditable(bool on)
{
    qDebug() << "Btn_ToolBox::slot_setEditable " << on;

    view->editable = on;

    if(on)
    {
        view->setSelectionBehavior(QAbstractItemView::SelectItems);

        ui->btn_delete->setEnabled(true);
        ui->btn_copy->setEnabled(true);
        ui->btn_edit->setEnabled(true);
        ui->btn_insert->setEnabled(true);
    }
    else
    {
        view->setSelectionBehavior(QAbstractItemView::SelectRows);

        ui->btn_delete->setEnabled(false);
        ui->btn_copy->setEnabled(false);
        ui->btn_edit->setEnabled(false);
        ui->btn_insert->setEnabled(false);
    }

    view->repaint();
}


void Btn_ToolBox::on_btn_selectByValue_clicked()
{
    setSelectionByValue(false);

    mdl->setFilter("");

    if ( ! mdl->select())
        QMessageBox::warning(this ,"error", "select return false");

}


#include "search_settings_dlg.h"
#include "ui_search_settings_dlg.h"
#include "qp/db/model/qp_sqltablemodel.h"
#include "qp_tableview_wrapper.h"
#include "qp/gui/qp_gui.h"
#include <QDebug>
#include <QSqlField>


Search_Settings_Dlg::Search_Settings_Dlg(QpSqlTableModel * mdl_,
                                         QpTableViewWrapper * view_,
                                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search_Settings_Dlg),
    tableName(QString())
{
    ui->setupUi(this);

    setAttribute(Qt::WA_TranslucentBackground);

    qp::gui::setWindow_woTitle__woFrame_woToolsBtn( this );


    mdl = mdl_;
    view = view_;
    int idx =0;

    QSqlRecord rec = mdl->record();
    QSqlRecord baseRec = mdl->baseRecord();

    for(int col =0 ; col < baseRec.count(); col++)
    {
        if(col == view->priCol)

            continue;


        QString name = baseRec.field(col).name();

        ui->cmb_Fields->insertItem(col , name, col);

    }
}

Search_Settings_Dlg::~Search_Settings_Dlg()
{
    delete ui;
}

void Search_Settings_Dlg::accept()
{
    find_settings.exactly = ui->chk_exactly->isChecked();
    find_settings.caseSensitive = ui->chk_caseSensetive->isChecked();

    QAbstractItemModel *mdl = ui->cmb_Fields->model();

    int row = ui->cmb_Fields->currentIndex();

    find_settings.searchedField =  mdl->data(mdl->index(row,0),Qt::UserRole).toInt();

    QDialog::accept();
}

void Search_Settings_Dlg::reject()
{
    QDialog::reject();
}

void Search_Settings_Dlg::cmb_Fields_currentIndexChanged(int row)
{
    QAbstractItemModel *mdl = ui->cmb_Fields->model();

    find_settings.searchedField = mdl->data(mdl->index(row,0),Qt::UserRole).toInt();

}
void Search_Settings_Dlg::setSettings(FIND_SETTINGS find_settings_)
{
    find_settings = find_settings_;

    ui->chk_caseSensetive->setChecked(find_settings.caseSensitive);

    ui->chk_exactly->setChecked(find_settings.exactly);

    if(find_settings.searchedField>=0)
    {
        int col =  ui->cmb_Fields->findData(find_settings.searchedField , Qt::UserRole);

        if(col>=0)
            ui->cmb_Fields->setCurrentIndex(col);
    }
}


void Search_Settings_Dlg::on_buttonBox_accepted()
{

}

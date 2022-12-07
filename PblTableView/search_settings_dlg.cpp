#include "search_settings_dlg.h"
#include "ui_search_settings_dlg.h"
#include "PblSqlRelationalTableModel.h"
#include "pbltableview.h"
#include <QDebug>


Search_Settings_Dlg::Search_Settings_Dlg(PblSqlRelationalTableModel * mdl_,
                   PblTableView * view_,
                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search_Settings_Dlg),
    tableName(QString())
{
    ui->setupUi(this);

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

    done(0);
}

void Search_Settings_Dlg::cmb_Fields_currentIndexChanged(int row)
{
    QAbstractItemModel *mdl = ui->cmb_Fields->model();

    find_settings.searchedField = mdl->data(mdl->index(row,0),Qt::UserRole).toInt();

    qDebug() << " searchedField " <<  find_settings.searchedField;

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


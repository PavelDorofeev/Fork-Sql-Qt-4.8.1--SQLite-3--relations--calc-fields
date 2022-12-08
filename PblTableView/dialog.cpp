#include "dialog.h"
#include "ui_dialog.h"
#include "pbltableview.h"
#include "PblSqlRelationalTableModel.h"
#include <QMessageBox>
#include <QSqlRelation>
#include <QSqlError>
#include "some_tests.h"
#include "table_dlg.h"
#include "pbltableview_purchases.h"
#include "pblheaderview.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    setWindowTitle("purchases");

    mdl = new PblSqlRelationalTableModel(this);

    mdl->setTable("purchases");


    if( ! mdl->setRelation( 1 , PblSqlRelation(1, "goods" , "id" , "productName")))
        QMessageBox::critical(this , tr("error"), tr("setRelation"));


    bool bbb= mdl->select();

    view = new PblTableView_Purchases(mdl, ui->tableViewLO, this , true);

    view->setActionVisible(PblTableView::ACTION_CHOSE_ROW , false);
    view->setModel(mdl);

    _CONNECT_(mdl , SIGNAL(dataChanged(QModelIndex,QModelIndex)),
              view , SLOT(slot_dataChanged(QModelIndex,QModelIndex)));

    setSizeGripEnabled(true);

    adjustSize();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btn_Close_clicked()
{
    close();
}


void Dialog::on_btn_save_clicked()
{
    PblSqlRelationalTableModel mdl_checks(this);

    mdl_checks.setEditStrategy(QSqlTableModel::OnManualSubmit);

    QString tableName = "checks";

    mdl_checks.setTable(tableName);

    qDebug() << "mdl->rowCount()" << mdl->rowCount();

    for(int row=0; row < mdl->rowCount(); row++)
    {
        if ( ! mdl_checks.insertRow(0))
        {
            QMessageBox::critical(this , "error" , tr("вставка строки в таблицу ").append(tableName).append(" закончилась не успешно"));
            return;
        }

        // -----------------------------------------------------------------

        int sumCol1 =  mdl->record().indexOf("sum");

        QVariant sumValue = mdl->data(mdl->index(row , sumCol1));

        int sumCol2 =  mdl_checks.record().indexOf("sum");

        if ( ! mdl_checks.setData(mdl_checks.index(0 , sumCol2), sumValue) )
        {
            QMessageBox::critical(this , "error" , tr("setData return false, table").append(mdl_checks.tableName()).append(", field : sum"));
            return;
        }

        // -----------------------------------------------------------------

        qDebug() << "mdl->record() " << mdl->record();

        int productNameCol1 = mdl->baseRecord().indexOf("productName");

        int productNameCol2 = mdl_checks.record().indexOf("productName");

        if( mdl->getRelIdColumn(productNameCol1) == -1 )
        {
            QMessageBox::critical(this , "error" , tr("productName field is not with relation"));
            return;
        }

        int productNameCol2Ex = mdl->getRelIdColumn(productNameCol1);

        QVariant productName_id_Value = mdl->data(mdl->index(row , productNameCol2Ex ));

        if ( ! mdl_checks.setData(mdl_checks.index(0 , productNameCol2), productName_id_Value) )
        {
            QMessageBox::critical(this , "error" , tr("setData return false, table").append(mdl_checks.tableName()).append(", field : productName"));
            return;
        }
    }

    if ( ! mdl_checks.submitAll())
    {
        QMessageBox::critical(this , "error" , tr("submit return false, table ").append(mdl_checks.tableName()).append(" sql: ").append(mdl_checks.lastError().text()));
        return;
    }
}

void Dialog::openTable(const QString & tableName)
{
}

void Dialog::on_btn_goods_clicked()
{
    QList<CALC_COLUMN> lstCalc;

    CALC_COLUMN calc;

    calc.idField1 = "productName";
    calc.table = "checks";
    calc.idField2 = "id";
    calc.calcFuncName = "sum";
    calc.calcFuncName_As = tr("продано");


    lstCalc << calc;

    Table_Dlg dlg("goods" , this, true, lstCalc);

    dlg.exec();
}

void Dialog::on_btn_checks_clicked()
{


    QList<CALC_COLUMN> calcLst;
    QList<PblSqlRelation> relLst;

    relLst << PblSqlRelation(1, "goods" , "id" , "productName");

    Table_Dlg dlg("checks" , this, false, calcLst ,relLst);

    dlg.mdl->select();
    dlg.exec();

}

void Dialog::on_btn_logView_clicked()
{
    emit sig_openLoggingOnToOnNotepad();
}


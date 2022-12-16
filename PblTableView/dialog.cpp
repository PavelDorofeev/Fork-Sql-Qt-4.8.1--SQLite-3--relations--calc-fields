#include "dialog.h"
#include "ui_dialog.h"
#include "pbltableview.h"
#include "pblsqlrelationaltablemodel.h"
#include <QMessageBox>
#include <QSqlRelation>
#include <QSqlError>
#include "some_tests.h"
#include "table_dlg.h"
#include "pblsqlrelationaltablemodel_purchases.h"
#include "pblapplication.h"
#include <QDebug>
#include "pbltableview/my_sql.h"

Dialog::Dialog(QString langId, QSqlDatabase &db_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    db = db_;

    int cmbLangIdx=0;

    if(ui->cmb_Language->findText(langId)>=0)
        cmbLangIdx=ui->cmb_Language->findText(langId);

    ui->cmb_Language->setCurrentIndex(cmbLangIdx);

    QString title = windowTitle();
    title += " 4.0.1.1";

    setWindowTitle(title) ;


    mdl = new PblSqlRelationalTableModel_Purchases(this , db);

    if( ! mdl->set_Table("purchases"))
        return;

    mdl->setAlignment(0, Qt::AlignCenter);

    mdl->setAlignment(2, Qt::AlignRight|Qt::AlignVCenter);
    mdl->setPrecision(2, 2);
    mdl->setDblFormat(2, 'f');

    mdl->setAlignment(3, Qt::AlignRight|Qt::AlignVCenter);
    mdl->setPrecision(3, 3);
    mdl->setDblFormat(3, 'f');

    mdl->setAlignment(4, Qt::AlignRight|Qt::AlignVCenter);
    mdl->setPrecision(4, 2);
    mdl->setDblFormat(4, 'f');

    mdl->setAlignment(5, Qt::AlignCenter|Qt::AlignVCenter);


    if( ! mdl->setRelation( PblSqlRelation(1, "productName", "goods" , "id" , "productName")))
        QMessageBox::critical(this , mySql::error, tr("setRelation returns false"));

    //if()
    bool bbb= mdl->select();

    view = new PblTableView(mdl, ui->tableViewLO, db, this , true);

    view->setActionVisible(PblTableView::ACTION_CHOSE_ROW , false);
    view->setModel(mdl);

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
    if( mdl->rowCount() == 0)
    {
        QMessageBox::critical(this , mySql::error , tr("you should fill the table '%1'").arg(mdl->tableName()));
        return;
    }

    PblSqlRelationalTableModel mdl_checks(this , db);

    mdl_checks.setEditStrategy(QSqlTableModel::OnManualSubmit);

    QString tableName = "checks";

    if( ! mdl_checks.set_Table(tableName) )
        return;

    for(int row=0; row < mdl->rowCount(); row++)
    {
        if ( ! mdl_checks.insertRow(0))
        {
            QMessageBox::critical(this , mySql::error , tr("inserting row in table '%1' returns false %2").arg(tableName).arg(mdl->lastError().text()));
            return;
        }

        // -----------------------------------------------------------------

        int sumCol1 =  mdl->record().indexOf("sum");

        QVariant sumValue = mdl->data(mdl->index(row , sumCol1));

        int sumCol2 =  mdl_checks.record().indexOf("sum");

        if ( ! mdl_checks.setData(mdl_checks.index(0 , sumCol2), sumValue) )
        {
            QMessageBox::critical(this , mySql::error , tr("setData return false, table").append(mdl_checks.tableName()).append(", field : sum"));
            return;
        }

        // -----------------------------------------------------------------

        int productNameCol1 = mdl->baseRecord().indexOf("productName");

        int productNameCol2 = mdl_checks.record().indexOf("productName");

        if( mdl->getRelIdColumn(productNameCol1) == -1 )
        {
            QMessageBox::critical(this , mySql::error , tr("productName field is not with relation"));
            return;
        }

        int productNameCol2Ex = mdl->getRelIdColumn(productNameCol1);

        QVariant productName_id_Value = mdl->data(mdl->index(row , productNameCol2Ex ));

        if ( ! mdl_checks.setData(mdl_checks.index(0 , productNameCol2), productName_id_Value) )
        {
            QMessageBox::critical(this , mySql::error , tr("setData return false, table").append(mdl_checks.tableName()).append(", field : productName"));
            return;
        }
    }

    if ( ! mdl_checks.submitAll())
    {
        QMessageBox::critical(this , mySql::error , tr("submit returns false, table ").append(mdl_checks.tableName()).append(" sql: ").append(mdl_checks.lastError().text()));
        return;
    }

    if( ! mdl->removeRows(0,  mdl->rowCount()))
    {
        QMessageBox::critical(this , mySql::error , tr("removeRows returns false, table '%1' ").arg(mdl->tableName()).append(mdl->lastError().text()));
        return;
    }

    if( ! mdl->submitAll() && mdl->editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        QMessageBox::critical(this , mySql::error , mySql::submitAllFalse.arg(mdl->tableName()).arg(mdl->lastError().text()));
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

    calc.idField1        = "id";
    calc.table          = "checks";
    calc.idField2        = "productName";
    calc.summaryField   = "sum";
    calc.calcFunc       = "sum";
    calc.calcFuncName_As = tr("sold");


    lstCalc << calc;

    Table_Dlg dlg("goods" , db , this, true, lstCalc);


    dlg.mdl->setAlignment(0, Qt::AlignCenter);

    dlg.mdl->setAlignment(2, Qt::AlignRight|Qt::AlignVCenter);
    dlg.mdl->setPrecision(2, 2);
    dlg.mdl->setDblFormat(2, 'f');

    dlg.mdl->setAlignment(3, Qt::AlignRight|Qt::AlignVCenter);
    dlg.mdl->setPrecision(3, 2);
    dlg.mdl->setDblFormat(3, 'f');


    dlg.exec();
}

void Dialog::on_btn_checks_clicked()
{


    QList<CALC_COLUMN> calcLst;
    QList<PblSqlRelation> relLst;

    relLst << PblSqlRelation(1, "productName",  "goods" , "id" , "productName");

    Table_Dlg dlg("checks" , db, this, false, calcLst ,relLst);

    dlg.mdl->setAlignment(0, Qt::AlignCenter);

    dlg.mdl->setPrecision(2,2);
    dlg.mdl->setAlignment(2, Qt::AlignRight|Qt::AlignVCenter);
    dlg.mdl->setDblFormat(2, 'f');

    dlg.mdl->select();
    dlg.exec();

}

void Dialog::on_btn_logView_clicked()
{
    emit sig_openLoggingOnToOnNotepad();
}


void Dialog::on_cmb_Language_currentIndexChanged(const QString &countryName)
{
    emit sig_changeLanguage(countryName);

   accept();

}

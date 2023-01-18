#include "dialog.h"
#include "ui_dialog.h"
#include "pbltableview/pbltableview.h"
#include "pbltableview/pblsqlrelationaltablemodel.h"
#include <QMessageBox>
#include <QSqlRelation>
#include <QSqlError>
#include "pbltableview/some_tests.h"
#include "pbltableview/pbl_table_dlg.h"
#include "pblsqlrelationaltablemodel_purchases.h"
#include "pbltableview/pblapplication.h"
#include <QDebug>
#include "pbltableview/my_sql.h"
#include "pbltableview/pbl_table_dlg.h"
#include "config.h"
#include "logging_system/logging_system.h"

DialogTest::DialogTest(QString langId,
                       QSqlDatabase &db_,
                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    db(db_)
{
    ui->setupUi(this);

    int cmbLangIdx=0;

    if(ui->cmb_Language->findText(langId)>=0)
        cmbLangIdx=ui->cmb_Language->findText(langId);

    ui->cmb_Language->setCurrentIndex(cmbLangIdx);

    QString title = windowTitle();
    title += " 6.0.0.1";

    setWindowTitle(title) ;

    const QString tableName = "purchases";

    //ui->tableViewLO->addWidget(tbl);


    mdl = new PblSqlRelationalTableModel_Purchases(db , this);

    view = new PblTableView(mdl ,
                            ui->tableViewLO,
                            db,
                            this,
                            true,
                            false);

    if ( ! view->prepare(tableName))
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("opening table '%1' is unsuccefully").arg(tableName)
                             +tr("\n\nerror: : %2").arg(mdl->lastError().text()));

        return ;
    }

    view->setEditStrategyVisible(true);
    setSizeGripEnabled(true);

    adjustSize();
}


DialogTest::~DialogTest()
{
    if(mdl->isDirtyRow != -1)
        mdl->submitAll();

    delete ui;
}


void DialogTest::on_btn_Close_clicked()
{
    close();
}


void DialogTest::on_btn_save_clicked()
{
    if( mdl->rowCount() == 0)
    {
        QMessageBox::critical(this , mySql::error_ , tr("you should fill the table '%1'").arg(mdl->tableName()));
        return;
    }

    PblSqlRelationalTableModel mdl_checks( db , this);

    mdl_checks.setEditStrategy(QSqlTableModel::OnManualSubmit);

    QString tableName = "checks";

    if( ! mdl_checks.set_Table(tableName) )
        return;

    for(int row=0; row < mdl->rowCount(); row++)
    {
        if ( ! mdl_checks.insertRow(0))
        {
            QMessageBox::critical(this , mySql::error_ , tr("inserting row in table '%1' returns false %2").arg(tableName).arg(mdl->lastError().text()));
            return;
        }

        // -----------------------------------------------------------------

        int sumCol1 =  mdl->record().indexOf("sum");

        QVariant sumValue = mdl->data(mdl->index(row , sumCol1));

        int sumCol2 =  mdl_checks.record().indexOf("sum");

        if ( ! mdl_checks.setData(mdl_checks.index(0 , sumCol2), sumValue) )
        {
            QMessageBox::critical(this , mySql::error_ , tr("setData return false, table").append(mdl_checks.tableName()).append(", field : sum"));
            return;
        }

        // -----------------------------------------------------------------

        int productNameCol1 = mdl->baseRecord().indexOf("productName");

        int productNameCol2 = mdl_checks.record().indexOf("productName");

        if( mdl->getRelIdColumn(productNameCol1) == -1 )
        {
            QMessageBox::critical(this , mySql::error_ , tr("productName field is not with relation"));
            return;
        }

        int productNameCol2Ex = mdl->getRelIdColumn(productNameCol1);

        QVariant productName_id_Value = mdl->data(mdl->index(row , productNameCol2Ex ));

        if ( ! mdl_checks.setData(mdl_checks.index(0 , productNameCol2), productName_id_Value) )
        {
            QMessageBox::critical(this , mySql::error_ , tr("setData return false, table").append(mdl_checks.tableName()).append(", field : productName"));
            return;
        }
    }

    if ( ! mdl_checks.submitAll())
    {
        QMessageBox::critical(this , mySql::error_ , tr("submit returns false, table ").append(mdl_checks.tableName()).append(" sql: ").append(mdl_checks.lastError().text()));
        return;
    }

    if( ! mdl->removeRows(0,  mdl->rowCount()))
    {
        QMessageBox::critical(this , mySql::error_ , tr("removeRows returns false, table '%1' ").arg(mdl->tableName()).append(mdl->lastError().text()));
        return;
    }

    if( ! mdl->submitAll() && mdl->editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        QMessageBox::critical(this , mySql::error_ , mySql::submitAllFalse.arg(mdl->tableName()).arg(mdl->lastError().text()));
        return;
    }
}

void DialogTest::openTable(const QString & tableName)
{
}

void DialogTest::on_btn_goods_clicked()
{
    QString tableName = "goods";

    PblTableDlg dlg(db , this, true);

    if ( ! dlg.view->prepare(tableName))
    {
        QMessageBox::critical(this , tr("Error") , tr("set_Table '%1' return false").arg("goods"));
        return;
    }

    dlg.view->setEditStrategyVisible(true);

    dlg.exec();
}

void DialogTest::on_btn_checks_clicked()
{
    PblTableDlg dlg( db, this, true);

    QString tableName = "checks";

    if ( ! dlg.view->prepare(tableName))
    {

        QMessageBox::critical(this ,
                              mySql::error_,
                              tr("set_Table '%1' return false").arg(tableName));
        return;
    }

    dlg.view->setEditStrategyVisible(true);

    dlg.exec();

}

void DialogTest::on_btn_logView_clicked()
{
    logging_System::openLoggingOnToOnNotepad();
}


void DialogTest::on_cmb_Language_currentIndexChanged(const QString &countryName)
{
    emit sig_changeLanguage(countryName);

    accept();

}

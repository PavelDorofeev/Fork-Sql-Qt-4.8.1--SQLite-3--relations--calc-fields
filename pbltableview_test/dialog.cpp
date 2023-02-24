#include "dialog.h"
#include "ui_dialog.h"
#include "pbltableview/pbltableview.h"
#include "pbltableview/pblsqlrelationaltablemodel.h"
#include <QMessageBox>
#include <QSqlRelation>
#include <QSqlError>
#include "pbltableview/some_tests.h"
#include "pbltableview/pbl_table_dlg.h"
#include "pblsqlrelationaltablemodel2.h"
#include "pbltableview/pblapplication.h"
#include <QDebug>
#include "pbltableview/my_sql.h"
#include "pbltableview/pbl_table_dlg.h"
#include "config.h"
#include "logging_system/logging_system.h"
#include <QDateTime>
#include "version.h"
#include <QSqlQuery>

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

    title.append(" ").append(PROG_VERSION);

    setWindowTitle(title) ;

    const QString tableName = "purchases";

    //ui->tableViewLO->addWidget(tbl);


    mdl = new PblSqlRelationalTableModel2(db , this);

    if( ! mdl->prepare(tableName))
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("opening table '%1' is unsuccefully").arg(tableName)
                             +tr("\n\nerror: : %2").arg(mdl->lastError().text()));

        return ;
    }

    _CONNECT_(mdl , SIGNAL(sig_column_values_changed(int)),
              this, SLOT(slot_recalculate_tbl(int)));

    view = new PblTableView(this,
                            true,
                            false);


    if ( ! view->prepare( mdl ))
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("opening table '%1' is unsuccefully").arg(tableName)
                             +tr("\n\nerror: : %2").arg(mdl->lastError().text()));

        return ;
    }

    view->setToLayout(ui->tableViewLO);

    slot_recalculate_tbl(mdl->fieldIndex("sum"));

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

    QSqlQuery qq;

    int dat =  QDateTime::currentDateTime().toTime_t() ;

    int productName = mdl->baseRec.indexOf("productName");

    int exCol = mdl->getRelIdColumn(productName);

    for(int row=0; row < mdl->rowCount(); row++)
    {
        QString str = QString( "INSERT INTO checks (productName,sum,date_ )VALUES("\
                               "%1, %2,"+QString::number(dat)+
                               ")").
                arg(mdl->record(row).value(exCol).toInt()  ).
                arg(mdl->record(row).value("sum").toDouble() , 0 , 'f' , 2 );


        qDebug() << str;

        if( ! qq.exec(str))
        {


            QMessageBox::critical(this ,
                                  mySql::error_ ,
                                  tr("query exec wrong \n\n"\
                                     "%1\n\n"\
                                     "%2").
                                  arg(qq.lastError().text()).
                                  arg(str));

            return;
        }
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
    PblTableDlg dlg(tableName , db , this, true);


    dlg.exec();

}

void DialogTest::on_btn_goods_clicked()
{
    openTable("goods");

}

void DialogTest::on_btn_checks_clicked()
{
    openTable("checks");

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


void DialogTest::slot_recalculate_tbl(int col)
{
    if( col == mdl->fieldIndex("sum"))
    {
        double summ=0;

        for( int row =0 ; row < mdl->rowCount(); row++)
        {
            QModelIndex idx = mdl->index( row , mdl->fieldIndex("sum"));

            summ += mdl->data( idx ).toDouble();

        }

        ui->lbl_sum->setText(QString::number(summ , 'f' ,2 ));
    }
}

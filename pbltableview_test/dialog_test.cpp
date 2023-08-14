#include "dialog_test.h"
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
#include "pbltableview/pbltableview2.h"
#include "config.h"
#include "config2.h"
#include "logging_system/logging_system.h"
#include <QDateTime>
#include "pbltableview/version_pbl.h"
#include "pbltableview/pbltableview.h"
#include <QSqlQuery>
#include <QFontDialog>
#include "btn_toolbox.h"


const QString DialogTest::progName = "QTableDlg test db";
const QString DialogTest::fontDir= "font";


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

    if( ! mdl->prepare_mdl(tableName))
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("opening table '%1' is unsuccefully")
                             .arg(tableName)
                             +tr("\n\nerror: : %2")
                             .arg(mdl->lastError().text()));

        return ;
    }

    if( ! config2::setting_mdl2(mdl)) //second level
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("setting_mdl table '%1' is unsuccefully").arg(tableName)
                             +tr("\n\nerror: : %2").arg(mdl->lastError().text()));

        return ;
    }

    _CONNECT_(mdl , SIGNAL(sig_column_values_changed(int)),
              this, SLOT(slot_recalculate_tbl(int)));

    view = new PblTableView2(this,
                             config::setting_view,
                             false);



    if( !view->prepare_view( mdl ) )
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("setting_mdl table '%1' is unsuccefully").arg(tableName)
                             +tr("\n\nerror: : %2").arg(mdl->lastError().text()));

        return ;
    }


    if ( ! mdl->select() )
    {
        QMessageBox::warning(this,
                                  mySql::error_,
                                  tr("select method with table '%1' is wrong").arg(tableName)
                                  +tr("\n\nerror: : %2").arg(mdl->lastError().text()));

             return ;
      }

    view->resizeColumnsToContents();

    view->setToLayout(ui->tableViewLO);

    ui->tableViewLO->setStretch( 0 , 1);
    ui->tableViewLO->setStretch( 1 , 4);
    ui->tableViewLO->addStrut(2); // !!!!!

    //    qDebug() << "   stretch(0) " << ui->tableViewLO->stretch(0);

    //    qDebug() << "   stretch(1) " << ui->tableViewLO->stretch(1);

    //    qDebug() << "   stretch(2) " << ui->tableViewLO->stretch(2);

    //    qDebug() << "   stretch(3) " << ui->tableViewLO->stretch(3);

    slot_recalculate_tbl(mdl->baseRec.indexOf("sum"));

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

    int extCol1 = mdl->getRelIdColumn3( "productName");

    int extCol2 = mdl->getRelIdColumn3( "sub" );

    for(int row=0; row < mdl->rowCount(); row++)
    {

        QString ff = "productName,qty,sum,date_" ;

        QString vv = QString("%1, %2 , %3 , %4").
                arg(mdl->record(row).value(extCol1).toInt()  ).
                arg(mdl->record(row).value("qty").toDouble() , 0 , 'f' , 3 ).
                arg(mdl->record(row).value("sum").toDouble() , 0 , 'f' , 2 ).
                arg(QString::number(dat));

        if(mdl->record(row).value(extCol2).toInt() >0)
        {
            ff += ", sub";

            vv += QString(", %1").
                    arg(mdl->record(row).value(extCol2).toInt() );
        }

        QString str = QString( "INSERT INTO checks ("+ff+") VALUES("+vv+")");




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
    PblTableDlg dlg(tableName ,
                    db ,
                    config::setting_mdl ,
                    config::setting_view ,
                    this,
                    false);


    if (! dlg.mdl->select())
    {
        QMessageBox::warning( this,
                              "select query error",
                              dlg.mdl->lastError().text()
                              );
        return;
    }

    dlg.setWindowTitle(tableName);

    if(tableName == "sub")
        dlg.showNormal();
    else
        dlg.showFullScreen();

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

/*void DialogTest::recalculate_sum(int col)
{
    if( col == mdl->fieldIndex("sum"))
    {
        double summ=0;

        for( int row =0 ; row < mdl->rowCount(); row++)
        {
            QModelIndex idx = mdl->index( row , mdl->fieldIndex("sum"));

            double dblSum = mdl->data( idx ).toDouble();

            summ += dblSum;

        }

        ui->lbl_sum->setText(QString::number(summ , 'f' ,2 ));
    }
}*/


void DialogTest::slot_recalculate_tbl(int col)
{
    if( col == mdl->baseRec.indexOf("sum") )
    {
        double summ=0;

        for( int row =0 ; row < mdl->rowCount(); row++)
        {
            QModelIndex idx = mdl->index( row , mdl->baseRec.indexOf("sum"));

            double dblSum = mdl->data( idx ).toDouble();

            summ += dblSum;

        }

        ui->lbl_sum->setText(QString::number(summ , 'f' ,2 ));
    }
}

void DialogTest::on_btn_font_clicked()
{
    bool bb=false;

    QFont prevFnt=QApplication::font();

    QFontMetrics fm(prevFnt);

    QFont newFont = QFontDialog::getFont(&bb, prevFnt, this);

    if(newFont.pointSize()< 6)
    {
        QMessageBox::warning(this,
                             tr("Недопустимый размер"),
                             tr("Не допускается выбирать размер меньше 6!"));
        return;
    }

    if(newFont.pointSize()>36)
    {
        QMessageBox::warning(this,
                             tr("invalid size (>36)"),
                             tr("This is impissible to use the size more 36!"));
        return;
    }

    QSettings sett( DialogTest::progName , DialogTest::fontDir );

    sett.setValue("font",newFont.toString());

    sett.setValue("pixelSize",newFont.pixelSize());
    sett.setValue("pointSize",newFont.pointSize());
    sett.setValue("pointSizeF",newFont.pointSizeF());
    sett.setValue("weight",newFont.weight());
    sett.setValue("bold",newFont.bold());
    sett.setValue("italic",newFont.italic());
    sett.setValue("family",newFont.family());

    QApplication::setFont(newFont);

    setFont(newFont);

    accept();

}


void DialogTest::on_btn_test_clicked()
{
    openTable("test");
}

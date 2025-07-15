#include "dialog_test.h"
#include "ui_dialog.h"
#include "qp/sql/model/qp_sqltablemodel.h"
#include <QMessageBox>
#include <QSqlRelation>
#include <QSqlError>
#include "qp/sql/view/some_tests.h"
#include "qp_sqltablemodel2.h"
#include "qp/gui/qp_application.h"
#include <QDebug>
#include "qp/sql/model/my_sql.h"
#include "qp/sql/view/qp_table_dlg.h"
#include "qp/sql/view/qp_tableview_wrapper2.h"
#include "config.h"
#include "config2.h"
#include "my_lib/logging_system/logging_system.h"
#include <QDateTime>
#include "qp/sql/version_model.h"
#include "qp/sql/view/qp_tableview_wrapper.h"
#include <QSqlQuery>
#include <QFontDialog>
#include "qp/sql/view/btn_toolbox.h"
#include "qp/core/meta/meta.h"
#include "qp/sql/qp_sql.h"
#include "db1.h"
#include "qp/sql/model/qp_temptablemodel.h"


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


    const QString tableName = db1::TBL_PURCHASES;

    mdl_purch = new QpTempSqlTableModel(db , config::setting_mdl , this);

    QpSqlRecord rec;

    if( ! mdl_purch->prepare_mdl( tableName , QStringList() , QHash<QString,QVariant> ()))
    {
        QMessageBox::warning(this,
                             qp::dbg::error_,
                             tr("opening table '%1' is failed")
                             .arg(tableName)
                             //                             +tr("\n\nerror: : %2")
                             //                             .arg(mdl_purch->lastError().text())
                             );

        return ;
    }


    qp::meta::cnct (mdl_purch , SIGNAL(sig_column_values_changed(int)),
                    this, SLOT(slot_recalculate_tbl(int)));

    view = new QpTableViewWrapper2(this,
                                   config::setting_view,
                                   false);


    //    mdl_purch->setEditStrategy( QSqlTableModel::OnManualSubmit );

    if( !view->prepare_view( mdl_purch ) )
    {
        QMessageBox::warning(this,
                             qp::dbg::error_,
                             tr("setting_mdl table '%1' is unsuccefully").arg(tableName)
                             +tr("\n\nerror: : %2").arg(mdl_purch->lastError().text()));

        return ;
    }


    if ( ! mdl_purch->select() )
    {
        QMessageBox::warning(this,
                             qp::dbg::error_,
                             tr("select method with table '%1' is wrong").arg(tableName)
                             //                             +tr("\n\nerror: : %2").arg(mdl_purch->lastError().text())
                             );

        return ;
    }

//    view->set_ExtColumnsVisible( false  , false);

//    mdl_purch->select();


    view->setToLayout(ui->tableViewLO);

    ui->tableViewLO->setStretch( 0 , 1);
    ui->tableViewLO->setStretch( 1 , 4);
    ui->tableViewLO->addStrut(2); // !!!!!

    //    qDebug() << "   stretch(0) " << ui->tableViewLO->stretch(0);

    //    qDebug() << "   stretch(1) " << ui->tableViewLO->stretch(1);

    //    qDebug() << "   stretch(2) " << ui->tableViewLO->stretch(2);

    //    qDebug() << "   stretch(3) " << ui->tableViewLO->stretch(3);

    //    slot_recalculate_tbl(mdl_purch->baseRec.indexOf( db1::PURCHASES::SUM));

    setSizeGripEnabled(true);

    //view->resizeColumnsToContents();

    adjustSize();
}


DialogTest::~DialogTest()
{
    //    if(mdl_purch->isDirtyRow != qp::db::ROW_UNDEFINED)
    //        mdl_purch->submitAll();

    delete ui;
}


void DialogTest::on_btn_Close_clicked()
{
    close();
}


void DialogTest::on_btn_save_clicked()
{
    if( mdl_purch->rowCount() == 0)
    {
        //        QMessageBox::critical(this , qp::dbg::error_ , tr("you should fill the table '%1'")
        //                              .arg(mdl_purch->tableName()));
        return;
    }

    QSqlQuery qq;

    int dat =  QDateTime::currentDateTime().toTime_t() ;

    //    int extCol1 = mdl_purch->getRelIdColumn3( "productName");

    //    int extCol2 = mdl_purch->getRelIdColumn3( "sub" );

    //    for(int row=0; row < mdl_purch->rowCount(); row++)
    //    {

    //        QString ff = "productName,qty,sum,date_" ;

    //        QString vv = QString("%1, %2 , %3 , %4").
    //                arg(mdl_purch->record(row).value(extCol1).toInt()  ).
    //                arg(mdl_purch->record(row).value("qty").toDouble() , 0 , 'f' , 3 ).
    //                arg(mdl_purch->record(row).value("sum").toDouble() , 0 , 'f' , 2 ).
    //                arg(QString::number(dat));

    //        if(mdl_purch->record(row).value(extCol2).toInt() >0)
    //        {
    //            ff += ", sub";

    //            vv += QString(", %1").
    //                    arg(mdl_purch->record(row).value(extCol2).toInt() );
    //        }

    //        QString str = QString( "INSERT INTO checks ("+ff+") VALUES("+vv+")");




    //        qDebug() << str;

    //        if( ! qq.exec(str))
    //        {


    //            QMessageBox::critical(this ,
    //                                  qp::dbg::error_ ,
    //                                  tr("query exec wrong \n\n"\
    //                                     "%1\n\n"\
    //                                     "%2").
    //                                  arg(qq.lastError().text()).
    //                                  arg(str));

    //            return;
    //        }
    //    }


    //    if( ! mdl_purch->removeRows(0,  mdl_purch->rowCount()))
    //    {
    //        QMessageBox::critical(this , qp::dbg::error_ , tr("removeRows returns false, table '%1' ").arg(mdl_purch->tableName()).append(mdl_purch->lastError().text()));
    //        return;
    //    }

    //    if( ! mdl_purch->submitAll() && mdl_purch->editStrategy() == QSqlTableModel::OnManualSubmit)
    //    {
    //        QMessageBox::critical(this , qp::dbg::error_ , qp::dbg::submitAllFalse.arg(mdl_purch->tableName()).arg(mdl_purch->lastError().text()));
    //        return;
    //    }
}

void DialogTest::openTable(const QString & tableName)
{
    QpTableDlg dlg( tableName ,
                    db ,
                    config::setting_mdl ,
                    config::setting_view ,
                    this,
                    false);



    dlg.setWindowTitle(tableName);

    if(tableName == db1::TBL_SUB_ACCOUNTING )
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
    //    if( col == mdl_purch->baseRec.indexOf("sum") )
    //    {
    //        double summ=0;

    //        for( int row =0 ; row < mdl_purch->rowCount(); row++)
    //        {
    //            QModelIndex idx = mdl_purch->index( row , mdl_purch->baseRec.indexOf("sum"));

    //            double dblSum = mdl_purch->data( idx ).toDouble();

    //            summ += dblSum;

    //        }

    //        ui->lbl_sum->setText(QString::number(summ , 'f' ,2 ));
    //    }
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

void DialogTest::on_btn_resizeColumnsToContents_clicked()
{
    view->resizeColumnsToContents();
}

void DialogTest::on_btn_resizeRowsToContents_clicked()
{
    view->resizeRowsToContents();
}

void DialogTest::on_btn_save_temp_mdl_clicked()
{
    bool bb = mdl_purch->submitAll();

    qDebug() << "submitAll()" << bb;
}

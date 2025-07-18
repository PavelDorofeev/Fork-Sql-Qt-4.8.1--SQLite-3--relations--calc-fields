/******************************************************************************
**
** Contact: BIT Ltd Company (p@kkmspb.ru) Individual Taxpayer Number (ITN) 7826152874
**
** This file is not part of the Qt Sources.
** This is a little convenient fork of QSqlTableModel (Qt 4.8.1) version 4.0
** created by Pavel Dorofeev ( p@kkmspb.ru )
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.

*******************************************************************************/

#include "qp_table_dlg.h"
#include "ui_qp_table_dlg.h"

#include "qp_tableview_wrapper.h"
#include <QMessageBox>
#include "some_tests.h"
#include "qp/sql/view/vertical_header.h"
#include "qp/gui/qp_gui.h"
#include "qp/core/qp_core.h"
#include "qp/core/meta/meta.h"
#include "qp/sql/model/qp_cmnsqltablemodel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>

#include "btn_toolbox.h"

QpTableDlg::QpTableDlg(
        const QString table_Name,
        QSqlDatabase &Db,
        cb_setting_mdl p_cb_setting_mdl,
        cb_setting_view p_cb_setting_view,
        QWidget *parent,
        bool Selectable,
        const QHash<QString,QVariant> &Filter,
        QSqlTableModel::EditStrategy edt
        )
    :
      SizeRememberDlg(parent),
      ui(new Ui::QpTableDlg),
      chosenRow(-1),
      view(0),
      mdl(0),
      selectable(Selectable)

{
    ui->setupUi(this);

    init();

    //----------------------------------------
    QSize  sz = qp::gui::screen_size();

    setMinimumSize( sz.width()*0.4 , sz.height()* 0.4 ); // да работает
    setMaximumSize(sz.width()*0.95 , sz.height()* 0.95 ); // да работает
    int hh = sz.height();
    int ww = sz.width();
    int hh1 = hh*0.1;
    int hhh = hh*0.8;
    int ww1 = ww*0.1;
    int www = ww*0.8;
    setGeometry( ww1, hh1 , www, hhh  );
    //setStyleSheet(QString("height:%1px;width:2%;").arg(sz.height()).arg(sz.width()));

    setSizeGripEnabled(true);


    // ----------------------------------------------------
    //      direct ctor
    // ----------------------------------------------------

    tableName = table_Name;

    setWindowTitle(table_Name);

    init_for_public_ctor( Db , table_Name, p_cb_setting_mdl, p_cb_setting_view, Filter);

    init_form( Db, editable, Selectable);

}

bool QpTableDlg::init_for_public_ctor( QSqlDatabase &Db,
                                       const QString tableName,
                                       cb_setting_mdl p_cb_setting_mdl,
                                       cb_setting_view p_cb_setting_view,
                                       const QHash<QString,QVariant> &Filter)
{
    mdl = new QpSqlTableModel( Db ,
                               p_cb_setting_mdl,
                               this);

    //qDebug() << " Filter " << Filter;

    if( ! mdl->prepare_mdl( tableName , QStringList(), Filter))
    {
        QMessageBox::critical(this ,
                              qp::dbg::error_ ,
                              tr(
                                  "prepare table model is wrong\n"\
                                  "sql error: %3").
                              arg(mdl->lastError().text())
                              );
        return false;
    }

    if (! mdl->select())
    {
        QMessageBox::warning( this,
                              "error",
                              QString("select query error: %1")
                              .arg(mdl->lastError().text())
                              );
        return false;
    }


    view = new QpTableViewWrapper (
                this,
                p_cb_setting_view,
                selectable);



    if( ! view->prepare_view( mdl) ) //  !!
    {
        QMessageBox::critical(this ,
                              qp::dbg::error_ ,
                              tr(
                                  "prepare table model is wrong\n"\
                                  "sql error: %3").
                              arg(mdl->lastError().text())
                              );
        return false;
    }


    return true;
}

// protected

QpTableDlg::QpTableDlg( const QString &tableName,
                        QpSqlTableModel *Mdl,
                        QpTableViewWrapper *View,
                        QSqlDatabase &Db,
                        QWidget *parent,
                        cb_setting_mdl p_cb_setting_mdl,
                        cb_setting_view p_cb_setting_view,
                        bool selectable,
                        const QHash<QString,QVariant> Filter,
                        QSqlTableModel::EditStrategy edt)
    :
      SizeRememberDlg(parent),
      ui(new Ui::QpTableDlg),
      chosenRow(-1),
      view(View),
      mdl(Mdl)
{
    // -------------------------------------------------------
    //                  protected ctor
    // -------------------------------------------------------

    ui->setupUi(this);

    qDebug() << "PblTableDlg Filter " <<Filter;

    // ------------------------------------------------------------
    //          view & mdl are alreeady created !!!! Nothing more
    // ------------------------------------------------------------

    // init( Db , tableName, p_cb_setting_mdl, p_cb_setting_view, Filter);


    if( ! mdl->prepare_mdl( tableName , QStringList(), Filter))
    {
        QMessageBox::critical(this ,
                              qp::dbg::error_ ,
                              tr(
                                  "prepare table model is wrong\n"\
                                  "sql error: %3").
                              arg(mdl->lastError().text())
                              );
        return ;
    }

    if (! mdl->select())
    {
        QMessageBox::warning( this,
                              "error",
                              QString("select query error: %1")
                              .arg(mdl->lastError().text())
                              );
        return ;
    }



    if( ! view->prepare_view( mdl) ) //  !!
    {
        QMessageBox::critical(this ,
                              qp::dbg::error_ ,
                              tr(
                                  "prepare table model is wrong\n"\
                                  "sql error: %3").
                              arg(mdl->lastError().text())
                              );
        return ;
    }

    // ------------------------------------------------------------------

    init_form( Db, editable, selectable);

    qp::meta::cnct ( view , SIGNAL(clicked(QModelIndex)),
                     this, SLOT(slot_view_clicked(QModelIndex) ) );


}

void QpTableDlg::slot_view_clicked(QModelIndex idx)
{
    qDebug() << "QpTableDlg::slot_view_clicked";

    qDebug() << "selectionBehavior" << view->selectionBehavior();

    qDebug() << "focusPolicy" << view->focusPolicy();

    qDebug()<<  "editTriggers " << view->editTriggers();


    qDebug()<<  "editTriggers CurrentChanged " << view->editTriggers().testFlag(QAbstractItemView::CurrentChanged)
             <<  "\n    DoubleClicked " <<view->editTriggers().testFlag(QAbstractItemView::DoubleClicked)
              <<  view->editTriggers().testFlag(QAbstractItemView::SelectedClicked)
               <<  view->editTriggers().testFlag(QAbstractItemView::EditKeyPressed)
                <<  view->editTriggers().testFlag(QAbstractItemView::AnyKeyPressed)
                 <<  view->editTriggers().testFlag(QAbstractItemView::AllEditTriggers)
                     ;
}

bool QpTableDlg::init_form( QSqlDatabase &Db, bool editable, bool selectable)
{
    if( ! Db.isOpen())
        return false;

    sqlite = &Db;


    setSizeGripEnabled(true);


    view->setToLayout(ui->for_table_lo); // impotant


    ui->for_table_lo->setStretch( 0 , 1);

    ui->for_table_lo->setStretch( 1 , 400);

    ui->for_table_lo->addStrut(20); // !!!!!


    // Attention there are two construstors

    qp::meta::cnct (view->act_selectAndClose, SIGNAL(triggered()),
                    this, SLOT(slot_accepted()));


    view->verticalHeader()->show( );
    //    view->ver->setVisible( true );
    //    view->ver->setHidden( false );
    //view->ver->show();

    qDebug() << "view->verticalHeader->isVisible " << view->verticalHeader()->isVisible() ;
    //qDebug() << "view->ver->isHidden " << view->ver->isHidden() ;


    //adjustSize();

    return true;

}

QpTableDlg::~QpTableDlg()
{
    if(view !=0)
    {
        delete view;
        view =0;
    }


    if(mdl !=0)
    {
        delete mdl;
        mdl =0;
    }

    delete ui;
}


void QpTableDlg::slot_accepted()
{
    if(view == 0 | ! view->currentIndex().isValid())
        return;


    chosenRow = view->currentIndex().row();


    chosenRec = mdl->qp_record( chosenRow  );

    QSqlIndex pk = mdl->primaryKey();

    //qDebug() << " pk " << pk;

    if(pk.count() != 1)
    {
        QMessageBox::critical(this,
                              "error" ,
                              "not defined index field name in " + mdl->tableName());
        return;
    }

    chosenId = chosenRec.value(pk.fieldName(0)).toInt();

    accept();
}


bool QpTableDlg::setRelation( QpSqlRelation &rel)
{

    return mdl->setRelation(rel);
}

QVBoxLayout * QpTableDlg::getUi()
{
    return ui->for_table_lo;
}


void QpTableDlg::on_btn_close_clicked()
{
    close();
}


QString QpTableDlg::getReestrPrefix() const
{
    return "table_"+tableName;
}

QSize QpTableDlg::getMinimumSize() const
{
    return QSize(800,500);
}



//void QpTableDlg::eventFilter(QObject *obj, QEvent *event)
//{
//    if(event->type() == QEvent::Enter)
//    {
//        if(obj == mySizeGrip)
//        {
//            QRect rect = mySizeGrip->geometry();
//            Qt_upDown_icon->move( rect.right(), rect.bottom())
//                    Qt_upDown_icon->show();
//            //  etc.....
//        }
//    }
//}

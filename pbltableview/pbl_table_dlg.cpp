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

#include "pbl_table_dlg.h"
#include "ui_pbl_table_dlg.h"

#include "pbltableview.h"
#include <QMessageBox>
#include "some_tests.h"
#include <QDebug>
#include "config.h"
#include <QSqlError>
#include <QSqlDatabase>

#include "btn_toolbox.h"

PblTableDlg::PblTableDlg(
        const QString tableName,
        QSqlDatabase &Db,
        cb_setting_mdl p_cb_setting_mdl,
        cb_setting_view p_cb_setting_view,
        QWidget *parent,
        bool selectable,
        const QHash<QString,QVariant> &Filter,
        QSqlTableModel::EditStrategy edt
        )
    :
      QDialog(parent),
      ui(new Ui::PblTableDlg),
      chosenRow(-1),
      view(0),
      mdl(0)

{
    ui->setupUi(this);

    // ----------------------------------------------------
    //      direct ctor
    // ----------------------------------------------------

    setWindowTitle(tableName);

    mdl = new PblSqlRelationalTableModel( Db ,
                                          p_cb_setting_mdl,
                                          this);

    //qDebug() << " Filter " << Filter;

    if( ! mdl->prepare_mdl(tableName , QStringList(), Filter))
    {
        QMessageBox::critical(this ,
                              mySql::error_ ,
                              tr(
                                  "prepare table model is wrong\n"\
                                  "sql error: %3").
                              arg(mdl->lastError().text())
                              );
        return;
    }


    view = new PblTableView (
                this,
                p_cb_setting_view,
                selectable);



    if( ! view->prepare_view( mdl) ) //  !!
    {
        QMessageBox::critical(this ,
                              mySql::error_ ,
                              tr(
                                  "prepare table model is wrong\n"\
                                  "sql error: %3").
                              arg(mdl->lastError().text())
                              );
    }

    init( Db, editable, selectable);

}

// protected

PblTableDlg::PblTableDlg( const QString &tableName,
                          PblSqlRelationalTableModel *Mdl,
                          PblTableView *View,
                          QSqlDatabase &Db,
                          QWidget *parent,
                          cb_setting_mdl p_cbMdl,
                          cb_setting_view p_cbView,
                          bool selectable,
                          const QHash<QString,QVariant> Filter,
                          QSqlTableModel::EditStrategy edt)
    :
      QDialog(parent),
      ui(new Ui::PblTableDlg),
      chosenRow(-1),
      view(0),
      mdl(0)
{
    // -------------------------------------------------------
    //                  protected ctor
    // -------------------------------------------------------

    ui->setupUi(this);

    mdl = Mdl;//new PblSqlRelationalTableModel( Db , this);

    qDebug() << "PblTableDlg Filter " <<Filter;

    if( ! mdl->prepare_mdl(tableName , QStringList(), Filter ))
    {
        QMessageBox::critical(this,
                              mySql::error_,
                              tr("wrong table name : '%1").
                              arg(tableName)
                              );
        return;

    }
    view = View;

    if( ! view->prepare_view( mdl ) )
    {
        QMessageBox::critical(this,
                              mySql::error_,
                              tr("wrong init table, name : '%1").
                              arg(tableName)
                              );
        return;

    }

    init( Db, editable, selectable);

    _CONNECT_( view , SIGNAL(clicked(QModelIndex)),
               this, SLOT(slot_view_clicked(QModelIndex) ) );


}

void PblTableDlg::slot_view_clicked(QModelIndex idx)
{
    qDebug() << "PblTableDlg::slot_view_clicked";

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

bool PblTableDlg::init( QSqlDatabase &Db, bool editable, bool selectable)
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

    _CONNECT_(view->act_selectAndClose, SIGNAL(triggered()),
              this, SLOT(slot_accepted()));


    adjustSize();

    return true;

}

/*bool PblTableDlg::select()
{
    bool bbb = mdl->select();

    adjustSize();

    return bbb ;
}*/

PblTableDlg::~PblTableDlg()
{
    if(view !=0)
    {
        //qDebug() << "~PblTableDlgEx() delete view";
        delete view;
        view =0;
    }


    if(mdl !=0)
    {
        //qDebug() << "~PblTableDlgEx() delete mdl";
        delete mdl;
        mdl =0;
    }

    delete ui;
}


void PblTableDlg::slot_accepted()
{
    if(view == 0 | ! view->currentIndex().isValid())
        return;


    chosenRow = view->currentIndex().row();


    chosenRec = mdl->getPblSqlRecord(  mdl->record( chosenRow ) );

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


bool PblTableDlg::setRelation(PblSqlRelation &rel)
{

    return mdl->setRelation(rel);
}

QVBoxLayout * PblTableDlg::getUi()
{
    return ui->for_table_lo;
}


void PblTableDlg::on_btn_close_clicked()
{
    close();
}

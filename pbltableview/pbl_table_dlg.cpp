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

PblTableDlg::PblTableDlg(
        QSqlDatabase &db_,
        QWidget *parent,
        bool editable,
        bool selectable)
    :
      QDialog(parent),
      ui(new Ui::PblTableDlg),
      chosenRec(QSqlRecord()),
      chosenRow(-1),
      view(0),
      mdl(0)

{
    ui->setupUi(this);

    setSizeGripEnabled(true);

    if( ! db_.isOpen())
        return;

    db = db_;

    mdl = new PblSqlRelationalTableModel( db , this);

    view = new PblTableView ( mdl , ui->for_table_lo , db, this , editable , selectable);

    if(selectable)
    {
        // ----------------------------------------------------------
        //                       SELECT_AND_CLOSE
        // ----------------------------------------------------------

        view->act_selectAndClose = new QAction( PblTableView::getActIcon(PblTableView::ACT_SELECT_AND_CLOSE), trUtf8("select and close window"), this);

        view->act_selectAndClose->setShortcut(Qt::Key_F7);

        view->contextMenu->addAction(view->act_selectAndClose);

        view->addAction(view->act_selectAndClose);

        view->act_selectAndClose->setVisible(true);

        _CONNECT_(view->act_selectAndClose, SIGNAL(triggered()),
                  this, SLOT(slot_accepted()));

    }

    adjustSize();
}

/*bool PblTableDlg::set_Table(const QString &tableName)
{

    setWindowTitle("table : "+tableName);

    return mdl->set_Table(tableName);
}*/

bool PblTableDlg::select()
{
    return mdl->select();
}

PblTableDlg::~PblTableDlg()
{
    delete ui;
}

void PblTableDlg::slot_accepted()
{
    if(view == 0 | ! view->currentIndex().isValid())
        return;


    chosenRow = view->currentIndex().row();

    chosenRec = mdl->record(chosenRow);

    QSqlIndex pk = mdl->primaryKey();

    //qDebug() << " pk " << pk;

    if(pk.count() != 1)
    {
        QMessageBox::critical(this,
                              "error" ,
                              "not defined index field name in " + mdl->tableName());
        return;
    }

    //qDebug() << "    pk.name() " << pk.name() << pk.cursorName() << pk.fieldName(0);
    //qDebug("    pk.value(0) %i" , pk.value(pk.fieldName(0)) );

    //qDebug() << " chosenRec " <<chosenRec;

    chosenId = chosenRec.value(pk.fieldName(0)).toInt();

    //chosenName = mdl_.data(mdl_.index(chosenRow , tDescr_->defaultNameCol)).toString();

    //qDebug() << "my_table_Dlg::the_choice_is_made    " << objectName()<< " chosenId : " << chosenId << " chosenName" << chosenName;

    accept();

}

bool PblTableDlg::slot_doubleClicked(QString tableName)
{
    qDebug() << "PblTableDlg::slot_doubleClicked";
    return true;

}

bool PblTableDlg::setCalcField(CALC_COLUMN &calc)
{
    return mdl->setCalcField(calc);

}

bool PblTableDlg::setRelation(PblSqlRelation &rel)
{

    return mdl->setRelation(rel);
}

bool PblTableDlg::setRelations()
{

    return true;
}



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

#include "table_dlg.h"
#include "ui_table_dlg.h"

#include "pbltableview.h"
#include <QMessageBox>
#include "some_tests.h"
#include <QDebug>

Table_Dlg::Table_Dlg(const QString & tableName,
                     QSqlDatabase &db_,
                     QWidget *parent,
                     bool editable,
                     QList<CALC_COLUMN> &calcLst,
                     QList<PblSqlRelation> &relLst) :
    QDialog(parent),
    ui(new Ui::Table_Dlg),
    chosenRec(QSqlRecord()),
    chosenRow(-1)

{
    ui->setupUi(this);

    setSizeGripEnabled(true);

    if( ! QSqlDatabase::database().isOpen())
        return;

    db = db_;

    mdl = new PblSqlRelationalTableModel(this , db);

    mdl->set_Table(tableName);

    foreach( CALC_COLUMN calc , calcLst)
        mdl->setCalcField(calc);


    foreach( PblSqlRelation rel , relLst)
        mdl->setRelation(rel.col, rel);


    setWindowTitle("table : "+tableName);

    if( ! mdl->select())
    {
        QMessageBox::critical(this , tr("Error") , tr("set_Table '%1' return false").arg(tableName));
        return;
    }

    view = new PblTableView ( mdl , ui->for_table_lo , db, this , editable);

    _CONNECT_(view, SIGNAL(sig_rowSelected(QModelIndex)),
              this, SLOT(slot_accepted(QModelIndex)));

    adjustSize();

}


Table_Dlg::~Table_Dlg()
{
    delete ui;
}

/*void Table_Dlg::slot_selectCurrentRecord()
{
    QModelIndex index = view->currentIndex();

    if( ! index.isValid())
        return;

    slot_entered(index);

}*/

void Table_Dlg::slot_accepted(QModelIndex index)
{
    if( ! index.isValid())
        return;

    chosenRow = index.row();

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

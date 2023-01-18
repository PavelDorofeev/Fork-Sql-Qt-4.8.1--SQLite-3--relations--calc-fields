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

#ifndef PBL_TABLE_DLG_H
#define PBL_TABLE_DLG_H

#include <QDialog>
#include <QSqlRecord>
#include <QModelIndex>
#include "pbltableview/pblsqlrelationaltablemodel.h"
#include <QSqlDatabase>


namespace Ui {
class PblTableDlg;
}

class PblSqlRelationalTableModel;
class PblTableView;

class PblTableDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit PblTableDlg(//const QString & tableName,
                          QSqlDatabase &db,
                          QWidget *parent = 0,
                          bool editable=false,
                          bool selectable=false);

    virtual ~PblTableDlg();
    
    QSqlRecord chosenRec;
    int chosenRow;
    int chosenId;

    PblSqlRelationalTableModel * mdl;

    PblTableView * view;

    QSqlDatabase db;

    //virtual bool set_Table(const  QString &tableName);
    virtual bool select();

    virtual bool setCalcField(CALC_COLUMN &calc);
    virtual bool setRelation(PblSqlRelation &rel);
    virtual bool setRelations();


public slots:
    //void slot_selectCurrentRecord();

    void slot_accepted();

    bool slot_doubleClicked(QString tableName);

private slots:


private:
    Ui::PblTableDlg *ui;

};

#endif // PBL_TABLE_DLG_H

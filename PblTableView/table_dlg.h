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

#ifndef TABLE_DLG_H
#define TABLE_DLG_H

#include <QDialog>
#include <QSqlRecord>
#include <QModelIndex>
#include "pblsqlrelationaltablemodel.h"
#include <QSqlDatabase>

namespace Ui {
class Table_Dlg;
}

//class PblSqlRelationalTableModel;
class PblTableView;

class Table_Dlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit Table_Dlg(const QString & tableName,
                       QSqlDatabase &db,
                       QWidget *parent = 0,
                       bool editable=false,
                       QList<CALC_COLUMN> &calcLst = QList<CALC_COLUMN>(),
                       QList<PblSqlRelation> &relLst = QList<PblSqlRelation>());
    ~Table_Dlg();
    
    QSqlRecord chosenRec;
    int chosenRow;
    int chosenId;

    PblSqlRelationalTableModel * mdl;
    PblTableView * view;

    QSqlDatabase db;

public slots:
    //void slot_selectCurrentRecord();
    void slot_accepted(QModelIndex index);
private slots:


private:
    Ui::Table_Dlg *ui;

};

#endif // TABLE_DLG_H

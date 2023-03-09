/****************************************************************************
**
** Contact: BIT Ltd Company (p@kkmspb.ru) Individual Taxpayer Number (ITN)  7826152874
**
** This file is not part of the Qt.
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
**
**
****************************************************************************/

#ifndef PBLSQLRELATION_H
#define PBLSQLRELATION_H

#include <QString>

class PblSqlRelation
{
public:
    enum JoinMode {
        InnerJoin,
        LeftJoin
    };
    enum FLD_VALUE{
        FLD_UNDEFINED = -1
    };

public:
    PblSqlRelation(); //default

    PblSqlRelation operator=(const PblSqlRelation &other);


    explicit PblSqlRelation(
            int idField1,   // id field column in current table // id field in current table
            const QString &extTblName,                          // external table name
            const QString & idField2Name,                       // id field name in external table for bindind
            const QString & dstFldName,                         // text field name in external table for displaing in current table
            JoinMode join_mode = PblSqlRelation::LeftJoin,
            const QString & srvSubAcntOnFldName = ""
);

    ~PblSqlRelation();

    int col;

    JoinMode joinMode;

    int idField1;

    QString extTblName;

    QString idField2Name;   // QString (not int) because of in SELECT we dont know field names of ext relational table

    QString dstFldName; // QString (not int) because of in SELECT we dont know field names of ext relational table

    int displayType ;

    // ---------------------------------
    //     for sub accounting
    // ---------------------------------

    //QString subAccTblName;

    int subAcntColumn;

    int subPrntAcntColumn;

    QString srvSubAcntOnFldName;

    QString srvSubAcntParentFld;


    //const QString subAccountingTextName;

    // this creates a filter WHERE subAccountingField1=subAccountingField1




    // ---------------------------------
    //     parent binding
    // ---------------------------------

    //QString parentTblName;

    QString subAcntOnFld;

    void setSubAcntOnFld(const QString & SubAcntOnFld);


private:





};
#endif // PBLSQLRELATION_H

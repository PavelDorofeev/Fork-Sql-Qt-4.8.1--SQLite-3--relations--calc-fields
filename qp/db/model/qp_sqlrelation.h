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

#ifndef QP_SQLRELATION_H
#define QP_SQLRELATION_H

#include <QString>

class QpSqlRelation
{
public:
    enum JoinMode {
        InnerJoin,
        LeftJoin
    };
    enum FLD_VALUE{
        COL_UNDEFINED = -1
    };

public:

    static int counter;

    QpSqlRelation(); //default

    QpSqlRelation operator=(const QpSqlRelation &other);


    explicit QpSqlRelation(
            const QString & idField1Name,    // id field column in current table
            const QString & extTblName,   // external table name
            const QString & idField2Name, // id field name in external table for binding
            const QString & dstFldName,   // text field name in external table for displaing in current table
            JoinMode join_mode = QpSqlRelation::LeftJoin
);

    //PblSqlRelation &operator=(const PblSqlRelation &other);

    ~QpSqlRelation();


    JoinMode joinMode;

    const QString idField1Name;

    const QString extTblName;

    const QString idField2Name;

    const QString dstFldName;

    const QString ext_fld_name;


    QString get_fld_name();

    const QString & get_ext_fld_name() const;

private:


};
#endif // QP_SQLRELATION_H

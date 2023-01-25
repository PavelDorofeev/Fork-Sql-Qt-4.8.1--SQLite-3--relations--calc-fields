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
public:
    PblSqlRelation() {}

    explicit PblSqlRelation(
                   const int col,
                   int idField1,
                   const QString &ext_table,
                   QString idField2,
                   const QString &destField,
                   JoinMode join_mode = PblSqlRelation::LeftJoin);

    int col;

    JoinMode joinMode;

    int idField1;

    QString ext_table;

    QString idField2;

    QString destField;

private:





};
#endif // PBLSQLRELATION_H

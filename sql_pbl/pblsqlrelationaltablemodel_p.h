/****************************************************************************
**
** Contact: BIT Ltd Company (p@kkmspb.ru) Individual Taxpayer Number (ITN)  7826152874
**
** This file is not part of the Qt.
** This is a little fork of QSqlTableModel (Qt 4.8.1) version 3.0
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

#ifndef PBLSQLRELATIONALTABLEMODEL_P_H
#define PBLSQLRELATIONALTABLEMODEL_P_H

#include "models/qsqltablemodel_p.h"
#include "pblsqlrelationaltablemodel.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QSqlRecord;


class PblSqlRelationalTableModelPrivate: public QSqlTableModelPrivate
{
    Q_DECLARE_PUBLIC(PblSqlRelationalTableModel)
public:
    PblSqlRelationalTableModelPrivate()
        : QSqlTableModelPrivate()
    {}

    bool clearGeneratedFrom_cache(int row, int col);
    bool clearGeneratedFrom_editBuffer(int exCol);

    QString relationField(const QString &tableName, const QString &fieldName) const;

    mutable QHash<int , int> relations; // for translating to orig field names
    // relations 1 , 0 (индекс QList)

    mutable QList<PblColumn> ex_columns;

    QSqlRecord baseRec; // the record without relations

    void translateFieldNames(int row, QSqlRecord &values, QSqlTableModel::EditStrategy editStrategy) const;



};

QT_END_NAMESPACE

QT_END_HEADER

#endif // PBLSQLRELATIONALTABLEMODEL_P_H

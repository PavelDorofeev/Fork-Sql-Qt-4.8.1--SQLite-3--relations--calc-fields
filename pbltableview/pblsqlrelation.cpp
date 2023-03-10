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

#include "pblsqlrelation.h"
#include <QDebug>

PblSqlRelation::PblSqlRelation()
    :
      extTblName("undefined"),
      displayType(123)
{

    qDebug() << "ctor DEFAULT PblSqlRelation " << this;

}

PblSqlRelation::PblSqlRelation( int IdField1,
                                const QString & Table,
                                const QString & IdField2,
                                const QString & DestField,
                                JoinMode Join_mode)

    :

      idField1(IdField1),
      extTblName(Table),
      idField2Name(IdField2),
      dstFldName(DestField),
      col(IdField1),
      displayType(-1),
      subAcntColumn(FLD_UNDEFINED),
      subDisplayAcntColumn(FLD_UNDEFINED)

{
    joinMode = Join_mode;

    //qDebug() << "ctor PblSqlRelation extTblName " << extTblName << this;
}

PblSqlRelation::~PblSqlRelation()
{
    //qDebug() << "~PblSqlRelation extTblName " << extTblName << this;
}



PblSqlRelation PblSqlRelation::operator=(const PblSqlRelation &other)
{
    //qDebug() << "PblSqlRelation::operator=";

    displayType =234;
    //relation = other.relation;

    return *this;
};


void PblSqlRelation::setSubAcntOnFld(const QString & SubAcntOnFld)
{
    subAcntOnFld = SubAcntOnFld;
}


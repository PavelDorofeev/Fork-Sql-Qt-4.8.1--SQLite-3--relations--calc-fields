/****************************************************************************
**
** Contact: BIT Ltd Company (p@kkmspb.ru) Individual Taxpayer Number (ITN) 7826152874
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

#include "pblsqlrelationaltablemodel.h"

#include "qhash.h"
#include "qstringlist.h"
#include "qsqldatabase.h"
#include "qsqldriver.h"
#include "qsqlerror.h"
#include "qsqlfield.h"
#include "qsqlindex.h"
#include "qsqlquery.h"
#include "qsqlrecord.h"
#include <QMessageBox>
#include "pbltableview/my_sql.h"

#include "qdebug.h"

QT_BEGIN_NAMESPACE



PblSqlRelationalTableModel::PblSqlRelationalTableModel(QObject *parent, QSqlDatabase db_ ):
    QSqlTableModel( parent, db_),
    sortColumn(-1),
    sortOrder(Qt::AscendingOrder),
    isInsertingRow(-1)
{
    db = db_;
}


PblSqlRelationalTableModel::~PblSqlRelationalTableModel()
{
    //qDebug() << "dtor PblSqlRelationalTableModel " << tableName();
}

QVariant PblSqlRelationalTableModel::data(const QModelIndex &idx, int role) const
{

    int row = idx.row();

    int col = idx.column();
    int baseCount = baseRec.count();

    if( role == Qt::TextAlignmentRole)
        if( colInfo.contains(col))
            return colInfo.value(col).alignment;


    if( role != Qt::DisplayRole && role != Qt::UserRole )
    {
        return  QSqlTableModel::data(idx, role);
    }

    if(role == Qt::DisplayRole)
    {
        QVariant vv = QSqlTableModel::data(idx, role);

        if(vv.type() == QVariant::Double)
        {
            if( colInfo.contains(col))
            {
                return QString::number(vv.toDouble(),
                                       colInfo.value(col).cFormat,
                                       colInfo.value(col).precision) ;
            }

        }
    }

    return QSqlTableModel::data(idx, role);
}

void PblSqlRelationalTableModel::setEditStrategy(EditStrategy strategy)
{
    if(editStrategy() != strategy)
    {
        if( ! submitAll() )
        {
            QMessageBox::warning(0 , mySql::error , tr("Before sets new edit strategy we call submitAll and it returns false"));
            return;
        }
    }
    QSqlTableModel::setEditStrategy(strategy);
}

Qt::ItemFlags PblSqlRelationalTableModel::flags(const QModelIndex &index) const
{

    int col = index.column();
    int baseCount = baseRec.count();

    if(col >= baseCount) // extended columns will be unenabled and unseletable
    {
        int idxCol = col - baseCount;

        if(idxCol < ex_columns.count())
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
    }
    else if ( relations.contains(col) )
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    else
        return QSqlTableModel::flags(index);;
}

const QSqlRecord & PblSqlRelationalTableModel::baseRecord()
{

    return baseRec;
}


bool PblSqlRelationalTableModel::setDataForRelationField(const QModelIndex &idx,
                                                         const QVariant &value,
                                                         int role)
{

    if( ! idx.isValid())
        return false;

    if(role != Qt::EditRole)
        return QSqlTableModel::setData(idx, value, role);

    if(value.type() != QVariant::List) //  txt + id
    {
        qCritical("setData для поля relation д/б тип QList");
        return false;
    }

    int col = idx.column();
    int row = idx.row();

    // --------------------------------------------------------------
    //  In is nesasary QBVaiant type is List
    // --------------------------------------------------------------

    QList<QVariant> lst = value.toList();

    QVariant txt = lst.at(0);

    QVariant id = lst.at(1);

    int exCol = getRelIdColumn(col);

    QModelIndex idxEx = index(row , exCol);

    if( ! idxEx.isValid())
        return false;


    switch (editStrategy())
    {
    case OnFieldChange:
    {
        if ( ! QSqlTableModel::setData( idx, id, role )) // id
            // afterward will be called updateRowInTable and select
        {
            qCritical() << "error 4768975654" << lastError().text();
            return false;
        }
        return true;
    }
    case OnRowChange:
    {

        if ( ! QSqlTableModel::setData( idxEx, id , role ))
        {
            qCritical() << "error setData расширенное поле %" << exCol << lastError().text();
            return false;
        }


        if ( ! QSqlTableModel::setData( idx, txt, role )) // text
        {
            qCritical() << "error 47663736576" << lastError().text();
            return false;
        }
        return true;
    }
    case OnManualSubmit:
    {
        // устанавливается расширенное поле

        if ( ! QSqlTableModel::setData( idxEx, id , role ))
        {
            qCritical() << "error setData расширенное поле %" << exCol << lastError().text();
            return false;
        }


        if ( ! QSqlTableModel::setData(idx, txt, role)) // txt
        {
            qCritical("         error 4768975654");
            return false;
        }
        // far is calling updateRowInTable and select
        return true;

    }
    }

    return false;
}

bool PblSqlRelationalTableModel::setData(const QModelIndex &idx,
                                         const QVariant &value,
                                         int role)
{
    if( ! idx.isValid())
        return false;


    if(role != Qt::EditRole)
        return QSqlTableModel::setData(idx, value, role);

    // next is only EditRole

    int col = idx.column();
    int row = idx.row();


    if(relations.contains(col))
    {
        return setDataForRelationField(idx , value, role);
    }

    return QSqlTableModel::setData(idx, value, role);
}


bool PblSqlRelationalTableModel::setRelation(const PblSqlRelation &relation)
{
    if (relation.col < 0)
        return false;

    if(relations.contains(relation.col))
    {
        qCritical() << tr("PblSqlRelationalTableModel::setRelation This is a second trying setRelation for column number : %1 ").arg(relation.col);
        return false;
    }

    int newRelIdCol = baseRec.count() + ex_columns.count();


    PblColumn exCol = PblColumn(relation,
                                newRelIdCol);
    ex_columns.append(exCol);

    int ex_cols = ex_columns.count();

    relations.insert(relation.col ,newRelIdCol);

    return true;
}

bool PblSqlRelationalTableModel::setCalcField(CALC_COLUMN & calc)
{
    if(tableName().isNull() || tableName().isEmpty())
    {
        qCritical() << "missing call setTable() before setCalcField";
        return false;
    }

    if(calc.table.isEmpty() || calc.table.isNull())
        return false;

    if(calc.idField1.isEmpty() || calc.idField1.isNull())
        return false;

    if(calc.idField2.isEmpty() || calc.idField2.isNull())
        return false;

    if(calc.calcFunc.isEmpty() || calc.calcFunc.isNull())
        return false;

    int count = ex_columns.count();

    ex_columns.append(PblColumn(calc,
                                count));


    return true;
}

QString PblSqlRelationalTableModel::relationField(const QString &tableName,
                                                  const QString &fieldName) const
{
    QString ret;

    ret.reserve(tableName.size() + fieldName.size() + 1);

    ret.append(tableName).append(QLatin1Char('.')).append(fieldName);

    return ret;
}



bool PblSqlRelationalTableModel::select()
{
    //qDebug() << "PblSqlRelationalTableModel::select()";

    if ( ! QSqlTableModel::select())
        return false;

    isInsertingRow = -1;

    // ------------------------------------------------------------
    //  rename extended fields headers if you want
    // ------------------------------------------------------------

    int origColumnCount = record().count();

    for(uint exCol=0; exCol < ex_columns.count(); exCol++)
    {
        QString header = ex_columns.value(exCol).renamedField_As;

        if( header != QString())
        {
            bool b =setHeaderData( origColumnCount + exCol, Qt::Horizontal, header);
        }
    }

    return true;
}

bool PblSqlRelationalTableModel::set_Table(const QString &table)
{

    QSqlTableModel::setTable(table);

    relations.clear();

    ex_columns.clear();

    colInfo.clear();

    if(! db.isValid() || ! db.isOpen())
    {
        QMessageBox::critical(0 , mySql::error , tr("database is not opened!"));
        return false;
    }

    baseRec = db.record(table);

    if(baseRec.isEmpty())
    {
        QMessageBox::critical(0 , mySql::error , tr("table '%1'! is not valid").arg(table));
        return false;
    }


    qDebug() <<"baseRec " << baseRec;

    return true;
}


void PblSqlRelationalTableModel::translateFieldNames(
        int row,
        QSqlRecord &rec,
        QSqlTableModel::EditStrategy editStrategy) const
{
    // Эта функция возвращает наименования полей к оригинальным
    // в SELECT наименование полей через as могут быть изменены
    // например для INSERT ROW нужны оригинальные поля

    for( QHash<int,int>::const_iterator ii = relations.begin(); ii!=relations.end(); ++ii)
    {
        int col = ii.key();
        int exCol = ii.value();

        //qDebug() << " rec \n\n" << rec;
        //qDebug() << " rec.field(col) \n" << rec.field(col);
        bool gen = rec.field(col).isGenerated();

        if(gen)
        {
            // if QSqlTableModel::OnFieldChange than in col place int id

            QString name = baseRec.field( col ).name(); // заменяем наименования полей на базовые

            QVariant val;
            if ( editStrategy == QSqlTableModel::OnFieldChange)
                val = rec.value(col); // оставляем значение поля как есть (int id)
            else
                val = rec.value(exCol); // подмена текста поля на int id

            QSqlField ff = rec.field( col );

            ff.setName(name);
            ff.setValue(val);
            ff.setGenerated(gen);

            rec.replace( col , ff );

        }

        if(rec.field( exCol ).isGenerated())
        {
            rec.setGenerated(exCol , false );
            //rec.setValue(col , rec.value(exCol));
        }
    }
}

bool PblSqlRelationalTableModel::updateRowInTable(int row, const QSqlRecord &values)
{

    // ----------------------------------------------------------------------
    // We changed field names to original as in table were
    // text filed values of relation field need to replaces with id values
    // By the way SQLITE succesful writing a text  into int field
    // ----------------------------------------------------------------------

    QSqlRecord rec = values;

    // replace to original table field names
    // set generated no to relational id fields
    translateFieldNames(row, rec, editStrategy());

    return QSqlTableModel::updateRowInTable(row, rec);
}

bool PblSqlRelationalTableModel::insertRowIntoTable(const QSqlRecord &values)
{
    QSqlRecord rec = values;

    // replace to original table field names
    // set generated no to relational id fields
    translateFieldNames(0, rec, editStrategy());

    //qDebug() << "PblSqlRelationalTableModel::insertRowIntoTable rec " << rec;

    return QSqlTableModel::insertRowIntoTable(rec);

}


QString PblSqlRelationalTableModel::orderByClause() const
{

    if( sortColumn >= 0 && relations.contains(sortColumn))
    {

        // ----------------------------------------------------------
        //      sorting by column with a relation
        // ----------------------------------------------------------

        PblColumn exCol = ex_columns.value( relations.value(sortColumn) - baseRec.count());

        if(exCol.type == PblColumn::COLUMN_TYPE_RELATION_ID)
        {
            // for relational fields

            QString s = QLatin1String("\nORDER BY ");

            s.append(relationField(
                         QLatin1String("relTblAl_") + QString::number(sortColumn),
                         exCol.destField));

            s += sortOrder == Qt::AscendingOrder ? QLatin1String(" ASC") : QLatin1String(" DESC");

            return s;
        }
        else
            return QSqlTableModel::orderByClause();
    }
    else if( sortColumn >= baseRec.count() ) // ex_col
    {
        // ----------------------------------------------------------
        //      sorting by extended columns
        // ----------------------------------------------------------

        int excolIdx = sortColumn - baseRec.count();

        if(excolIdx < ex_columns.count())
        {
            PblColumn exColData = ex_columns.value(excolIdx);

            QString s = QLatin1String(" ORDER BY ");

            PblColumn::COLUMN_TYPE type = ex_columns.value(excolIdx).type;

            if( type == PblColumn::COLUMN_TYPE_CALCULATION)
            {

                s.append( exColData.renamedField_As);

                s += sortOrder == Qt::AscendingOrder ? QLatin1String(" ASC") : QLatin1String(" DESC");

                return s;
            }
            else if( type == PblColumn::COLUMN_TYPE_RELATION_ID)
            {

                s.append( QString::fromLatin1("relTblAl_%1.").arg(exColData.origCol));

                s.append( exColData.idField1);

                s += sortOrder == Qt::AscendingOrder ? QLatin1String(" ASC") : QLatin1String(" DESC");

                return s;
            }
        }
        return QString();
    }
    else
        return QSqlTableModel::orderByClause();
}




QString PblSqlRelationalTableModel::selectStatement() const
{
    QString query;

    if (tableName().isEmpty())
        return query;

    QString sTablesList;
    QString sFieldsList;
    QString where;

    QStringList lstTables;


    bool bFieldsFullName = false;

    if( ex_columns.count()>0)
        bFieldsFullName = true;

    //-------------------------------------------------------
    //                STANDART FIELDS
    //-------------------------------------------------------

    int baseCount = baseRec.count();

    for (int col = 0; col < baseCount; ++col)
    {
        QString name;

        if (relations.contains(col))
        {
            int exNumCol =  relations.value(col);

            if(exNumCol - baseCount < ex_columns.count())
            {

                PblColumn exCol = ex_columns.value(exNumCol - baseCount);

                if (exCol.type == PblColumn::COLUMN_TYPE_RELATION_ID)
                {
                    PblColumn exCol = ex_columns.value(exNumCol - baseCount);

                    QString relTableAlias = QString::fromLatin1("relTblAl_%1").arg(col);

                    name = QString(relationField(relTableAlias , exCol.destField)).
                            append(QString::fromLatin1(" AS %1_%2_%3").
                                   arg(exCol.idField1).
                                   arg(col).
                                   arg(exCol.destField));

                }
            }
        }
        else
        {
            name = baseRec.fieldName(col);

            if( bFieldsFullName )
                name.prepend(QLatin1String(".")).prepend(tableName());
        }


        if( ! sFieldsList.isEmpty())
            sFieldsList.append(QLatin1String(",\n"));

        sFieldsList.append(name);

    }

    //qDebug() << "\nsFieldsList " << sFieldsList;

    QString sAddFields;

    //-------------------------------------------------------
    //                      EXT TEXT / CALC
    //-------------------------------------------------------

    QString sExtFieldNameAdds;
    int groupBy = 0;

    for(int col=0; col < ex_columns.count(); col++)
    {
        PblColumn exCol = ex_columns.at(col);

        if(exCol.type == PblColumn::COLUMN_TYPE_RELATION_ID)
        {
            QString relTableAlias = QString::fromLatin1("relTblAl_%1").arg(exCol.origCol);

            sAddFields.append(QString::fromLatin1(",\n %1.%2 AS %3_%4_%5").
                              arg(relTableAlias).
                              arg(exCol.idField1).
                              arg(exCol.table).
                              arg( exCol.origCol ).
                              arg(exCol.idField1));


        }
        else if(exCol.type == PblColumn::COLUMN_TYPE_CALCULATION)
        {
            QStringList lst = exCol.destField.split(QLatin1String(","));

            QString fields;

            sExtFieldNameAdds.
                    append(QLatin1String(", \n")).
                    append(exCol.funcName).
                    append(QLatin1String("("));

            for(int ii=0; ii < lst.count(); ii++) // this is a sum by some fields
            {

                sExtFieldNameAdds.
                        append(exCol.table).
                        append(QLatin1String(".")).
                        append(lst.at(ii));

                if(exCol.renamedField_As.isEmpty())
                    fields.append(lst.at(ii));

                if(ii < lst.count() -1)
                {
                    sExtFieldNameAdds.append(QLatin1String(" + "));

                    if(exCol.renamedField_As.isEmpty())
                        fields.append(QLatin1String("_"));
                }
            }
            sExtFieldNameAdds.append(QLatin1String(") as "));

            if(exCol.renamedField_As.isNull())
                sExtFieldNameAdds.append(exCol.table).append(QLatin1String("_")).append(fields);
            else
                sExtFieldNameAdds.append(exCol.renamedField_As);

            groupBy++;
        }
    }

    QString sExtLeftJoins;
    QStringList joinedTables;

    //-------------------------------------------------------
    //                      JOIN
    //-------------------------------------------------------

    for(int ii=0; ii < ex_columns.count(); ii++)
    {
        PblColumn addCol = ex_columns.at(ii);

        if( addCol.type == PblColumn::COLUMN_TYPE_RELATION_ID)
        {

            if( ! joinedTables.contains(addCol.table))
            {

                QString relTableAlias = QString::fromLatin1("relTblAl_%1").arg(addCol.origCol);

                sExtLeftJoins.append(QLatin1String(" \nLEFT JOIN ")).
                        append(addCol.table).
                        append(QLatin1String(" ")).
                        append(relTableAlias).

                        append(QLatin1String(" ON ")).

                        append(tableName()).append(QLatin1String(".")).
                        append(addCol.idField1).

                        append(QLatin1String("=")).

                        append(relTableAlias).append(QLatin1String(".")).
                        append(addCol.idField2);

                joinedTables.append(addCol.table);
            }
        }
        else  if( addCol.type == PblColumn::COLUMN_TYPE_CALCULATION)
        {
            if( ! joinedTables.contains(addCol.table))
            {
                sExtLeftJoins.append(QLatin1String(" \nLEFT JOIN ")).
                        append(addCol.table).
                        append(QLatin1String(" ")).

                        append(QLatin1String(" ON ")).

                        append(tableName()).append(QLatin1String(".")).
                        append(addCol.idField1).

                        append(QLatin1String("=")).

                        append(addCol.table).append(QLatin1String(".")).
                        append(addCol.idField2);

                joinedTables.append(addCol.table);
            }
        }
    }

    //------------------------------------------------------------

    sTablesList.append(lstTables.join(QLatin1String(" ")));

    if (sFieldsList.isEmpty())
    {
        qCritical() << tr("PblSqlRelationalTableModel::selectStatement() field list is empty");

        return query;
    }

    sTablesList.prepend(tableName());
    query.append(QLatin1String("\n\nSELECT "));

    if( ! sExtFieldNameAdds.isEmpty())
    {
        sFieldsList.append(sExtFieldNameAdds);
    }


    query.append(sFieldsList).append(sAddFields).append(QLatin1String(" \nFROM ")).append(sTablesList);


    if( ! sExtLeftJoins.isEmpty())
    {
        query.append(sExtLeftJoins);
    }

    // --------------------- WHERE ------------------------

    if ( ! filter().isEmpty() )
    {

        query.append(QLatin1String(" \nWHERE ("));
        query.append(filter());
        query.append(QLatin1String(")"));
    }

    // ---------------------- GROUP BY -------------------------

    if( groupBy>0)
    {
        query.append(QLatin1String(" \nGROUP BY ")).append(tableName()).append(QLatin1String(".id"));
    }

    // ---------------------- ORDER -------------------------

    QString orderBy = orderByClause();

    if (!orderBy.isEmpty())
        query.append(QLatin1Char('\n')).append(orderBy);

#ifdef  PBL_SQL_DEBUG
    //qDebug() << "\nselectStatement : \n" << query;
#endif

    return query;
}

void PblSqlRelationalTableModel::setAlignment(int col , Qt::Alignment align)
{
    colInfo[col].alignment = align;
}

void PblSqlRelationalTableModel::setPrecision(int col , int precision)
{
    colInfo[col].precision = precision;

}

void PblSqlRelationalTableModel::setDblFormat(int col , char ch)
{
    colInfo[col].cFormat = ch;

}

PblColumn::COLUMN_TYPE PblSqlRelationalTableModel::exColType(int exCol)
{

    //qDebug() << "PblSqlRelationalTableModel::exColType " << exCol;

    if(exCol < ex_columns.count())
    {
        PblColumn::COLUMN_TYPE tt = ex_columns[exCol].type;
        return tt;
    }
    return PblColumn::COLUMN_TYPE_UNKNOUWN;
}


PblColumn PblSqlRelationalTableModel::getRelationInfoForColumn(int col)
{

    if( ! relations.contains(col))
        return PblColumn();

    int exCol = relations.value(col);

    if(exCol - baseRec.count() < ex_columns.count())
    {
        return ex_columns.value(exCol - baseRec.count());
    }
    return PblColumn();
}


int PblSqlRelationalTableModel::getRelIdColumn(int relCol)
{
    if(relations.contains(relCol))
        return relations.value(relCol);
    else
        return -1;
}

PblColumn::COLUMN_TYPE PblSqlRelationalTableModel::columnType(int col)
{
    if(relations.contains(col))
        return PblColumn::COLUMN_TYPE_RELATION_TEXT;
    else
    {
        if(col > baseRec.count()) // extended column
        {
            int idxCol = col - baseRec.count();

            if ( idxCol < ex_columns.count() )
                return ex_columns.value(idxCol).type;
        }

    }

    return PblColumn::COLUMN_TYPE_UNKNOUWN;
}



void PblSqlRelationalTableModel::setSort(int column, Qt::SortOrder order)
{
    //qDebug() << "setSort "<< column;

    sortColumn = column;
    sortOrder = order;

    QSqlTableModel::setSort(column , order);

}


QT_END_NAMESPACE

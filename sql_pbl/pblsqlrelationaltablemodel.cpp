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

#include "pblsqlrelationaltablemodel.h"
#include "D:\DEVELOPMENT\QT4\_MY__\my_lib\common\my_sql.h"

#include "qhash.h"
#include "qstringlist.h"
#include "qsqldatabase.h"
#include "qsqldriver.h"
#include "qsqlerror.h"
#include "qsqlfield.h"
#include "qsqlindex.h"
#include "qsqlquery.h"
#include "qsqlrecord.h"

#include "models/qsqltablemodel_p.h"
#include "pblsqlrelationaltablemodel_p.h"

#include "qdebug.h"

QT_BEGIN_NAMESPACE



PblColumn::PblColumn(COLUMN_TYPE rel_Type,
                     const QString &exTableName_,
                     const QString &exIndexField_,
                     const QString &exTextField_,
                     const QString &funcName,
                     int origCol_,
                     int exCol_,

                     const QString renamedField_As_):
    exTableName(exTableName_),
    exIndexFieldName(exIndexField_),
    exTextFieldName(exTextField_),
    exFuncName(funcName),
    renamedField_As(renamedField_As_),
    cFormat(0),
    precision(0),
    alignment(Qt::AlignRight)
{
    type = rel_Type;
    origCol = origCol_;
    exCol = exCol_;

}

bool PblColumn::isValid()
{
    if( ! exTableName.isEmpty()
            && ! exIndexFieldName.isEmpty()
            && ! exTextFieldName.isEmpty())
        return true;

    return false;
}


PblSqlRelationalTableModel::PblSqlRelationalTableModel(QObject *parent, QSqlDatabase db):
    QSqlTableModel(*new PblSqlRelationalTableModelPrivate, parent, db)
{

}

PblSqlRelationalTableModel::PblSqlRelationalTableModel(PblSqlRelationalTableModelPrivate &dd,
                                                       QObject *parent,
                                                       QSqlDatabase db)
    : QSqlTableModel(dd,
                     parent,
                     db)
{

}

PblSqlRelationalTableModel::~PblSqlRelationalTableModel()
{
    qDebug() << "dtor PblSqlRelationalTableModel " << tableName();
}


PblSqlRecord PblSqlRelationalTableModel::record(int row) const
{
    //qDebug() << "PblSqlRecord pblRec = QSqlQueryModel::record("<<row<<")";

    /*
        copy ctor
    */

    //PblSqlRecord pblRec(QSqlTableModel::record(row));
    PblSqlRecord pblRec = QSqlTableModel::record(row);
    //qDebug("pblRec %p ", pblRec) ;

    // тоже вариант
    // PblSqlRecord pblRec = reinterpret_cast<PblSqlRecord&>(QSqlQueryModel::record(row));

    if(pblRec.isEmpty())
    {
        qCritical() << "PblSqlRelationalTableModel::record Why is empty?";
        return pblRec;
    }

    //qDebug(" pblRec %p pblRec.exRelFieldsMap.count()=%i " , pblRec, pblRec.exRelFieldsMap.count());


    //createRelColumnMap(pblRec); // create map of columns relations


    Q_D(const PblSqlRelationalTableModel);

    foreach(PblColumn exCol, d->ex_columns )
    {
        if (exCol.type == PblColumn::COLUMN_TYPE_RELATION_ID)
        {
            pblRec.appendExCol(exCol.origCol , exCol.exCol);
        }
    }
    pblRec.origСolCount = d->baseRec.count();

    //qDebug(" pblRec %p pblRec.exRelFieldsMap.count()=%i " , pblRec, pblRec.exRelFieldsMap.count());

    return pblRec;
}

bool PblSqlRelationalTableModel::createRelColumnMap(PblSqlRecord& pblRec)
{
    return true;
}

PblSqlRecord PblSqlRelationalTableModel::record()
{
    //qDebug() << "PblSqlRelationalTableModel::record() ";

    //PblSqlRecord pblRec(QSqlQueryModel::record());
    PblSqlRecord pblRec(QSqlTableModel::record());
    //PblSqlRecord &pblRec = QSqlTableModel::record();

    createRelColumnMap(pblRec);

    return pblRec;
}

QVariant PblSqlRelationalTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant vv =QSqlTableModel::headerData(section , orientation , role);

    /*if( ! vv.isNull())
        qDebug() << "PblSqlRelationalTableModel::headerData:\n\t   section : " << section << " orientation:" <<orientation << " role: " << mySql::roleToStr(role) << " " <<vv;*/



    return vv;

}


QVariant PblSqlRelationalTableModel::data(const QModelIndex &idx, int role) const
{
    Q_D(const PblSqlRelationalTableModel);

    int row = idx.row();

    int col = idx.column();
    int max = d->baseRec.count();

    if( role != Qt::DisplayRole
            && role != Qt::UserRole )//  && filterDone.col >=0)
    {
        QVariant vv = QSqlTableModel::data(idx, role);//::Color;

        //qDebug() << "data() value = " << vv << " role :" <<mySql::roleToStr(role) << " row : " << row << " col : " << col ;

        return  vv;//QBrush(QColor(Qt::red));
    }

    if(col >= max )
    {
        int exCol = col - max;

        if( exCol < d->ex_columns.count())
        {
            if(role == Qt::TextAlignmentRole)
            {
                if(d->ex_columns[exCol].alignment != 0)
                    return d->ex_columns[exCol].alignment;

            }
            else if(role == Qt::DisplayRole)
            {
                char ch = d->ex_columns.at(exCol).cFormat;

                if( ch != 0)
                {
                    QVariant vv = QSqlTableModel::data(idx, role);

                    if(vv.type() == QVariant::Double)
                    {
                        return QString::number(vv.toDouble(),
                                               d->ex_columns.at(exCol).cFormat,
                                               d->ex_columns.at(exCol).precision) ;
                    }
                    return vv;
                }
            }
        }

        return QSqlTableModel::data(idx, role);
    }

    return QSqlTableModel::data(idx, role);
}

Qt::ItemFlags PblSqlRelationalTableModel::flags(const QModelIndex &index) const
{
    Q_D(const PblSqlRelationalTableModel);

    int col = index.column();
    int max = d->baseRec.count();

    if(col >= max) // extended columns will be unenabled and unseletable
    {
        int add = col - max;

        if(add < d->ex_columns.count())
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
    }
    else if ( d->relations.contains(col) )
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    else
        return QSqlTableModel::flags(index);;
}

const QSqlRecord & PblSqlRelationalTableModel::baseRecord()
{
    Q_D(const PblSqlRelationalTableModel);

    return d->baseRec;
}


bool PblSqlRelationalTableModel::setDoubleFormat(int exCol,
                                                 const char &format,
                                                 const int &precision)
{
    Q_D(const PblSqlRelationalTableModel);

    if(exCol >=0 && exCol < d->ex_columns.count())
    {

        d->ex_columns.value(exCol).setFormat(format , precision);
        return true;
    }
    return false;

}

bool PblSqlRelationalTableModel::setDataForRelation(const QModelIndex &idx,
                                                    const QVariant &value,
                                                    int role)
{

    if( ! idx.isValid())
        return false;

    if(role != Qt::EditRole)
        return QSqlTableModel::setData(idx, value, role);

    if(value.type() != QVariant::List) // значит txt + id
    {
        qCritical("setData для поля relation д/б тип QList");
        return false;
    }

    Q_D(PblSqlRelationalTableModel);

    int col = idx.column();
    int row = idx.row();

    // --------------------------------------------------------------
    //  ОБЯЗАТЕЛЬНО тип должен быть QList (пара значений текст и id)
    // --------------------------------------------------------------

    QList<QVariant> lst = value.toList();

    QVariant txt = lst.at(0);

    QVariant id = lst.at(1);

    int exCol = d->relations.value(col) +d->baseRec.count();

    QModelIndex idxEx = index(row , exCol);

    if( ! idxEx.isValid())
        return false;


    switch (d->strategy)
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
        // устанавливается расширенное поле

        if ( ! QSqlTableModel::setData( idxEx, id , role ))
        {
            qCritical() << "error setData расширенное поле %" << exCol << lastError().text();
            return false;
        }

        /*if ( ! d->clearGeneratedFrom_editBuffer(exCol))
        {
            qCritical("error clearGeneratedFromEditBuffer расширенное поле %i" ,exCol);
            return false;
        }*/

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

        /*if ( ! d->clearGeneratedFrom_cache(row , exCol)) // обязательно снимаем флаг genereated
        {
            qCritical("error clearGeneratedFromCache расширенное поле %i" ,exCol);
            return false;
        }*/

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
    Q_D(PblSqlRelationalTableModel);

    if( ! idx.isValid())
        return false;


    if(role != Qt::EditRole)
        return QSqlTableModel::setData(idx, value, role);

    // next is only EditRole

    int col = idx.column();
    int row = idx.row();

    int origColCount = d->baseRec.count();

    if (col >= origColCount) // extended cols
    {
        if(editStrategy() == QSqlTableModel::OnFieldChange)
        {
            qWarning()<< "setData for extended column " << col <<" is not needs by OnFieldChange strategy";
            return false;
        }
        return setDataOnlyIntoEditBuffer(idx , value ,role);
    }
    else if(col < origColCount) // original fields
    {

        if(d->relations.contains(col))  // внешняя связь
        {
            return setDataForRelation(idx , value, role);
        }

        return QSqlTableModel::setData(idx, value, role);
    }


    return QSqlTableModel::setData(idx, value, role);
}


bool PblSqlRelationalTableModel::setRelation(int origCol,
                                             const PblSqlRelation &relation)
{
    Q_D(PblSqlRelationalTableModel);

    if (origCol < 0)
        return false;

    int exCount = d->ex_columns.count();
    int origCount = d->baseRec.count();

    if(d->relations.contains(origCol))
    {
        qCritical() << "PblSqlRelationalTableModel::setRelation This is a second trying setRelation for column number : " << origCol;
        return false;
    }

    int count = origCount + d->ex_columns.count();

    //qDebug() << relation.tableFrom() << relation.indexFieldFrom() <<relation.displayFieldFrom();

    PblColumn exCol = PblColumn(PblColumn::COLUMN_TYPE_RELATION_ID,
                                relation.tableFrom(),
                                relation.indexFieldFrom(),
                                relation.displayFieldFrom(),
                                QString(),
                                origCol,
                                count,
                                QString()
                                );
    d->ex_columns.append(exCol);

    int ex_cols = d->ex_columns.count();

    d->relations.insert(origCol , ex_cols - 1);

    return true;
}

bool PblSqlRelationalTableModel::setCalcField(CALC_COLUMN & calc)
/* const QString &tableFrom,
                                              const QString foreignKeyField,
                                              const QString &fieldFrom,
                                              const QString &funcName,
                                              const QString fieldNameTo
                                              )*/
{
    if(tableName().isNull() || tableName().isEmpty())
    {
        qCritical() << "missing call setTable() before setCalcField";
        return false;
    }

    Q_D(PblSqlRelationalTableModel);

    if(calc.table.isEmpty() || calc.table.isNull())
        return false;

    if(calc.idField1.isEmpty() || calc.idField1.isNull())
        return false;

    if(calc.calcFuncName.isEmpty() || calc.calcFuncName.isNull())
        return false;

    int count = d->ex_columns.count();

    d->ex_columns.append(PblColumn(
                             PblColumn::COLUMN_TYPE_CALCULATION,
                             calc.table,
                             calc.idField2,
                             calc.idField1,
                             calc.calcFuncName,
                             -1,
                             count,
                             calc.calcFuncName_As));


    return true;
}

bool PblSqlRelationalTableModelPrivate::clearGeneratedFrom_editBuffer(int exCol)
{
    if( exCol<0 || exCol >= editBuffer.count())
        return false;

    QSqlRecord &rec = editBuffer;

    rec.setGenerated( exCol , false);

    return true;
}


bool PblSqlRelationalTableModelPrivate::clearGeneratedFrom_cache(int row, int exCol)
{
    if( ! cache.contains(row))
        return false;

    QSqlTableModelPrivate::ModifiedRow &mRow = cache[row];

    QSqlRecord &rec = mRow.rec;

    if( exCol < 0 || exCol >= rec.count() )
        return false;


    rec.setGenerated( exCol , false);

    return true;
}

QString PblSqlRelationalTableModelPrivate::relationField(const QString &tableName,
                                                         const QString &fieldName) const
{
    QString ret;

    ret.reserve(tableName.size() + fieldName.size() + 1);

    ret.append(tableName).append(QLatin1Char('.')).append(fieldName);

    return ret;
}



bool PblSqlRelationalTableModel::select()
{
    Q_D(PblSqlRelationalTableModel);

    //qDebug() << "PblSqlRelationalTableModel::select()";

    if ( ! QSqlTableModel::select())
        return false;

    // ------------------------------------------------------------
    //  rename extended fields headers if you want
    // ------------------------------------------------------------

    int origColumnCount = d->rec.count();

    for(uint exCol=0; exCol < exColCount(); exCol++)
    {
        QString header = exColName(exCol);

        if( header != QString())
        {
            bool b =setHeaderData( origColumnCount + exCol, Qt::Horizontal, header);
        }
    }

    return true;
}

void PblSqlRelationalTableModel::setTable(const QString &table)
{
    Q_D(PblSqlRelationalTableModel);

    d->baseRec = d->db.record(table);

    d->relations.clear();

    d->ex_columns.clear();

    QSqlTableModel::setTable(table);
}


void PblSqlRelationalTableModelPrivate:: translateFieldNames(
        int row,
        QSqlRecord &rec,
        QSqlTableModel::EditStrategy editStrategy) const
{
    // Эта функция возвращает наименования полей к оригинальным
    // в SELECT наименование полей через as могут быть изменены
    // например для INSERT ROW нужны оригинальные поля

    for( QHash<int,int>::iterator ii = relations.begin(); ii!=relations.end(); ++ii)
    {
        int col = ii.key();
        int exCol = ii.value() + baseRec.count();

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

void PblSqlRelationalTableModel::printQRec(const QSqlRecord &rec, const QString txt )
{

#ifdef  PBL_SQL_DEBUG
    if(txt==0)
        qDebug() << "-------------------------------";
    else
        qDebug() << "----- " << txt <<" ------";

    for( int ii=0; ii < rec.count(); ii++ )
    {
        if(rec.isGenerated(ii))
            qDebug() << "    "<< rec.value(ii) << "\t"<<rec.field(ii);
    }
    qDebug() << "------------------";
#endif
}

bool PblSqlRelationalTableModel::updateRowInTable(int row, const QSqlRecord &values)
{
    Q_D(PblSqlRelationalTableModel);

    //qDebug() << "\n\nPblSqlRelationalTableModel::updateRowInTable values " << values<< "\n";

    // ----------------------------------------------------------------------
    // тут relations оригинальные поля представлены как текстовые
    // их надо ОБЯЗАТЕЛЬНО заменить на id из ex колонок
    // SQLITE КСТАТИ ПРЕКРАСНО ЗАПИШЕТ ТЕКС В ПОЛЕ INT
    // ----------------------------------------------------------------------

    QSqlRecord rec = values;

    d->translateFieldNames(row, rec, editStrategy());
    // возврат к оригинальным наименованиям полей

    //qDebug() << "\n\nPblSqlRelationalTableModel::updateRowInTable rec " << rec<< "\n";

    return QSqlTableModel::updateRowInTable(row, rec);
}

bool PblSqlRelationalTableModel::insertRowIntoTable(const QSqlRecord &values)
{
    // const QSqlRecord &values  delete const is not possible (because of virtual function)

    Q_D(PblSqlRelationalTableModel);

    //qDebug() << "PblSqlRelationalTableModel::insertRowIntoTable values " << values;

    QSqlRecord rec = values;

    d->translateFieldNames(0, rec, editStrategy()); // возврат к оригинальным наименованиям полей

    //qDebug() << "PblSqlRelationalTableModel::insertRowIntoTable rec " << rec;

    return QSqlTableModel::insertRowIntoTable(rec);

}


QString PblSqlRelationalTableModel::orderByClause() const
{
    Q_D(const PblSqlRelationalTableModel);

    //qDebug() << " d->sortColumn " << d->sortColumn;

    if( d->relations.contains(d->sortColumn) ) // ex_col
    {
        // ----------------------------------------------------------
        //      sorting by column with a relation
        // ----------------------------------------------------------

        PblColumn exCol = d->ex_columns.value(d->relations.value(d->sortColumn));

        if(exCol.type == PblColumn::COLUMN_TYPE_RELATION_ID)
        {
            // for relational fields

            QString s = QLatin1String("\nORDER BY ");

            s.append(d->relationField(
                         QLatin1String("relTblAl_") + QString::number(d->sortColumn),
                         exCol.exTextFieldName));

            s += d->sortOrder == Qt::AscendingOrder ? QLatin1String(" ASC") : QLatin1String(" DESC");

            return s;
        }
    }
    else if( d->sortColumn >= d->baseRec.count() ) // ex_col
    {
        // ----------------------------------------------------------
        //      sorting by extended columns
        // ----------------------------------------------------------

        int excolIdx = d->sortColumn - d->baseRec.count();

        if(excolIdx < d->ex_columns.count()
                && d->ex_columns.value(excolIdx).type == PblColumn::COLUMN_TYPE_CALCULATION)
        {

            PblColumn exColData = d->ex_columns.value(excolIdx);

            QString s = QLatin1String("\nORDER BY ");

            s.append( exColData.renamedField_As);

            s += d->sortOrder == Qt::AscendingOrder ? QLatin1String(" ASC") : QLatin1String(" DESC");

            return s;
        }
        return QString();
    }
    else
        return QSqlTableModel::orderByClause();
}


bool PblSqlRelationalTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    Q_D(PblSqlRelationalTableModel);

    if (parent.isValid()
            || column < 0
            || column + count > d->rec.count())
        return false;

    for (int i = 0; i < count; ++i)
    {
        d->baseRec.remove(column);

        if (d->relations.count() > column)
            d->relations.remove(column);
    }

    return QSqlTableModel::removeColumns(column, count, parent);
}



QString PblSqlRelationalTableModel::selectStatement() const
{
    Q_D(const PblSqlRelationalTableModel);
    QString query;

    if (tableName().isEmpty())
        return query;

    /*if (d->relations.isEmpty())
                                  return QSqlTableModel::selectStatement();*/

    QString sTablesList;
    QString sFieldsList;
    QString where;

    // This is impotant d->baseRec ! because of d->rec maybe contains modified field names already after first select
    QSqlRecord origRec = d->baseRec; // this is after setTable created

    QStringList lstTables;

    // Count how many times each field name occurs in the record
    //QHash<QString, int> fieldNames;
    //QStringList fieldList;

    bool bFieldsFullName = false;

    if( d->ex_columns.count()>0)
        bFieldsFullName = true;

    //-------------------------------------------------------
    //                STANDART FIELDS
    //-------------------------------------------------------

    for (int col = 0; col < origRec.count(); ++col)
    {
        QString name;

        if (d->relations.contains(col))
        {
            int exNumCol =  d->relations.value(col);

            if(exNumCol < d->ex_columns.count())
            {

                PblColumn exCol = d->ex_columns.value(exNumCol);

                if (exCol.type == PblColumn::COLUMN_TYPE_RELATION_ID)
                {
                    //name = exCol.exTextFieldName;

                    /*if (d->db.driver()->isIdentifierEscaped(name, QSqlDriver::FieldName))
                                    {
                                        name = d->db.driver()->stripDelimiters(name, QSqlDriver::FieldName);
                                    }*/
                    PblColumn exCol = d->ex_columns.value(exNumCol);

                    QString relTableAlias = QString::fromLatin1("relTblAl_%1").arg(col);

                    name = QString(d->relationField(relTableAlias , exCol.exTextFieldName))
                            .append(QString::fromLatin1(" AS %1_%2_%3").
                                    arg(origRec.fieldName(col)).
                                    arg(col).
                                    arg(exCol.exTextFieldName));

                }
            }
        }
        else
        {
            name = origRec.fieldName(col);

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

    for(int col=0; col < d->ex_columns.count(); col++)
    {
        PblColumn exCol = d->ex_columns.at(col);

        if(exCol.type == PblColumn::COLUMN_TYPE_RELATION_ID)
        {
            QString relTableAlias = QString::fromLatin1("relTblAl_%1").arg(exCol.origCol);

            sAddFields.append(QString::fromLatin1(",\n %1.%2 AS %3_%4_%5").
                              arg(relTableAlias).
                              arg(exCol.exIndexFieldName).
                              arg(exCol.exTableName).
                              arg( exCol.origCol ).
                              arg(exCol.exIndexFieldName));


        }
        else if(exCol.type == PblColumn::COLUMN_TYPE_CALCULATION)
        {
            QStringList lst = exCol.exTextFieldName.split(QLatin1String(","));

            QString fields;

            sExtFieldNameAdds.
                    append(QLatin1String(", \n")).
                    append(exCol.exFuncName).
                    append(QLatin1String("("));

            for(int ii=0; ii < lst.count(); ii++) // this is a sum by some fields
            {

                sExtFieldNameAdds.
                        append(exCol.exTableName).
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
                sExtFieldNameAdds.append(exCol.exTableName).append(QLatin1String("_")).append(fields);
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

    for(int ii=0; ii < d->ex_columns.count(); ii++)
    {
        PblColumn addCol = d->ex_columns.at(ii);

        if( addCol.type == PblColumn::COLUMN_TYPE_RELATION_ID)
        {

            if( ! joinedTables.contains(addCol.exTableName))
            {
                int fggf= addCol.origCol;

                QString relTableAlias = QString::fromLatin1("relTblAl_%1").arg(addCol.origCol);

                sExtLeftJoins.append(QLatin1String(" \nLEFT JOIN ")).
                        append(addCol.exTableName).
                        append(QLatin1String(" ")).
                        append(relTableAlias).

                        append(QLatin1String(" ON ")).

                        append(tableName()).
                        append(QLatin1String(".")).
                        append(origRec.fieldName(addCol.origCol)).

                        append(QLatin1String("=")).

                        append(relTableAlias).
                        append(QLatin1String(".id"));

                joinedTables.append(addCol.exTableName);
            }
        }
        else  if( addCol.type == PblColumn::COLUMN_TYPE_CALCULATION)
        {
            if( ! joinedTables.contains(addCol.exTableName))
            {
                sExtLeftJoins.append(QLatin1String(" \nLEFT JOIN ")).
                        append(addCol.exTableName).
                        append(QLatin1String(" ")).

                        append(QLatin1String(" ON ")).

                        append(tableName()).
                        append(QLatin1String(".")).
                        append(addCol.exIndexFieldName).

                        append(QLatin1String("=")).

                        append(addCol.exTableName).
                        append(QLatin1String(".")).
                        append(addCol.exTextFieldName);

                joinedTables.append(addCol.exTableName);
            }
        }
    }

    //------------------------------------------------------------

    sTablesList.append(lstTables.join(QLatin1String(" ")));

    if (sFieldsList.isEmpty())
        return query;

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
        query.append(QLatin1Char(' ')).append(orderBy);

#ifdef  PBL_SQL_DEBUG
    //qDebug() << "\nselectStatement : \n" << query;
#endif

    return query;
}

void PblSqlRelationalTableModel::setAlignment(int exCol , Qt::Alignment align)
{
    Q_D(PblSqlRelationalTableModel);

    if(exCol < d->ex_columns.count() )
        d->ex_columns[exCol].setAlignment(align);
}

PblColumn::COLUMN_TYPE PblSqlRelationalTableModel::exColType(int exCol)
{
    Q_D(PblSqlRelationalTableModel);

    //qDebug() << "PblSqlRelationalTableModel::exColType " << exCol;

    if(exCol < d->ex_columns.count())
    {
        PblColumn::COLUMN_TYPE tt = d->ex_columns[exCol].type;
        return tt;
    }
    return PblColumn::COLUMN_TYPE_UNKNOUWN;
}


QSqlRecord  PblSqlRelationalTableModel::getEditBuffer()
{
    Q_D(PblSqlRelationalTableModel);

    return d->editBuffer;
}

PblColumn PblSqlRelationalTableModel::getRelationInfoForColumn(int col)
{
    Q_D(PblSqlRelationalTableModel);

    if( ! d->relations.contains(col))
        return PblColumn();

    int exCol = d->relations.value(col);

    if(exCol < d->ex_columns.count())
    {
        return d->ex_columns.value(exCol);
    }
    return PblColumn();
}

QString  PblSqlRelationalTableModel::exColName(int exCol)
{
    Q_D(PblSqlRelationalTableModel);

    if(exCol < d->ex_columns.count())
    {
        QString str = d->ex_columns[exCol].renamedField_As;
        return str;
    }
    return QString();
}

QString  PblSqlRelationalTableModel::exStr(int exCol)
{
    Q_D(PblSqlRelationalTableModel);

    if(exCol < d->ex_columns.count())
    {
        QString str;

        str.append(d->ex_columns[exCol].exTableName).
                append(QLatin1Char(' ')).
                append(d->ex_columns[exCol].exTextFieldName).
                append(QLatin1Char(' ')).append(d->ex_columns[exCol].exFuncName);

        return str;
    }
}

int PblSqlRelationalTableModel::exColCount()
{
    Q_D(PblSqlRelationalTableModel);

    return d->ex_columns.count();
}


int PblSqlRelationalTableModel::getRelIdColumn(int relCol)
{
    Q_D(PblSqlRelationalTableModel);

    if(d->relations.contains(relCol))
        return d->relations.value(relCol) + d->baseRec.count();
    else
        return -1;
}

PblColumn::COLUMN_TYPE PblSqlRelationalTableModel::columnType(int col)
{
    Q_D(PblSqlRelationalTableModel);

    if(d->relations.contains(col))
        return PblColumn::COLUMN_TYPE_RELATION_TEXT;
    else
    {
        if(col > d->baseRec.count()) // calculate column
        {
            int exCol = col - d->baseRec.count();

            if ( exCol < d->ex_columns.count() )
                return d->ex_columns.value(exCol).type;
        }

    }

    return PblColumn::COLUMN_TYPE_UNKNOUWN;
}


bool PblSqlRelationalTableModel::is_insertIndex()
{
    Q_D(const PblSqlRelationalTableModel);

    if(d->insertIndex != -1)
        return true;
    else
        return false;
}

bool PblSqlRelationalTableModel::setDataOnlyIntoEditBuffer(const QModelIndex &idx, const QVariant &value, int role)
{
    Q_D(PblSqlRelationalTableModel);

    switch (d->strategy)
    {
    case OnFieldChange:
    {
        /*if( ! QSqlTableModel::setData( idx ,value, role))
                            // call updateRowInTable & select
                            return false;*/

        qDebug() << "setDataOnlyIntoEditBuffer d->editBuffer " << d->editBuffer;

        if(d->editBuffer.isEmpty()) // редактирование первое ячейки после открытия таблицы
            d->clearEditBuffer();

        d->editBuffer.setValue( idx.column() , value);
        d->editBuffer.setGenerated(idx.column() , false);

        qDebug() << "setDataOnlyIntoEditBuffer d->editBuffer " << d->editBuffer;

        emit dataChanged(idx, idx);

        return true;
    }
    case OnRowChange:
    {
        d->editBuffer.setValue( idx.column() , value);
        d->editBuffer.setGenerated(idx.column(), false);

        emit dataChanged(idx, idx);
        return true;
    }
    case OnManualSubmit:
    {
        if ( ! d->cache.contains(idx.row() ) )
        {
            return true;
        }

        // устанавливаем знение поля в row.rec (строка кеша)
        d->editBuffer.setValue( idx.column() , value);
        d->editBuffer.setGenerated(idx.column() , false);

        emit dataChanged(idx, idx);

        return true;
    }
    }
    return false;
}

QT_END_NAMESPACE


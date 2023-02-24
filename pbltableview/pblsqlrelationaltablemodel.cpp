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
#include <QSqlTableModel>
#include "some_tests.h"
#include "qdebug.h"
#include <QApplication>
#include <QSqlQuery>
#include "config.h"
#include <QMessageBox>
#include "pbltableview/my_sql.h"

QT_BEGIN_NAMESPACE


PblSqlRelationalTableModel::PblSqlRelationalTableModel()
{

}

PblSqlRelationalTableModel::PblSqlRelationalTableModel(
        QSqlDatabase &db_,
        QObject *parent
        )
    :
      QSqlTableModel( parent, db_),
      sortColumn(-1),
      sortOrder(Qt::AscendingOrder),
      isDirtyRow(-1),
      isInsertRow(-1),
      lastDirtyCol(-1),
      lastDirtyRowId(-1),
      isSelectedLine(-1),
      db(db_),
      priCol(-1)
{

    qDebug() << "ctor PblSqlRelationalTableModel editStrategy " << editStrategy();

    _CONNECT_(this, SIGNAL(primeInsert(int,QSqlRecord&)),
              this, SLOT(slot_primeInsert(int,QSqlRecord&)));


}


int PblSqlRelationalTableModel::findRowById(int id)
{
    if(rowCount()==0)
        return -1;

    for(int row = 0 ; row < rowCount(); row++)
    {
        QModelIndex idx = index( row , getPriColumn() );

        if( ! idx.isValid())
            return -1;

        bool ok =false;

        int currId = data( idx ).toInt(&ok);

        if(! ok )
            return -1;

        if(currId == id)
            return row;
    }

    return -1;
}

void PblSqlRelationalTableModel::slot_primeInsert(int row, QSqlRecord &rec)
{
    qDebug() << "PblSqlRelationalTableModel::slot_primeInsert ";// <<    rec;

    // this writes into private d->editBuffer (= rec)
    // and don't calls setData


    if ( ! config::set_newInsertedRowParameters(this , rec))
    {
        QMessageBox::warning(0,
                             mySql::error_,
                             tr("874584584 inserting row:\n set_newInsertedRowParameters returns false, table name '%1'").
                             arg(tableName()));
    }


    /*if ( ! config::set_newInsertedRowParameters_withSetData(this , row) )
    {
        QMessageBox::warning(0,
                             mySql::error_,
                             tr("inserting row: set_newInsertedRowParameters returns false, table name '%1'").
                             arg(tableName()));
    }*/




    setDirtyRow( row , 0);

}

PblSqlRelationalTableModel::~PblSqlRelationalTableModel()
{
    //qDebug() << "dtor PblSqlRelationalTableModel " << tableName()<< "  isDirtyRow " <<isDirtyRow;

    if(isDirtyRow != -1)
    {
        bool bbb = submit();

        if( ! bbb && isDirtyRow < rowCount())
        {
            QMessageBox::warning(0,
                                 mySql::error_,
                                 tr("The data of row %1 are not saved fully").arg(isDirtyRow));
        }
    }

}

QVariant PblSqlRelationalTableModel::data(const QModelIndex &idx, int role) const
{

    int row = idx.row();

    int col = idx.column();
    int baseCount = baseRec.count();

    if( role == Qt::TextAlignmentRole)
        if( colInfo.contains(col))
            return colInfo.value(col).alignment;

    if(row == isSelectedLine && role == Qt::BackgroundColorRole) // repaint
    {
        // here returns color

        // int r,g,b,a=0;
        // qDebug() << " brush.color() " << r<< g << b <<a;

        return  QColor(QApplication::palette().color(QPalette::AlternateBase));
    }


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

    qDebug() << "PblSqlRelationalTableModel::setEditStrategy editStrategy " << this << "  strategy "<< strategy << tableName();

    QSqlTableModel::setEditStrategy(strategy);

    emit sig_editStrategyChanged(QSqlTableModel::editStrategy()); // needs for QTableView

}

Qt::ItemFlags PblSqlRelationalTableModel::flags(const QModelIndex &index) const
{

    int col = index.column();
    int row = index.row();

    int baseCount = baseRec.count();

    Qt::ItemFlags flgs=0;

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
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
    }
    else
    {
        Qt::ItemFlags flgs = QSqlTableModel::flags(index);

        if ( colInfo.contains(col) && ! colInfo.value(col).editable)
            flgs &= ~(Qt::ItemIsEditable);

        return flgs;

    }
    return flgs;
}

const QSqlRecord & PblSqlRelationalTableModel::baseRecord()
{

    return baseRec;
}

bool PblSqlRelationalTableModel::submit()
{
    // here we are following for dirty row

    bool bbb = QSqlTableModel::submit();

    return bbb;
}

int PblSqlRelationalTableModel::getPriColumn( ) const
{
    return priCol;
}

int PblSqlRelationalTableModel::getRowPriValue(int row) const
{
    if(priCol == -1)
    {
        QMessageBox::warning(0 ,
                             mySql::error_,
                             tr("pri column have to exist in table!"));
        return -1;
    }

    QVariant pri = data(index(row , priCol ));

    if( pri == QVariant()) // empty or undefined value, insertRow for exapmle
    {
        return -1;
    }

    bool ok = false;

    int iPri = pri.toInt(&ok);

    if( ! ok )
    {
        QMessageBox::warning(0 ,
                             mySql::error_,
                             tr("pri column value dont convert to int !"));
        return -1;
    }


    return iPri;
}

QVariant PblSqlRelationalTableModel::getRecordPriValue(const QSqlRecord &rec) const
{
    if(priCol == -1 )
    {
        QMessageBox::warning(0 ,
                             mySql::error_,
                             tr("pri column have to exist in table!"));
        return -1;
    }

    //qDebug() << " rec.field(priCol) " << rec.field(priCol) << rec.fieldName(priCol);
    //qDebug() << " rec.field(priCol) " << rec.field(99) << rec.fieldName(99);

    if( rec.fieldName(priCol).isEmpty()
            ||  ! rec.field(priCol).isValid() )
    {
        QMessageBox::warning(0 ,
                             mySql::error_,
                             tr("pri column have to exist in record!"));
        return -1;
    }

    QVariant val = rec.value( priCol );


    return val;
}

PblSqlRelationalTableModel::MODE PblSqlRelationalTableModel::isRowMode(int row) const
{
    int pri = getRowPriValue( row );

    if( pri == -1 ) // this is insert mode

        return PblSqlRelationalTableModel::INSERT;

    else

        return PblSqlRelationalTableModel::UPDATE;

}

bool PblSqlRelationalTableModel::isCopyRowMode(int extCol , const QSqlRecord &rec) const
{
    return rec.isGenerated(extCol);

}

PblSqlRelationalTableModel::MODE PblSqlRelationalTableModel::isRecordMode(const QSqlRecord &rec) const
{
    QVariant pri = getRecordPriValue( rec );

    if( pri == QVariant() ) // this is insert mode

        return PblSqlRelationalTableModel::INSERT;

    else

        return PblSqlRelationalTableModel::UPDATE;

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

    QModelIndex idx2 = idx; // after submit idx will be unvalid

    if(editStrategy() <= QSqlTableModel::OnRowChange)
    {
        if(isDirtyRow != -1 && isDirtyRow != row ) // needs to submit previouse changed row
        {
            int pri = getRowPriValue( row );

            if( pri == -1 ) // insertRow
            {
                if ( ! submit() )
                {
                    QMessageBox::warning(0 ,
                                         mySql::error_ ,
                                         tr("OnRowChange: needs to submit dirty row %1 (id : %2)").
                                         arg(row).
                                         arg(pri));
                    return false;

                }
                //qDebug() << "PblSqlRelationalTableModel::setData() , submit dirty row is OK";
            }


            row = findRowById( pri);

            if ( row == -1 )
            {
                QMessageBox::warning(0 ,
                                     mySql::error_ ,
                                     tr("OnRowChange: lost focus on row %1 (id : %2)").
                                     arg(row).
                                     arg(pri));
                return false;

            }

            qDebug() << "PblSqlRelationalTableModel::setData() , restore current row after submit/select is OK";

            idx2 = createIndex( row , col);

            if( ! idx2.isValid() )
                return false;

            emit sig_rowIsDirty(isDirtyRow);

        }
    }

    bool bSetData = false;

    bSetData = QSqlTableModel::setData(idx2, value, role);

    // with QSqlTableModel::OnFieldChange tab pressed (without Enter)
    // isDirtyRow must to set to row value

    if( bSetData )
    {
        // following unsaved fields

        setDirtyRow(row , col);

        emit sig_rowIsDirty(row);
    }

    return bSetData;
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

    if(calc.idField1 == -1 )
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


void PblSqlRelationalTableModel::setDirtyRow(int dirtyRow , int dirtyCol)
{

    //qDebug() << "setDirtyRow() " << dirtyRow;

    // 0 - undefined because of insertRow

    lastDirtyRowId  = getRowPriValue( dirtyRow );

    isDirtyRow      = dirtyRow;

    lastDirtyCol    = dirtyCol;

    isSelectedLine  = dirtyRow;

    //qDebug() << "        lastDirtyRowId " <<lastDirtyRowId ;
    //qDebug() << "        lastDirtyCol   " <<lastDirtyCol ;
    //qDebug() << "        isDirtyRow     " <<isDirtyRow ;
    //qDebug() << "        isSelectedLine " <<isSelectedLine ;

}



void PblSqlRelationalTableModel::clearDirtyRow()
{
    isDirtyRow      = -1;
    isSelectedLine  = -1;

}

void PblSqlRelationalTableModel::clear()
{
    //qDebug() << "PblSqlRelationalTableModel::clear() " <<tableName();

    QSqlTableModel::clear();

}

/*void PblSqlRelationalTableModel::fetchMore(const QModelIndex &parent)
                  {
                      qDebug() << "PblSqlRelationalTableModel::fetchMore( " << tableName();
                      QSqlQueryModel::fetchMore(parent);

                  }*/

bool PblSqlRelationalTableModel::canFetchMore(const QModelIndex &parent) const
{
    bool bbb = QSqlQueryModel::canFetchMore(parent);

    //qDebug() << "PblSqlRelationalTableModel::canFetchMore  " << bbb <<  tableName();

    return bbb;

}


bool PblSqlRelationalTableModel::select()
{
    /*qDebug() << "PblSqlRelationalTableModel::select() " << tableName() << " lastDirtyRowId"
             << lastDirtyRowId << " isDirtyRow" << isDirtyRow << " lastDirtyCol " << lastDirtyCol
             << " isSelectedLine" << isSelectedLine;*/

    if(editStrategy() <= QSqlTableModel::OnRowChange)
    {
        clearDirtyRow();
    }

    bool bbb = QSqlTableModel::select();

    emit sig_afterSelect(bbb);

    if ( ! bbb) // here occures PblTableView::reset()
        return false;

    lastDirtyRowId = -1;
    lastDirtyCol = -1;
    isDirtyRow = -1;
    isInsertRow = -1;


    /*qDebug() << " after PblSqlRelationalTableModel::select() : " << tableName()
             << " lastDirtyRowId " << lastDirtyRowId
             << " isDirtyRow"  << isDirtyRow
             << " lastDirtyCol " << lastDirtyCol
             << " isSelectedLine" << isSelectedLine;*/



    // ------------------------------------------------------------
    //  rename extended fields headers if you want
    // ------------------------------------------------------------

    int origColumnCount = record().count();

    for(uint exCol=0; exCol < ex_columns.count(); exCol++)
    {
        QString header = ex_columns.value(exCol).renamedField_As;

        if( header != QString())
        {
            bool b = setHeaderData( origColumnCount + exCol, Qt::Horizontal, header);
        }
    }

    return true;
}

bool PblSqlRelationalTableModel::prepare(const QString &tableName)
{

    if(! db.isValid() )
    {
        QMessageBox::critical(0 ,
                              mySql::error_ ,
                              tr("database is not valid!"));
        return false;
    }

    if( ! db.isOpen())
    {
        QMessageBox::critical(0 ,
                              mySql::error_ ,
                              tr("database is not opened!"));
        return false;
    }

    if(  db.isOpenError())
    {
        QMessageBox::critical(0 , mySql::error_ , tr("database is not opened! %1").arg(db.lastError().text()));
        return false;
    }

    if ( db.tables().isEmpty())
    {
        QMessageBox::critical( 0 ,
                               mySql::error_,
                               QObject::tr("database is empty?\n %1:\n error: %2").
                               arg(db.databaseName()).
                               arg(db.lastError().text()));

        return false;
    }

    if (tableName.isEmpty())
    {
        QMessageBox::critical( 0 ,
                               mySql::error_,
                               QObject::tr("empty table name '%1'").
                               arg(tableName));

        return false;
    }

    if (! db.tables().contains(tableName))
    {
        QMessageBox::critical( 0 ,
                               mySql::error_,
                               QObject::tr("database is not contains table '%1' ?\n\n error: %2").
                               arg(tableName).
                               arg(db.lastError().text()));

        return false;
    }

    baseRec = QSqlDatabase::database().record(tableName);

    //qDebug() << " tables " << QSqlDatabase::database().tables();

    if(baseRec.isEmpty())
    {
        QMessageBox::critical(0 ,
                              mySql::error_ ,
                              tr("table '%1' is not valid").
                              arg(tableName));
        return false;
    }

    QSqlTableModel::setTable(tableName);

    relations.clear();

    ex_columns.clear();

    colInfo.clear();

    primaryIndex = db.primaryIndex(tableName);

    if( ! primaryIndex.isEmpty() && primaryIndex.count() == 1)
    {
        QString field = primaryIndex.fieldName(0);

        priCol = fieldIndex(field);
    }

    if ( ! config::setting_mdl( this ) )
    {
        QMessageBox::warning(0,
                             mySql::error_,
                             tr("error in setting_mdl"),
                             "");
        return false;
    }


    return true;

}

bool PblSqlRelationalTableModel::prepareRecord(QSqlRecord &rec, MODE mode)
{
    // far setRecord will calls setData
    // that is required relation replace with QList value

    if( priCol >=0 && priCol < rec.count() )
        rec.setGenerated( priCol , false);
    //rec.remove(priCol); dont remove any field

    if(mode == PblSqlRelationalTableModel::INSERT) // it is important
        rec.setValue(priCol , QVariant() ); // this is flag (-1) for translateFieldNames()

    qDebug() << "prepareRecord " << rec;

    return true;

}

bool PblSqlRelationalTableModel::setRecord_withoutPriCol(int row,
                                                         QSqlRecord &rec,
                                                         MODE mode)
{


    QSqlRecord rec2 =rec;

    prepareRecord( rec2, mode);

    //qDebug() << "set_Record rec2 " << rec2;
    qDebug() << "QSqlTableModel::setRecord editStrategy() " << editStrategy();

    // -----------------------------------------------------
    //                  Attention !
    // setRecord is temporary chenge editStrategy to OnRowChange

    // -----------------------------------------------------
    bool bbb = QSqlTableModel::setRecord( row , rec2);

    qDebug() << "QSqlTableModel::setRecord editStrategy() " << editStrategy();

    return bbb;
}


bool PblSqlRelationalTableModel::translateFieldNames(
        int row,
        QSqlRecord &rec,
        PblSqlRelationalTableModel::MODE mode
        ) const
{
    // 1. Эта функция возвращает наименования полей к оригинальным
    // в SELECT наименование полей через as могут быть изменены
    // например для INSERT ROW нужны оригинальные поля

    int count = baseRec.count();

    int isGeneratedCount = 0;


    for( int col=0; col < rec.count(); col++)
    {
        // pri col presents forever , dont remove pri column

        if( ! rec.isGenerated(col))
            continue;

        isGeneratedCount++;

        if ( isRelationColumn(col))
        {

            int extCol = getRelIdColumn( col);


            // mode == UPDATE  translateFieldNames called from updateRowInTable
            // mode == INSERT  translateFieldNames called from insertRowIntoTable

            // actually UPDATE | INSERT are no matter in current program version

            QVariant txt = rec.value(col);

            //------------------------------------------------------------------------
            //                          Attention!
            //
            //  if edit strategy is OnFieldChane
            //  setRecord temporary change editStrategy to OnRowChange and afterward restore
            //------------------------------------------------------------------------

            if ( editStrategy() == QSqlTableModel::OnFieldChange) // will be submit /select
            {
                if ( isRecordMode(rec) == INSERT)
                {
                    // it occures when click insertRow and click to update relational field
                    // or if copyRow run

                    if( rec.isGenerated(extCol)) // is copyRow
                        qDebug() << "is copyRow"; // nothing to do
                    else
                        txt = rec.value(extCol).toInt(); // replace text from id

                }
                else if ( isRecordMode(rec) == UPDATE)
                {
                    txt = rec.value(extCol).toInt(); // replace text from id

                }

            }

            else if ( editStrategy() == QSqlTableModel::OnRowChange) // will be submit /select

            {
                //------------------------------------------------------------------------
                //                          Attention!
                //
                //  if edit strategy is OnFieldChange
                //  setRecord temporary change editStrategy to OnRowChange
                //------------------------------------------------------------------------

                if ( isRecordMode(rec) == INSERT)
                {
                    // it occures when click insertRow and click to update relational field
                    // or if copyRow run

                    if( isCopyRowMode( extCol , rec) ) // is copyRow
                        txt = rec.value(extCol).toInt(); // replace text from id
                    else
                        txt = rec.value(extCol).toInt(); // replace text from id

                }
                else if ( isRecordMode(rec) == UPDATE)
                {
                    txt = rec.value(extCol).toInt(); // replace text from id
                    // will be submit
                }


            }
            else if ( editStrategy() == QSqlTableModel::OnManualSubmit)
            {
                // it occures only if submitAll was called

                txt = rec.value(extCol).toInt(); // replace text from id
            }

            QSqlField ff = rec.field( col );
            QString name = baseRec.field( col ).name();  // replace record field name to original as in db exist, because of select query was changed it by AS operator
            ff.setName(name);
            ff.setValue(txt);
            ff.setGenerated(true);

            rec.replace( col , ff );

            if(rec.field( extCol ).isGenerated())
                // extCol is never writes to db, extCol is a virtual column
            {
                rec.setGenerated(extCol , false );
            }

        }


        else if( isExtRelationColumn( col ))


        {
            if(editStrategy() ==QSqlTableModel::OnFieldChange
                    && isRecordMode(rec) == UPDATE)
            {
                // -----------------------------------------------------
                //  only one case
                // -----------------------------------------------------

                rec.setGenerated( col , false); // has to be forever false

                int origCol = getOrigRelationColumn( col );

                if( origCol == -1)
                {
                    QMessageBox::warning(0,
                                         mySql::error_,
                                         tr("OnFieldChange: unknown relatinal column :\n"\
                                            "table name '%1'").
                                         arg(tableName()));
                }

                QSqlField ff = rec.field( origCol );
                QString name = baseRec.field( origCol ).name();  // replace record field name to original as in db exist, because of select query changes it by AS operator
                ff.setName(name);
                ff.setValue( rec.value(col));
                ff.setGenerated(true);

                rec.replace( origCol , ff );

            }
        }

    }

    qDebug() << "rec "<< rec;

    if(mode == INSERT)
        rec.remove(priCol);

    if( isGeneratedCount > 0 )
        return true;
    else
        return false;

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
    if( translateFieldNames(row, rec, UPDATE) )
    {

        qDebug() << "PblSqlRelationalTableModel::updateRowInTable " << rec;

        return QSqlTableModel::updateRowInTable(row, rec);
    }

    return true;

}

bool PblSqlRelationalTableModel::insertRowIntoTable(const QSqlRecord &values)
{
    QSqlRecord rec = values;

    // it occures when insetRow: insertRow and copyRow too!

    translateFieldNames(0, rec, INSERT);

    //qDebug() << "PblSqlRelationalTableModel::insertRowIntoTable rec " << rec;

    bool res = QSqlTableModel::insertRowIntoTable(rec); // insert all fields (with generated=no too)

    if( res )
    {
        lastDirtyRowId = getLastInsertId();
    }

    return res;
}

int PblSqlRelationalTableModel::getLastInsertId()
{
    QSqlQuery qq;

    if( qq.exec("SELECT last_insert_rowid()") )
    {

        if(qq.next())
        {
            bool ok = false;

            int lastIsertId = qq.value(0).toInt(&ok);

            if(ok)
            {
                return lastIsertId;
            }
            else
            {
                return -1;

            }

            qDebug() << "lastInsertId " <<  lastIsertId;
        }
    }
    return -1;
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

                s.append( baseRec.fieldName(exColData.idField1));

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
                                   arg(baseRec.fieldName(exCol.idField1)).
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
                              arg(exCol.idField2).
                              arg(exCol.ext_table).
                              arg(exCol.idField2).
                              arg(exCol.origCol)
                              );


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
                        append(exCol.ext_table).
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
                sExtFieldNameAdds.append(exCol.ext_table).append(QLatin1String("_")).append(fields);
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

            if( ! joinedTables.contains(addCol.ext_table))
            {

                QString relTableAlias = QString::fromLatin1("relTblAl_%1").arg(addCol.origCol);

                sExtLeftJoins.append(QLatin1String(" \nLEFT JOIN ")).
                        append(addCol.ext_table).
                        append(QLatin1String(" ")).
                        append(relTableAlias).

                        append(QLatin1String(" ON ")).

                        append(tableName()).append(QLatin1String(".")).
                        append(baseRec.fieldName( addCol.idField1 )).

                        append(QLatin1String("=")).

                        append(relTableAlias).append(QLatin1String(".")).
                        append(addCol.idField2);

                joinedTables.append(addCol.ext_table);
            }
        }
        else  if( addCol.type == PblColumn::COLUMN_TYPE_CALCULATION)
        {
            if( ! joinedTables.contains(addCol.ext_table))
            {
                sExtLeftJoins.append(QLatin1String(" \nLEFT JOIN ")).
                        append(addCol.ext_table).
                        append(QLatin1String(" ")).

                        append(QLatin1String(" ON ")).

                        append(tableName()).append(QLatin1String(".")).
                        append(baseRec.fieldName(addCol.idField1)).

                        append(QLatin1String("=")).

                        append(addCol.ext_table).append(QLatin1String(".")).
                        append(addCol.idField2);

                joinedTables.append(addCol.ext_table);
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

void PblSqlRelationalTableModel::setEditable(int col , bool on)
{
    colInfo[col].editable = on;

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

bool PblSqlRelationalTableModel::isRelationColumn(int col) const
{
    if( ! relations.contains(col))
        return false;

    return true;
}

bool PblSqlRelationalTableModel::isCalcColumn(int col) const
{

    if(col < baseRec.count())
        return false;

    int exCol = col - baseRec.count();

    if( exCol >= ex_columns.count() )
        return false;

    if(ex_columns.value(exCol).type == PblColumn::COLUMN_TYPE_CALCULATION)
        return true;

    return false;
}

bool PblSqlRelationalTableModel::isRelationalColumn(int col)
{
    if(relations.contains(col))
        return true;

    return false;
}

int PblSqlRelationalTableModel::getRelIdColumn(int relCol) const
{
    if(relations.contains(relCol))
        return relations.value(relCol);
    else
        return -1;
}

bool PblSqlRelationalTableModel::isExtRelationColumn(int col) const
{
    if(col < baseRec.count())
        return false;

    int extCol = col - baseRec.count();

    if(ex_columns.value( extCol).type == PblColumn::COLUMN_TYPE_RELATION_ID)
        return true;

    return false;
}

int PblSqlRelationalTableModel::getOrigRelationColumn(int col) const
{
    if(isExtRelationColumn( col))
    {
        return ex_columns.value( col - baseRec.count() ).origCol;

    }

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

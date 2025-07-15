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

#include "qp_sqltablemodel.h"

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
#include "qp/sql/model/my_sql.h"
#include <QSqlTableModel>
//#include "qp/sql/view/some_tests.h"
#include "qdebug.h"
#include <QApplication>
#include <QSqlQuery>
#include "qp/sql/model/my_sql.h"
#include <QMessageBox>
#include <QString>
#include <QSqlRecord>
#include <QSqlField>

#include "qp/sql/model/qp_sqlrelation.h"
#include "qp/sql/model/qp_calc_column.h"
#include "qp/sql/model/qp_sql_orderstring.h"

#include "qp/sql/model/qp_sqlrecord.h"
#include "qp/gui/qp_gui.h"
#include "qp/core/qp_core.h"
#include "qp/sql/qp_sql.h"
#include "qp/qp.h"

QT_BEGIN_NAMESPACE



//-------------------------------------------------------------------------------------

QpSqlTableModel::QpSqlTableModel(
        QSqlDatabase &Db,
        cb_setting_mdl pToSettingFunc,
        QObject *parent,
        const QList<QString> &FieldsSet
        )
    :
      QpCmnSqlTableModel( Db ,
                          pToSettingFunc,
                          parent)


{

    Q_ASSERT (Db.isValid() == true);

    Q_ASSERT (Db.isOpenError() == false);

    //qDebug() << "ctor QpSqlTableModel editStrategy " << editStrategy();

    qp::meta::cnct (this, SIGNAL(primeInsert(int,QSqlRecord&)),
                    this, SLOT(slot_primeInsert(int,QSqlRecord&)));

}



bool QpSqlTableModel::set_newInsertedRowParameters( QpSqlTableModel * mdl, QSqlRecord & rec)
{
    if( mdl->tableName().isNull() )
        return false;

    // -----------------------------------------------------------
    //              This is important!
    // new inserted row has not generated (yes) flag in editBuffer for any fileds
    // we have to repare this

    for(int col=0; col < mdl->columnCount(); col++)
    {
        if(col == mdl->getPriColumn())
            continue;

        rec.setGenerated( col , true ); // any col is not priCol will be generateg yes
        // with insertRow this is forbidden created fully empty row

    }
    // ------------------------------------------------------------

    return true;
}

void QpSqlTableModel::slot_primeInsert(int row, QSqlRecord &rec)
{
    //qDebug() << "QpSqlTableModel::slot_primeInsert ";// <<    rec;

    // this writes into private d->editBuffer (= rec)
    // and don't calls setData


    if ( ! set_newInsertedRowParameters(this , rec))
    {
        QMessageBox::warning(0,
                             qp::dbg ::error_,
                             tr("874584584 inserting row:\n set_newInsertedRowParameters returns false, table name '%1'").
                             arg(tableName()));
    }



    setDirtyRow( row , 0);

}

QpSqlTableModel::~QpSqlTableModel()
{
    //qDebug() << "dtor QpSqlTableModel " << tableName()<< "  isDirtyRow " <<isDirtyRow;

    clear();


}

QVariant QpSqlTableModel::get_displayData( const QModelIndex &idx ) const
{
    return QSqlTableModel::data(idx, Qt::DisplayRole );
}

//QVariant QpSqlTableModel::data(const QModelIndex &idx, int role) const
//{

//    if( role == Qt::TextAlignmentRole || role == Qt::BackgroundColorRole )
//        return QpCmnSqlTableModel::data( idx , role );

////    int row = idx.row();

////    int col = idx.column();

//    //qDebug() << "::data "<< idx.column() << idx.row() << " role : " << role;

////    const QString &fldName = baseRec.fieldName(col);


////    if(fldName == "date_")
////    {
////        if(role == Qt::DisplayRole)
////        {
////            QVariant vv = QSqlTableModel::data(idx, role);
////            //qDebug()<<"adssas" << vv.toString();
////        }
////    }


////    if( ! colInfo.contains( fldName ) )
////        return QSqlTableModel::data(idx, role);

////    if( calc_columns.contains( fldName ) && role == Qt::DisplayRole)
////    {
////        QVariant vv = QSqlTableModel::data(idx, role);

////        if( vv.type() >= QVariant::Int && vv.type() <= QVariant::Double &&  vv.toDouble() == 0)

////            return ""; // вместо 0 пусто возвращаем
////    }



//    return QpCmnSqlTableModel::data(idx, role);
//}

void QpSqlTableModel::setEditStrategy( QSqlTableModel::EditStrategy strategy)
{

    //qDebug() << "QpSqlTableModel::setEditStrategy editStrategy " << this << "  strategy "<< strategy << tableName();

    QSqlTableModel::setEditStrategy(strategy);

    emit sig_editStrategyChanged(QSqlTableModel::editStrategy()); // needs for QTableView

}




bool QpSqlTableModel::submit()
{
    // here we are following for dirty row
    qDebug() << "QpSqlTableModel::submit()";
    bool bbb = QSqlTableModel::submit();

    return bbb;
}


QVariant QpSqlTableModel::getRecordPriValue(const QSqlRecord &rec) const
{
    if( baseRec.indexOf( priColName ) == qp::db::COL_UNDEFINED )
    {
        QMessageBox::warning(0 ,
                             qp::dbg::error_,
                             tr("pri column have to exist in table!"));
        return qp::db::INT_UNDEFINED;
    }


    if( rec.indexOf( priColName ) == qp::db::COL_UNDEFINED )
    {
        QMessageBox::warning(0 ,
                             qp::dbg::error_,
                             tr("pri column have to exist in this record!"));
        return qp::db::INT_UNDEFINED;
    }

    QVariant val = rec.value( priColName );


    return val;
}


bool QpSqlTableModel::isCopyRowMode(int extCol , const QSqlRecord &rec) const
{
    return rec.isGenerated(extCol);

}




bool QpSqlTableModel::setData(const QModelIndex &idx,
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
        if(isDirtyRow != qp::db::ROW_UNDEFINED && isDirtyRow != row ) // needs to submit previous changed row
        {
            int lastPriOfRow = getRowPriValue( row );

            if( lastPriOfRow == qp::db::ROW_UNDEFINED ) // insertRow
            {
                if ( ! submit() )
                {
                    QMessageBox::warning(0 ,
                                         qp::dbg::error_ ,
                                         tr("QpSqlTableModel::setData: OnRowChange: submit return false  , row %1 (id : %2)").
                                         arg(row).
                                         arg(lastPriOfRow));
                    return false;

                }
                //qDebug() << "QpSqlTableModel::setData() , submit dirty row is OK";
            }

            // ---------------------------------------
            // restore current row position
            // ---------------------------------------

            row = findRowById( lastPriOfRow );

            if ( row == qp::db::ROW_UNDEFINED )
            {
                QMessageBox::warning(0 ,
                                     qp::dbg::error_ ,
                                     tr("OnRowChange: lost focus on row %1 (id : %2)").
                                     arg(row).
                                     arg(lastPriOfRow));
                return false;

            }

            //qDebug() << "QpSqlTableModel::setData() , restore current row after submit/select is OK";

            idx2 = createIndex( row , col);

            if( ! idx2.isValid() )
                return false;

            emit sig_rowIsDirty( isDirtyRow );

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



int QpSqlTableModel::fieldIndex(const QString &fieldName) const
{
    // don't use anymore
    return -1;
}




QString QpSqlTableModel::relationField(const QString &tableName,
                                       const QString &fieldName) const
{
    QString ret;

    ret.reserve(tableName.size() + fieldName.size() + 1);

    ret.append(tableName).append(QLatin1Char('.')).append(fieldName);

    return ret;
}


void QpSqlTableModel::setDirtyRow(int dirtyRow , int dirtyCol)
{

    //qDebug() << "setDirtyRow() " << dirtyRow;

    // 0 - undefined because of insertRow

    lastDirtyRowId  = getRowPriValue( dirtyRow );

    isDirtyRow      = dirtyRow;

    lastDirtyCol    = dirtyCol;

    isSelectedLine  = dirtyRow;

    //    qDebug() << "        lastDirtyRowId " <<lastDirtyRowId ;
    //    qDebug() << "        lastDirtyCol   " <<lastDirtyCol ;
    //    qDebug() << "        isDirtyRow     " <<isDirtyRow ;
    //    qDebug() << "        isSelectedLine " <<isSelectedLine ;

}



void QpSqlTableModel::clearDirtyRow()
{
    isDirtyRow      = qp::db::ROW_UNDEFINED;
    isSelectedLine  = qp::db::ROW_UNDEFINED;

}

void QpSqlTableModel::clear()
{
    //qDebug() << "QpSqlTableModel::clear() " <<tableName();

    QSqlTableModel::clear();

    QpAbstractTableModel::clearContainers();

}

/*void QpSqlTableModel::fetchMore(const QModelIndex &parent)
                  {
                      qDebug() << "QpSqlTableModel::fetchMore( " << tableName();
                      QSqlQueryModel::fetchMore(parent);

                  }*/

bool QpSqlTableModel::canFetchMore(const QModelIndex &parent) const
{
    bool bbb = QSqlQueryModel::canFetchMore(parent);

    //qDebug() << "QpSqlTableModel::canFetchMore  " << bbb <<  tableName();

    return bbb;

}


bool QpSqlTableModel::select()
{
    /*qDebug() << "QpSqlTableModel::select() " << tableName() << " lastDirtyRowId"
             << lastDirtyRowId << " isDirtyRow" << isDirtyRow << " lastDirtyCol " << lastDirtyCol
             << " isSelectedLine" << isSelectedLine;*/

    if(editStrategy() <= QSqlTableModel::OnRowChange)
    {
        clearDirtyRow();
    }


    bool bbb = QSqlTableModel::select();

    emit sig_afterSelect(bbb);

    if ( ! bbb) // here occures QpTableViewWrapper::reset()
        return false;


    lastDirtyRowId = qp::db::ROW_UNDEFINED;
    lastDirtyCol = qp::db::COL_UNDEFINED;
    isDirtyRow = qp::db::ROW_UNDEFINED;
    isInsertRow = qp::db::ROW_UNDEFINED;

    /*qDebug() << " after QpSqlTableModel::select() : " << tableName()
             << " lastDirtyRowId " << lastDirtyRowId
             << " isDirtyRow"  << isDirtyRow
             << " lastDirtyCol " << lastDirtyCol
             << " isSelectedLine" << isSelectedLine;*/



    return true;
}

QVariant QpSqlTableModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
    QVariant vv = QSqlTableModel::headerData( section , orientation , role );

    if(orientation == Qt::Horizontal)
    {

        QString fldName = baseRec.fieldName( section );

        if( role == Qt::DisplayRole)
        {
            if( section > origTblColumnCount )
            {
                // ------------------------------------------------------------
                // needs only for column number greater than record().count() [orig table column count]
                // ------------------------------------------------------------


                if( colInfo.contains( fldName ))
                {
                    //qDebug() << "QpSqlTableModel::headerData role : " << qp::dbg::roleToStr(role) << " section : " << section << " origTblColumnCount " << origTblColumnCount << fldName << colInfo[ fldName ].header;

                    return colInfo[ fldName ].header;
                }
                else
                {
                    //qDebug() << " fldName "<< fldName;
                }
            }
            else
                ;//qDebug() << "QpSqlTableModel::headerData role :: " << qp::dbg::roleToStr(role) << " origTblColumnCount " << origTblColumnCount << " section : " << section << fldName << vv;

        }
        else if( role == Qt::DecorationRole)
        {
            //qDebug() << "QpSqlTableModel::headerData role : " << qp::dbg::roleToStr(role) << " section : " << section << fldName << vv;
        }
        else
        {
            /*
                you can change here the behavior for this roles:

                TextColorRole
                BackgroundRole
                DecorationRole
                TextAlignmentRole
                FontRole
             */
            //qDebug() << "QpSqlTableModel::headerData role : " << role << " section : " << section << fldName << vv;
        }



    }

    return vv;
}

bool QpSqlTableModel::setHeaderData(int section,
                                    Qt::Orientation orientation,
                                    const QVariant &value,
                                    int role )
{
    // reimplement

    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::EditRole)
        {
            // only for column number greater than record().count()

            if( section >=origTblColumnCount )
            {

                QString fldName = baseRec.fieldName( section );

                QString hdr = value.toString();

                colInfo[ fldName ].header = hdr;


                if( section == 27)
                {
                    QVariant vv = QSqlTableModel::headerData( section , orientation , role );

                }
                else
                {

                }
            }
        }
        else
        {

            //qDebug() << "QpSqlTableModel::setHeaderData role : " << qp::dbg::roleToStr(role) << "  section : " << section << orientation << value;
        }
    }

    QSqlTableModel::setHeaderData( section, orientation , value, role );

    return true;
}


bool QpSqlTableModel::change_fld_list(const QList<QString> &lst)
{

    reset();

    QpSqlRecord newRec;

    qDebug() << lst.count() << "baseRec " << baseRec;

    QSqlRecord baseRec2 = db_.record( tableName() ); // заново считываем

    for(int col=0 ; col < lst.count(); col++)
    {
        QString fldName = lst.at( col);

        if ( baseRec2.contains( fldName ) )
        {
            newRec.append( baseRec2.field( fldName ));

        }
        else if( calc_columns.contains( fldName) )
        {
            newRec.append( baseRec2.field( fldName ));
        }
        else if( relations2.contains( fldName) )
        {
            newRec.append( baseRec2.field( fldName ));
        }


        qDebug() << "fieldName " << baseRec.fieldName( col);
    }

    qDebug() << "newRec " << newRec;

    baseRec.clear();

    baseRec = newRec;

    qDebug() << "baseRec " << baseRec;

    //    bool bbb = select();

    //    qDebug() << "select " << bbb;

    return true;
}


bool QpSqlTableModel::prepare_mdl( const QString &tableName,
                                   const QList<QString> &fldList,
                                   const QHash<QString,QVariant> &SubCountingFilter)
{

    if(! db_.isValid() )
    {
        QMessageBox::critical(0 ,
                              qp::dbg::error_ ,
                              tr("database is not valid!"));
        return false;
    }

    if( ! db_.isOpen())
    {
        QMessageBox::critical(0 ,
                              qp::dbg::error_ ,
                              tr("database is not opened!"));
        return false;
    }

    if(  db_.isOpenError())
    {
        QMessageBox::critical(0 , qp::dbg::error_ , tr("database is not opened! %1").arg(db_.lastError().text()));
        return false;
    }

    if ( db_.tables().isEmpty())
    {
        QMessageBox::critical( 0 ,
                               qp::dbg::error_,
                               QObject::tr("database is empty?\n %1:\n error: %2").
                               arg(db_.databaseName()).
                               arg(db_.lastError().text()));

        return false;
    }

    if (tableName.isEmpty())
    {
        QMessageBox::critical( 0 ,
                               qp::dbg::error_,
                               QObject::tr("empty table name '%1'").
                               arg(tableName));

        return false;
    }


    if (! database().tables().contains(tableName))
    {
        QMessageBox::critical( 0 ,
                               qp::dbg::error_,
                               QObject::tr("database is not contains table '%1' ?\n\n error: %2").
                               arg(tableName).
                               arg(db_.lastError().text()));

        return false;
    }



    // ----------------------------------------------------
    //                      setTable
    // ----------------------------------------------------

    setTable( tableName ); // !!!


    // ----------------------------------------------------------
    //      may be call external function for setting this mdl
    // ----------------------------------------------------------

    if( callback_setting_mdl_func != 0)
    {
        qDebug() << "QpSqlTableModel::prepare_mdl table: " << tableName;

        callback_setting_mdl_func( this ); //!!!!
    }

    // -------------------------------------------------------------------

    subAccountingFilter = SubCountingFilter;


    return true;

}

bool QpSqlTableModel::setRecord_withoutPriCol(int row,
                                              QSqlRecord &rec,
                                              MODE mode)
{


    QSqlRecord rec2 =rec;

    //prepareRecord( rec2, mode);

    qDebug() << "QSqlTableModel::setRecord editStrategy() " << editStrategy();

    // -----------------------------------------------------
    //                  Attention !
    // setRecord is temporary changes editStrategy to OnRowChange
    // -----------------------------------------------------

    bool bbb = QSqlTableModel::setRecord( row , rec2);

    qDebug() << "QSqlTableModel::setRecord editStrategy() " << editStrategy();

    return bbb;
}


bool QpSqlTableModel::translateFieldNames(
        int row,
        QSqlRecord &rec,
        QpSqlTableModel::MODE mode
        ) const
{
    // 1. Эта функция возвращает наименования полей к оригинальным
    // в SELECT наименование полей через as могут быть изменены
    // например для INSERT ROW нужны оригинальные поля


    //    foreach (QString fldName , baseRec.specialFld.keys())
    //    {
    //        // all special fileds need been set to generated NO !

    //        rec.field( fldName ).setGenerated( false);

    //        qDebug() << "specialFld  fldName " << fldName << " isGenerated " << rec.field( fldName ).isGenerated();
    //    }

    //return true;


    int count = baseRec.count();

    int isGeneratedCount = 0;


    for( int col=0; col < rec.count(); col++)
    {
        // pri col presents forever , dont remove pri column

        QString fldName = rec.fieldName( col );

        bool isRelationalColumn = isRelationColumn( fldName );


        if ( isRelationalColumn )
        {

            bool isGenereted_col = rec.field( col ).isGenerated();

            //QString fldName = rec.fieldName( col );

            int extCol = getRelIdColumn( col );


            //------------------------------------------------------------------------
            //  we must forever set generated OFF for ext columns
            //------------------------------------------------------------------------

            bool isGenereted_extCol = rec.field( extCol ).isGenerated();

            if( isGenereted_extCol )  // extCol is never writes to db, extCol is a virtual column
            {
                rec.setGenerated(extCol , false );
            }

            QVariant txt = rec.value(col);

            if ( editStrategy() == QSqlTableModel::OnFieldChange) // will be submit /select
            {
                if ( mode == INSERT)
                {
                    //------------------------------------------------------------------------
                    //                          Attention!
                    //
                    //  if edit strategy is OnFieldChange
                    //  if you used setRecord this temporary changes editStrategy to OnRowChange
                    //------------------------------------------------------------------------

                    // it occures when click insertRow and click to update relational field
                    // or if copyRow run

                    if( rec.isGenerated(extCol)) // is copyRow

                        qDebug() << "is copyRow"; // nothing to do

                    else

                        txt = rec.value(extCol).toInt(); // replace text from id

                    //isGeneratedCount++;

                }
                else if ( mode == UPDATE)
                {
                    //------------------------------------------------------------------------
                    //                          This is special case
                    //
                    //  with OnFieldChange/UPDATE case all setData functions calls this code
                    //  and only one column is generated yes
                    /*
                        QpSqlTableModel::translateFieldNames before  QSqlRecord( 12 )
                         " 0:" QSqlField("id", int, generated: no, typeID: 1) "0"
                         " 1:" QSqlField("productName_1_productName", QString, generated: no, typeID: 3) ""

                         " 2:" QSqlField("sub_2_val", QString, generated: yes !!!!! , typeID: 3) "L"

                         " 3:" QSqlField("price", double, generated: no, typeID: 2) "0"
                         " 4:" QSqlField("qty", double, generated: no, typeID: 2) "0"
                         " 5:" QSqlField("sum", double, generated: no, typeID: 2) "0"
                         " 6:" QSqlField("cmb", int, generated: no, typeID: 1) "0"
                         " 7:" QSqlField("chk", int, generated: no, typeID: 1) "0"
                         " 8:" QSqlField("foo", int, generated: no, typeID: 3) "0"
                         " 9:" QSqlField("goods_id_1", int, generated: no, typeID: 1) "0"
                         "10:" QSqlField("sub_accounting_id_2", int, generated: no, typeID: 1) "0"
                         "11:" QSqlField("goods_sub_on_1", int, generated: no, typeID: 1) "0"
                         */
                    // because of this case will calls submit(select) forever after this code
                    //------------------------------------------------------------------------


                    if( isGenereted_col ) // not for ext columns
                    {
                        qDebug() << "\n\nWe never update txt relation column with OnFieldChange/UPDATE \n"\
                                    "because of this case will calls submit(select) forever after this code\n\n";

                        return false; //  !!!!! it is true. Dont update in database
                    }

                    txt = rec.value(extCol).toInt(); // replace text from id

                }

            }

            else if ( editStrategy() == QSqlTableModel::OnRowChange) // will be submit /select

            {
                //------------------------------------------------------------------------
                //                          Attention!
                //
                //  if edit strategy is OnFieldChange
                //  if you used setRecord this temporary changes editStrategy to OnRowChange
                //------------------------------------------------------------------------

                if ( mode == INSERT)
                {

                    // it occures when click insertRow and click to update relational field
                    // or if copyRow run

                    if( isCopyRowMode( extCol , rec) ) // is copyRow

                        txt = rec.value(extCol).toInt(); // replace text from id

                    else

                        txt = rec.value(extCol).toInt(); // replace text from id

                    //isGeneratedCount++;

                }
                else if ( mode == UPDATE)
                {
                    txt = rec.value(extCol).toInt(); // replace text from id

                    // with relation field next will be submit

                    //isGeneratedCount++;
                }


            }
            else if ( editStrategy() == QSqlTableModel::OnManualSubmit)
            {
                // it occures only if submitAll was called

                txt = rec.value(extCol).toInt(); // replace text from id

                //isGeneratedCount++;
            }

            if( isGenereted_col || isGenereted_extCol)
            {
                //  -----------------------------------------------------
                //          replace field
                //  -----------------------------------------------------

                QSqlField ff = rec.field( col );

                QString name = baseRec.field( col ).name();  // replace record field name to original as in db exist, because of select query was changed it by AS operator

                ff.setName( name );

                ff.setValue( txt );

                ff.setGenerated( true );

                rec.replace( col , ff );

                isGeneratedCount++;
            }


        }
        else if( ! rec.isGenerated(col) )

            continue;

        else // generated On and not relational columns

            isGeneratedCount++;



    }

    //qDebug() << "\n\n\n translateFieldNames rec "<< rec << "\n\n";

    if(mode == INSERT)

        rec.remove( rec.indexOf(priColName) );

    if( isGeneratedCount > 0 )
        return true;
    else
    {
        /* QMessageBox::warning(0,
                             qp::dbg::error_,
                             tr("changes is not presents:\n"\
                                "table name '%1'").
                             arg(tableName()));*/

        qDebug()<< "translateFieldNames : changes is not presents";

        return false;
    }

}


bool QpSqlTableModel::updateRowInTable(int row, const QSqlRecord &values)
{

    // ----------------------------------------------------------------------
    // We changed field names to original as in table were
    // text filed values of relation field need to replaces with id values
    // By the way SQLITE succesful writing a text  into int field
    // ----------------------------------------------------------------------

    QSqlRecord rec = values;


    foreach( QString subOnColumn, specialFld.keys() )
    {
        SPECIAL_FLD_TYPES tt = specialFld[ subOnColumn ] ;

        if(  tt == SUBACCOUNT_ENABLE_FLD
             || tt == CALC_FLD
             )
        {

            QP_ASSERT( rec.indexOf( subOnColumn ) >=0 );

            rec.setGenerated( rec.indexOf( subOnColumn ) , false);
        }
    }

    // replace to original table field names
    // set generated no to relational id fields

    //qDebug() << "\n\n\nQpSqlTableModel::translateFieldNames before " << rec<< "\n\n";

    if( translateFieldNames(row, rec, UPDATE) )
    {

        //qDebug() << "\n\n\nQpSqlTableModel::translateFieldNames after " << rec<< "\n\n";

        return QSqlTableModel::updateRowInTable(row, rec);
    }

    return true;

}

bool QpSqlTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    // для OnManualSubmit

    bool bb = QSqlTableModel::removeRows( row , count , parent);

    return bb;

}

bool QpSqlTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    bool bb = QSqlTableModel::insertRows( row , count , parent);

    if( !bb)
        return false;


    if(count == 1)
    {
        for( int rr=row; rr < row +count; rr++)
        {
            bool foundDefVls = false;

            foreach(int col , defaultVls.keys())
            {

                if ( ! setData( index( rr, col) , defaultVls.value(col)))
                {
                    QMessageBox::warning( 0,
                                          qp::dbg::error_,
                                          tr("look reimplemention of insertRows function\n"\
                                             "class QpSqlTableModel\n"
                                             "we have to set a field default values"));

                    return bb;

                    // OnFieldChange is here not matter
                }

                foundDefVls  = true;
            }

            if( ! foundDefVls )
            {
                // set any one field (not pri) to genereted yes
                int pri_Col = baseRec.indexOf( priColName );

                for(int col=0; col < columnCount(); col++ )
                {
                    if (col == pri_Col)
                        continue;

                    QVariant val = data(index(row , col ));

                    if( ! setData( index(row , col ) , val))
                    {
                        QMessageBox::warning( 0,
                                              qp::dbg::error_,
                                              QString("function insertRows\n setData for some field returns false, row : %1, col: %2")
                                              .arg( row )
                                              .arg( col )
                                              );
                    }
                    break;
                }

            }

        }
    }

    return bb;
}





void QpSqlTableModel::sort(int col,
                           Qt::SortOrder order )
{

    QSqlTableModel::sort( col , order);
}

QString QpSqlTableModel::orderByClause() const
{

    if( orderSet.fldName.isEmpty() )

        return QSqlTableModel::orderByClause();

    return orderSet.getTxt();
}

QpSqlRecord QpSqlTableModel::qp_record(int row) const
{
    QpSqlRecord rec ( (QpCmnSqlTableModel*)this , record( row ) );

    return rec;
}
bool QpSqlTableModel::qp_setRecord(int row, const QpSqlRecord &record)
{
    return QSqlTableModel::setRecord( row , record );
}

void QpSqlTableModel::setBaseRec( QpCmnSqlTableModel *mdl, const QSqlRecord& rec)
{
    baseRec = rec;
    baseRec.setRefToModel( mdl );
}


QString QpSqlTableModel::selectStatement() const
{
    QString query;

    if (tableName().isEmpty())
        return query;

    QString sTablesList;
    QString sFieldsList;
    //QString where;

    QStringList lstTables;


    bool bFieldsFullName = true; //!!

    if( relations2.count()>0 || calc_columns.count()>0)
        bFieldsFullName = true;

    //-------------------------------------------------------
    //                STANDART FIELDS
    //-------------------------------------------------------

    int baseColumnCount =0 ;

    baseColumnCount = baseRec.count();

    int groupBy = 0;

    for (int col = 0; col < baseColumnCount; ++col)
    {
        QString name;

        QString fldName =  baseRec.fieldName( col );


        if(calc_columns.contains(fldName) )
        {
            //-------------------------------------------------------
            //                      CALC
            //-------------------------------------------------------

            QpCalcColumn calcCol = calc_columns.value(fldName);

            QString relTableAlias = QString(prefix+"_%1").arg(col);



            QStringList lst = calcCol.summaryField.split(QLatin1String(","));

            QString fields;

            name.
                    append(calcCol.calcFunc).
                    append(QLatin1String("("));

            for(int ii=0; ii < lst.count(); ii++) // this is a sum by some fields
            {

                if( calcCol.calcFunc == "sum" )
                {
                    name.
                            append(QString("ifnull((%1.%2 ),0)")
                                   .arg(calcCol.extTblName)
                                   .arg(lst.at(ii))
                                   );

                }
                else
                {
                    name.
                            append(calcCol.extTblName).
                            append(QLatin1String(".")).
                            append(lst.at(ii));
                }

                fields.append(lst.at(ii));

                if(ii < lst.count() -1)
                {
                    name.append(QLatin1String(" + "));

                    fields.append(QLatin1String("_"));
                }
            }
            name.append(QLatin1String(") as "));


            name.append(calcCol.select_as_name);

            groupBy++;

        }

        else if ( relations2.contains( fldName ) ) // RELATIION FIELDS
        {
            int exNumCol =  getRelIdColumn3( fldName  );

            if( ! relations2.contains( fldName ))

                qDebug() << " --------- ";

            QpSqlRelation relation = relations2.value( fldName );

            QString relTableAlias = QString(prefix+"_%1").arg(col);

            // -----------------------------------------------
            QString arg1 = relation.idField1Name;

            // -----------------------------------------------


            name = QString( relationField(relTableAlias , relation.dstFldName)).

                    append(QString::fromLatin1(" AS %1").
                           arg(relation.get_fld_name())); // restore filed name like original




            name += QString(",\n %1.%2 AS %3").
                    arg(relTableAlias).
                    arg(relation.idField2Name).
                    arg(relation.get_ext_fld_name());


            // третье поле - если есть субучет
            if( subAccnt.contains( fldName ))
                //if( baseRec.specialFld.contains( fldName )&&  baseRec.specialFld.contains( fldName ) == PblSqlRecord::SUBACCOUNT_ENABLE_FLD )
            {

                name += QString(",\n %1.%2 AS %3").
                        arg( relTableAlias).
                        arg( subAccnt[ fldName ].sub_on_fld_name_extTbl). // ??
                        arg( subAccnt[ fldName ].get_sub_on_fld_name())
                        ;

                col++; // !!!! pass next field
            }

            col++; // !!!! pass next field

        }
        else // EASY FIELDS
        {
            name = baseRec.fieldName(col);


            if( bFieldsFullName )
                name.prepend(QLatin1String(".")).prepend(tableName());

        }

        if( ! sFieldsList.isEmpty())
            sFieldsList.append(QLatin1String(",\n"));


        sFieldsList.append(name);

    }


    //qDebug() << "selectStatement FieldsList: " << sFieldsList;

    QString sAddFields;



    QString sExtLeftJoins;
    QStringList joinedTables;

    //-------------------------------------------------------
    //                      JOIN CALC
    //-------------------------------------------------------

    foreach(QString colName,  calc_columns.keys())
    {
        QpCalcColumn calcCol = calc_columns.value(colName);

        if( ! joinedTables.contains(calcCol.extTblName))
        {
            sExtLeftJoins.append(QLatin1String(" \nLEFT JOIN ")).
                    append(calcCol.extTblName).
                    append(QLatin1String(" ")).

                    append(QLatin1String(" ON ")).

                    append(tableName()).append(QLatin1String(".")).
                    append(calcCol.idField1Name).

                    append(QLatin1String("=")).

                    append(calcCol.extTblName).append(QLatin1String(".")).
                    append(calcCol.idField2Name);

            joinedTables.append(calcCol.extTblName);
        }

    }

    //-------------------------------------------------------
    //                      JOIN RELATION
    //-------------------------------------------------------

    foreach(QString colName,  relations2.keys())
    {
        QpSqlRelation relation = relations2.value(colName);

        int relCol = baseRec.indexOf(relation.idField1Name);

        QString relTableAlias = QString(prefix+"_%1").arg(relCol);


        sExtLeftJoins.append(QLatin1String(" \nLEFT JOIN ")).

                append(relation.extTblName).
                append(QLatin1String(" ")).
                append(relTableAlias).

                append(QLatin1String(" ON ")).

                append(tableName()).append(QLatin1String(".")).
                append(relation.idField1Name).

                append(QLatin1String("=")).

                append(relTableAlias).append(QLatin1String(".")).
                append(relation.idField2Name);


        joinedTables.append(relation.extTblName);



    }

    //------------------------------------------------------------

    sTablesList.append(lstTables.join(QLatin1String(" ")));

    if (sFieldsList.isEmpty())
    {
        qCritical() << tr("QpSqlTableModel::selectStatement() field list is empty");

        return query;
    }

    sTablesList.prepend(tableName());
    query.append(QLatin1String("\n\nSELECT "));

    //    if( ! sExtFieldNameAdds.isEmpty())
    //    {
    //        sFieldsList.append(sExtFieldNameAdds);
    //    }


    query.append(sFieldsList).append(sAddFields).append(QLatin1String(" \nFROM ")).append(sTablesList);


    if( ! sExtLeftJoins.isEmpty())
    {
        query.append(sExtLeftJoins);
    }

    // -------------------------------------------------
    //                      WHERE
    // -------------------------------------------------


    QString where;

    if( subAccountingFilter.count()>0 )
    {
        foreach(QString fld, subAccountingFilter.keys())
        {
            if( ! where.isEmpty() )
                where.append(" AND ");

            where.append( QString("%1=%2")
                          .arg( fld )
                          .arg( subAccountingFilter[fld].toString() ));
        }
    }

    if( ! filter().isEmpty() )
    {
        if( ! where.isEmpty() )
            where.append(" AND ");

        where.append(filter());
    }

    if( ! where.isEmpty() )
    {

        query.append( QString( " \nWHERE (%1)")
                      .arg(where));

    }


    // -------------------------------------------------
    //                     GROUP BY
    // -------------------------------------------------

    if( groupBy>0)
    {
        query.append(QLatin1String(" \nGROUP BY ")).append(tableName()).append(QLatin1String(".id"));
    }

    // -------------------------------------------------
    //                      HAVING
    // -------------------------------------------------

    if ( having.count()>0 )
    {
        // filter only for aggregate functions

        query.append(QLatin1String(" \nHAVING ("));

        QString havStr;

        foreach( QString fld, having.keys())
        {
            if(! havStr.isEmpty())
                havStr.append(" AND ");

            havStr.append(fld + "="+having.value(fld));
        }

        query.append( havStr );
        query.append(QLatin1String(")"));
    }

    // -------------------------------------------------
    //                      ORDER
    // -------------------------------------------------

    QString orderBy = orderByClause();

    if (!orderBy.isEmpty())
        query.append(QLatin1Char('\n')).append(orderBy);

#ifdef  PBL_SQL_DEBUG
    //qDebug() << "\nselectStatement : \n" << query;
#endif

    return query;
}



void QpSqlTableModel::setSort(int col, Qt::SortOrder order)
{

    orderSet.order = order;

    QP_ASSERT(baseRec.fieldName( col ).isEmpty()==false);

    QString fldName = baseRec.fieldName(col);

    qDebug() << "setSort "<< col << fldName;

    QP_ASSERT( fldName.isEmpty()==false );

    if( specialFld.contains( fldName))
    {
        orderSet.fldName = fldName;//calcCol.get_fld_name();
    }
    else if( relations2.contains( fldName))
    {
        // ----------------------------------------------------------
        //      sorting by column with a relation
        // ----------------------------------------------------------

        QpSqlRelation relCol = relations2[ fldName ];

        orderSet.fldName = relCol.get_ext_fld_name();

    }
    else
    {
        orderSet.fldName = tableName()+"."+ baseRec.fieldName( col );
    }


}


int QpSqlTableModel::columnCount(const QModelIndex &parent ) const
{
    //qDebug() << "QpSqlTableModel::columnCount " << baseRec.count();

    return baseRec.count();
}

int QpSqlTableModel::rowCount(const QModelIndex &parent ) const
{
    int rows = QSqlTableModel::rowCount();
    //qDebug() << "QpSqlTableModel::rowCount " << rows;

    return rows;
}



//bool QpSqlTableModel::insertRecord(int row, const QSqlRecord &record)
//{
//    qDebug() << "QpSqlTableModel::insertRecord(int row, const QSqlRecord &record)";

//    return true;
//}

//bool QpSqlTableModel::insertRecord(int row, const PblSqlRecord &rec)
//{

//    qDebug() << "\n ----------------------------------------------------------- \n";
//    qDebug() << "QpSqlTableModel::insertRecord(int row, const PblSqlRecord &record)";

//    qDebug() << "\n ----------------------------------------------------------- \n";
//    qDebug() << "PblSqlRecord &record : " << rec;

//    QSqlRecord rec2 = rec;

//    qDebug() << "\n ----------------------------------------------------------- \n";
//    qDebug() << "PblSqlRecord &record : rec2 " << rec2;

//    for( int col = 0; col < rec.count(); col++)
//    {
//        QString extRelFld = getRelIdColumn4( rec.fieldName( col ));

//        if ( ! extRelFld.isEmpty() )
//        {
//            if( rec2.value( extRelFld ).toInt() == qp::db::REL_EMPTY_ID)
//            {
//                rec2.setValue( col , QVariant());
//            }
//            else
//            {
//                rec2.setValue( col , rec.value( extRelFld ));
//            }

//            if( ! rec2.isGenerated( col))
//                rec2.setGenerated( col , true );


//        }
//    }

//    qDebug() << "\n ----------------------------------------------------------- \n";
//    qDebug() << "PblSqlRecord &record : rec2 " << rec2;


//    foreach ( QString fldExtName , rec.specialFld.keys() )
//    {
//        qDebug() << "remove 634586345 " << fldExtName ;

//        rec2.remove( rec2.indexOf( fldExtName ) );
//    }

//    qDebug() << "\n ----------------------------------------------------------- \n";
//    qDebug() << "PblSqlRecord &record : rec2 " << rec2;

//    bool bbb = QSqlTableModel::insertRecord( row, rec2);

//    bbb = select();

//    return bbb ;
//}



QT_END_NAMESPACE





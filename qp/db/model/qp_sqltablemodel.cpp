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
#include "qp/db/model/my_sql.h"
#include <QSqlTableModel>
#include "qp/db/view/some_tests.h"
#include "qdebug.h"
#include <QApplication>
#include <QSqlQuery>
#include "config.h"
#include "qp/db/model/my_sql.h"
#include <QMessageBox>
#include <QString>
#include <QSqlRecord>
#include <QSqlField>

#include "qp/db/model/qp_sqlrelation.h"
#include "qp/db/model/qp_calc_column.h"

#include "qp/db/model/qp_sqlrecord.h"
#include "qp/gui/qp_gui.h"
#include "qp/qp.h"

QT_BEGIN_NAMESPACE


const QLatin1String QpSqlTableModel::prefix = QLatin1String("relTbl");


const QString Order_Settings::asc = " ASC";
const QString Order_Settings::desc = " DESC";
const QString Order_Settings::ord = " ORDER BY ";

Order_Settings::Order_Settings()
    :
      fldName(QString()),
      order( Qt::AscendingOrder)
{

}

QString Order_Settings::getTxt()
{

    return ord + fldName + ( order == Qt::AscendingOrder ?  asc : desc) ;
}

//-------------------------------------------------------------------------------------

QpSqlTableModel::QpSqlTableModel(
        QSqlDatabase &Db,
        cb_setting_mdl pToSettingFunc,
        QObject *parent,
        const QList<QString> &FieldsSet
        )
    :
      QSqlTableModel( parent, Db),
      isDirtyRow( qp::db::ROW_UNDEFINED ),
      isInsertRow( qp::db::ROW_UNDEFINED ),
      lastDirtyCol( qp::db::COL_UNDEFINED ),
      lastDirtyRowId( qp::db::ROW_UNDEFINED ),
      isSelectedLine( qp::db::ROW_UNDEFINED ),
      db_( Db ),
      isDefaultSearchingColumn( qp::db::COL_UNDEFINED ),
      editable(false),
      priColName(QString()),
      callback_setting_mdl_func( pToSettingFunc ),
      origTblColumnCount(0)
{

    QP_ASSERT (Db.isValid() == true);

    QP_ASSERT (Db.isOpenError() == false);

    //qDebug() << "ctor QpSqlTableModel editStrategy " << editStrategy();

    qp::meta::cnct (this, SIGNAL(primeInsert(int,QSqlRecord&)),
              this, SLOT(slot_primeInsert(int,QSqlRecord&)));

}


int QpSqlTableModel::findRowById( int id )
{
    if(rowCount()==0)

        return qp::db::ROW_UNDEFINED;

    for(int row = 0 ; row < rowCount(); row++)
    {
        QModelIndex idx = index( row , getPriColumn() );

        if( ! idx.isValid())
            return qp::db::ROW_UNDEFINED;

        bool ok =false;

        int currId = data( idx ).toInt(&ok);

        if(! ok )
            return qp::db::ROW_UNDEFINED;

        if(currId == id)
            return row;
    }

    return qp::db::ROW_UNDEFINED;
}

void QpSqlTableModel::slot_primeInsert(int row, QSqlRecord &rec)
{
    //qDebug() << "QpSqlTableModel::slot_primeInsert ";// <<    rec;

    // this writes into private d->editBuffer (= rec)
    // and don't calls setData


    if ( ! config::set_newInsertedRowParameters(this , rec))
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

    calc_columns.clear();
    defaultVls.clear();
    relations2.clear();
    subAccnt.clear();
    rel_bindings.clear();
    colInfo.clear();
    subAccountingFilter.clear();
    having.clear();


}

QVariant QpSqlTableModel::data(const QModelIndex &idx, int role) const
{

    int row = idx.row();

    int col = idx.column();

    int baseCount = baseRec.count();

    //qDebug() << "::data "<< idx.column() << idx.row() << " role : " << role;

    const QString &fldName = baseRec.fieldName(col);


    if( role == Qt::TextAlignmentRole)
    {

        if( baseRec.specialFld.contains( fldName ))

            return Qt::AlignCenter;

    }

    if( colInfo.contains( fldName ) )
    {

        QpColumnInfo inf = colInfo[ fldName ];

        if(role == Qt::DisplayRole)
        {
            QVariant var =  QSqlTableModel::data(idx, role);

            if(inf.precision >0 && var.type() == QVariant::Double)

                return QString::number( var.toDouble(),
                                        inf.cFormat,
                                        inf.precision );
        }
        else if( role == Qt::TextAlignmentRole)
        {
            return colInfo[ fldName ].alignment;
        }
    }

    if( role == Qt::BackgroundColorRole ) // repaint
    {
        // here returns color
        // int r,g,b,a=0;

        if( baseRec.specialFld.contains( fldName ))
        {
            if( baseRec.specialFld[ fldName ] != QpSqlRecord::CALC_FLD )

                return  QColor( QApplication::palette().color(QPalette::AlternateBase) );
        }

    }


    if( calc_columns.contains( fldName ) && role == Qt::DisplayRole)
    {
        QVariant vv = QSqlTableModel::data(idx, role);

        if( vv.type() >= QVariant::Int && vv.type() <= QVariant::Double &&  vv.toDouble() == 0)

            //if( vv.isNull()) // !!!!

            return "";
    }

    return QSqlTableModel::data(idx, role);
}

void QpSqlTableModel::setEditStrategy( QSqlTableModel::EditStrategy strategy)
{

    //qDebug() << "QpSqlTableModel::setEditStrategy editStrategy " << this << "  strategy "<< strategy << tableName();

    QSqlTableModel::setEditStrategy(strategy);

    emit sig_editStrategyChanged(QSqlTableModel::editStrategy()); // needs for QTableView

}

Qt::ItemFlags QpSqlTableModel::flags(const QModelIndex &index) const
{

    int col = index.column();
    int row = index.row();


    Qt::ItemFlags flgs = QSqlTableModel::flags(index);

    const QString &fldName = baseRec.fieldName( col );

    if ( baseRec.specialFld.contains( fldName ) )
    {
        // ----------------------------------------------
        //              RELATIONS
        // --------------------------------------------

        if( ! editable )
            flgs = ( Qt::ItemIsSelectable |  Qt::ItemIsUserCheckable);
        else
            flgs = ( Qt::ItemIsSelectable |  Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

        //qDebug() << "editable : " << editable << "  col : " << index.column() << " flags : " << flgs;

        return flgs;
    }
    else if(relations2.contains( fldName ))
    {
        if( ! editable )
            flgs = ( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        else
            flgs = ( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable); // ItemIsEditable


    }
    else if( colInfo.contains( fldName ))
    {
        QpColumnInfo inf = colInfo[ baseRec.fieldName(col) ];

        if( ! editable )
            flgs = ( Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        else
            flgs = ( Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

        //qDebug() << "editable : " << editable << "  col : " << index.column() << " flags : " << flgs;

    }
    else
    {
        if ( ! editable )
        {
            flgs = ( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
            //qDebug() << "editable : " << editable << "  col : " << index.column() << " flags : " << flgs;

        }
        else
        {
            flgs = ( Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
            //flgs &= ~(Qt::ItemIsSelectable);
            //qDebug() << "editable : " << editable << "  col : " << index.column() << " flags : " << flgs;

        }

    }


    return flgs;
}

void QpSqlTableModel::set_editable( bool Editable)
{
    editable = Editable;
}

const QSqlRecord & QpSqlTableModel::baseRecord()
{

    return baseRec;
}

bool QpSqlTableModel::submit()
{
    // here we are following for dirty row
    qDebug() << "QpSqlTableModel::submit()";
    bool bbb = QSqlTableModel::submit();

    return bbb;
}

int QpSqlTableModel::getPriColumn( ) const
{
    return baseRec.indexOf( priColName);
}

int QpSqlTableModel::getRowPriValue(int row) const
{
    if( baseRec.indexOf( priColName ) == qp::db::COL_UNDEFINED)
    {
        QMessageBox::warning(0 ,
                             qp::dbg::error_,
                             tr("pri column have to exist in table!"));

        return qp::db::INT_UNDEFINED;
    }

    QModelIndex idx = index(row , baseRec.indexOf( priColName ) );

    if( ! idx.isValid())

        return qp::db::INT_UNDEFINED;

    QVariant pri = data( idx , Qt::DisplayRole);

    if( pri == QVariant()) // empty or undefined value, insertRow for exapmle
    {
        return qp::db::INT_UNDEFINED;
    }

    bool ok = false;

    int iPri = pri.toInt(&ok);

    if( ! ok )
    {
        QMessageBox::warning(0 ,
                             qp::dbg::error_,
                             tr("pri column value dont convert to int !"));
        return qp::db::INT_UNDEFINED;
    }


    return iPri;
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
bool QpSqlTableModel::setRelation( QpSqlRelation &relation )
{

    if( ! baseRec.contains( relation.idField1Name)  )
    {
        qCritical() << tr("QpSqlTableModel::setRelation. Error finding  : %1 ").arg(relation.idField1Name);

        return false;
    }


    //--------------------------------------------
    //          duplicate protect
    //--------------------------------------------

    if( relations2.contains( relation.idField1Name ))
    {

        QMessageBox::warning(0,
                             "error",
                             QString("QpSqlTableModel::setRelation. This is a second trying to add setRelation for column : %1 , table %2")
                             .arg(relation.idField1Name)
                             .arg(tableName())
                             );

        return false;
    }

    // --------------------------------------------

    int relCol = baseRec.indexOf( relation.idField1Name ) ;

    QP_ASSERT ( relCol >= 0 );



    int newRelIdCol = baseRec.count() + relations2.count();

    //relations.insert( relCol ,newRelIdCol);

    relations2.insert( relation.idField1Name , relation);

    //qDebug() << " relation.get_ext_fld_name() " << relation.get_ext_fld_name();

    QSqlField relIdSqlFld; // !!
    relIdSqlFld.setName( relation.get_ext_fld_name() );
    relIdSqlFld.setType( QVariant::Int ); // else
    //relIdSqlFld.setReadOnly( true );
    relIdSqlFld.setRequired( false );
    relIdSqlFld.setValue( (int) 0 );
    //relIdSqlFld.setAutoValue( false );

    bool bbb = relIdSqlFld.isValid();

    baseRec.insert( relCol + 1 , relIdSqlFld ); // !!!

    bbb = baseRec.value( relCol + 1) .isValid();

    //baseRec.specialFld.insert( relation.idField1Name, PblSqlRecord::RELATION_TXT_FLD ); // !!!!
    baseRec.specialFld.insert( relation.get_ext_fld_name(), QpSqlRecord::RELATION_ID_EXT_FLD ); // !!!!



    return true;
}

bool QpSqlTableModel::setSubAccount(

        const QString & parentTblName ,    // parent table name
        const QString & col1Name ,      // parent field name
        const QString & col2Name ,      // child field id name
        const QString & filterColName,  // child filter name
        const QString & sub_on
        )
{


    QP_ASSERT ( baseRec.indexOf(col1Name) >=0 );


    int col1 = baseRec.indexOf(col1Name);

    if( ! relations2.contains( col1Name))

        return false;

    // ------------------------------------

    QpSubAccnt SubAccnt( parentTblName, col1Name , col2Name , sub_on);

    subAccnt.insert( col1Name , SubAccnt );

    // ------------------------------------

    // ----------------------------------------------------------

    rel_bindings.insert(col2Name , &subAccnt[col1Name]);

    //-----------------------------------------------------

    QString sub_on_fldName = subAccnt[col1Name].get_sub_on_fld_name();

    QP_ASSERT(sub_on_fldName.isEmpty()==false);

    QSqlField sqlFld;

    sqlFld.setName( sub_on_fldName );
    sqlFld.setType( QVariant::Int ); // else isValid = false

    baseRec.insert( col1 + 2 , sqlFld ); // !!!!!!!!

    QP_ASSERT ( baseRec.field( col1 + 2 ).isValid() == true) ;


    baseRec.specialFld.insert( sub_on_fldName , QpSqlRecord::SUBACCOUNT_ENABLE_FLD ); // !!!!

    int col2 = baseRec.indexOf(col2Name);

    QP_ASSERT ( baseRec.indexOf(col2Name) >=0 );

    if( ! relations2.contains(col1Name) || ! relations2.contains(col2Name))
    {
        QMessageBox::critical(0,
                              tr("Error"),
                              tr("setBinding is not correct\n"\
                                 "before you should create two relations"));

        return false;
    }

    // ------------------------------------------------------------------------------------------------
    // dont use value() , this will be a copy and removes with return from this function
    // ------------------------------------------------------------------------------------------------


    //    addSubAcntOnField( relations2[ col1Name ] ,
    //                       col1 ,
    //                       col2 ,
    //                       sub_on );

    //relations2[col1Name].srvSubAcntParentFld = filterColName;

    //relations2[col2Name].subDisplayAcntColumn = col1;



    return true;
}


bool QpSqlTableModel::setCalcField( QpCalcColumn Calc)
{
    if(tableName().isNull() || tableName().isEmpty())
    {
        qCritical() << "missing call setTable() before setCalcField";
        return false;
    }

    if( Calc.extTblName.isEmpty() || Calc.extTblName.isNull())
        return false;

    if( Calc.idField1Name.isEmpty() || Calc.extTblName.isNull())
        return false;

    if( Calc.idField2Name.isEmpty() || Calc.idField2Name.isNull())
        return false;

    if( Calc.calcFunc.isEmpty() || Calc.calcFunc.isNull())
        return false;

    //PblCalcColumn Calc ( summaryField , extTblName , idField1Name, idField2Name, calcFunc, col_after) ;


    QpSqlField CalcFld ( QpSqlField::FLD_CALC , Calc.select_as_name );

    int before;

    if( ! Calc.col_after.isEmpty() )
    {
        if( ! baseRec.contains(Calc.col_after) )
        {
            return false;
        }

        before = baseRec.indexOf( Calc.col_after );



    }
    else
    {
        before = baseRec.count();
    }

    baseRec.insert( before ,  CalcFld);

    //qDebug() << " baseRec " << baseRec;

    calc_columns.insert( Calc.select_as_name , Calc ) ;  // , extCol ) );


    baseRec.specialFld.insert( Calc.select_as_name , QpSqlRecord::CALC_FLD );


    return true;
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

void QpSqlTableModel::setTable(const QString &tableName)
{
    QSqlTableModel::setTable( tableName );

    baseRec = record( );

    origTblColumnCount = baseRec.count();

    // ----------------------------------------------------

    if(baseRec.isEmpty())
    {
        QMessageBox::critical(0 ,
                              qp::dbg::error_ ,
                              tr("table '%1' is not valid [37675676576]").
                              arg(tableName));
        return;
    }

    relations2.clear();

    colInfo.clear();

    subAccnt.clear();

    rel_bindings.clear();

    primaryIndex = db_.primaryIndex(tableName);

    if( primaryIndex.count() ==0 )
    {
        QMessageBox::warning( 0,
                              "Error in table "+ tableName,
                              "Each table have to exists one pri field!");
    }
    else if( ! primaryIndex.isEmpty() && primaryIndex.count() == 1)
    {
        priColName = primaryIndex.fieldName(0);
    }
    else if( primaryIndex.count() >1)
    {
        QMessageBox::warning( 0,
                              "Error",
                              "Unfortunately only one primary column accessable!");
    }

    // -------------------------------------------------------
    //              add some calc columns
    // -------------------------------------------------------

    foreach( QpCalcColumn calc , calc_columns.values())
    {
        if( ! baseRec.contains( (calc.col_after) ) )
        {
            QMessageBox::warning( 0 ,
                                  "prepare_mdl",
                                  QString("column %1 is unknown")
                                  .arg(calc.col_after)
                                  );
        }

        int pos = baseRec.indexOf( calc.col_after );

        baseRec.insert( pos , calc.select_as_name );

    }

    //    for (int col=0; col < baseRec.count(); col++)
    //    {
    //        QSqlField fld = baseRec.field( col );
    //        qDebug() << "QSqlField:" << fld<< " defaultValue:" << fld.defaultValue();
    //    }


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

    setTable(tableName); // !!!


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

bool QpSqlTableModel::removePrimaryKeys_fromRec(QSqlRecord &rec, MODE mode)
{
    // later the setRecord method will calls setData

    QSqlIndex priKey = primaryKey();

    //qDebug() << "priKey " << priKey;

    for( int ii=0; ii< priKey.count(); ii++ )
    {
        QSqlField fld = priKey.field( ii );

        rec.setValue(priColName , QVariant() );

        rec.setGenerated( fld.name() , false);

    }

    //rec.remove(priCol); dont remove any field


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

bool QpSqlTableModel::prepareInsertRow( int row,
                                                   QSqlRecord &rec)
{

    int count = baseRec.count();

    int isGeneratedCount = 0;


    for( int col=0; col < rec.count(); col++)
    {
        QString fldName = rec.fieldName( col );

        if ( isRelationColumn( fldName ) )
        {

            bool isGenereted_col = rec.field( col ).isGenerated();

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
                //------------------------------------------------------------------------
                //                          Attention!
                //
                //  if edit strategy is OnFieldChange
                //  if you used setRecord this temporary changes editStrategy to OnRowChange
                //------------------------------------------------------------------------

                // it occures when click insertRow and click to update relational field
                // or if copyRow run

                if( rec.isGenerated( extCol )) // is copyRow

                    qDebug() << "is copyRow"; // nothing to do

                else

                    txt = rec.value(extCol).toInt(); // replace text from id !


            }

            else if ( editStrategy() == QSqlTableModel::OnRowChange) // will be submit /select

            {
                //------------------------------------------------------------------------
                //                          Attention!
                //
                //  if edit strategy is OnFieldChange
                //  if you used setRecord this temporary changes editStrategy to OnRowChange
                //------------------------------------------------------------------------


                // it occures when click insertRow and click to update relational field
                // or if copyRow run

                //if( isCopyRowMode( extCol , rec) ) // is copyRow

                txt = rec.value(extCol).toInt(); // replace text from id !

                //                else

                //                    txt = rec.value(extCol).toInt(); // replace text from id


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

    rec.remove( rec.indexOf(priColName) ); // !!


    foreach ( QString extFld ,  calc_columns.keys())
    {
        QP_ASSERT (rec.contains( extFld )==true);

        qDebug() << "remove " << extFld;

        rec.remove( rec.indexOf( extFld ) );

    }

    foreach ( QString extFld ,  relations2.keys())
    {
        QP_ASSERT (rec.contains( extFld )==true);

        qDebug() << "remove " << extFld << relations2[ extFld ].get_ext_fld_name();

        rec.remove( rec.indexOf( relations2[ extFld ].get_ext_fld_name() ) );

    }

    foreach ( QString extFld ,  subAccnt.keys())
    {
        qDebug() << "remove " << extFld;

        //QP_ASSERT (rec.contains( extFld )==true);

        //rec.remove( rec.indexOf( extFld ) );

    }

    if( isGeneratedCount > 0 )
    {
        return true;
    }
    else
    {
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


    foreach( QString subOnColumn, baseRec.specialFld.keys() )
    {
        QpSqlRecord::SPECIAL_FLD_TYPES tt = baseRec.specialFld[ subOnColumn ] ;

        if(  tt == QpSqlRecord::SUBACCOUNT_ENABLE_FLD
             || tt == QpSqlRecord::CALC_FLD
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

                for(int colunm=0; colunm < columnCount(); colunm++ )
                {
                    if (colunm == pri_Col)
                        continue;

                    QVariant val = data(index(row , colunm ));

                    if( ! setData( index(row , colunm ) , val))
                    {
                        QMessageBox::warning( 0,
                                              qp::dbg::error_,
                                              tr("function insertRows\n"\
                                                 "setData for some field returns false"));
                    }
                    break;
                }

            }

        }
    }

    return bb;
}


bool QpSqlTableModel::insertRowIntoTable(const QSqlRecord &values)
{
    QSqlRecord rec = values;

    qDebug() << "\n\n\nQpSqlTableModel::insertRowIntoTable values " << values << "\n\n";

    // it occures when insetRow: insertRow and copyRow too!

    // --------------------------------------------------------------------------
    //          all special (extened) columns set generated no
    // --------------------------------------------------------------------------

    for( int col=0; col< rec.count(); col++)
    {

        QString fldName = rec.fieldName( col );

        QP_ASSERT( baseRec.contains( fldName ) ) ;

        if ( baseRec.specialFld.contains( fldName ) )
        {
            QpSqlRecord::SPECIAL_FLD_TYPES tt = baseRec.specialFld[ fldName ] ;

            if(  tt == QpSqlRecord::SUBACCOUNT_ENABLE_FLD
                 || tt == QpSqlRecord::CALC_FLD
                 )
            {

                rec.setGenerated( fldName , false);
            }
        }
    }

    // --------------------------------------------------------------------------
    //
    // --------------------------------------------------------------------------

    foreach( QString fldName , subAccountingFilter.keys())
    {
        QP_ASSERT( rec.indexOf( fldName )>=0);

        int id  = subAccountingFilter.value( fldName ).toInt();

        //QP_ASSERT(id>=0);

        rec.setValue( fldName , id );
        rec.setGenerated( fldName , true );

    }



    qDebug() << "\n\n\nQpSqlTableModel::insertRowIntoTable before " << rec << "\n\n";

    prepareInsertRow(0, rec);

    qDebug() << "\n\n\nQpSqlTableModel::insertRowIntoTable translateFieldNames " << rec<< "\n\n";

    bool res = QSqlTableModel::insertRowIntoTable(rec); // insert all fields (with generated=no too)

    //qDebug() << "\n\n\nQpSqlTableModel::insertRowIntoTable after " << rec<< "\n\n";

    if( res )
    {
        lastDirtyRowId = getLastInsertId();
    }

    return res;
}

int QpSqlTableModel::getLastInsertId()
{

    QSqlQuery qq(  db_ );

    if( ! qq.exec("SELECT last_insert_rowid()") )
    {
        QMessageBox::warning( 0,
                              "error",
                              qq.lastError().text()
                              );

        return qp::db::ROW_UNDEFINED;

    }

    if( qq.next() )
    {
        bool ok = false;

        int lastIsertId = qq.value(0).toInt(&ok);

        if(ok)
        {
            return lastIsertId;
        }
        else
        {
            return qp::db::ROW_UNDEFINED;

        }

        qDebug() << "lastInsertId " <<  lastIsertId;
    }


    return qp::db::ROW_UNDEFINED;
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

void QpSqlTableModel::setColInf(const QString & colName , const QpColumnInfo & inf)
{
    colInfo[ colName ] = inf;
}


void QpSqlTableModel::setAlignment(const QString & colName , Qt::Alignment align)
{
    colInfo[colName].alignment = align;
}

void QpSqlTableModel::setPrecision(const QString & colName , int precision)
{
    colInfo[colName].precision = precision;

}

void QpSqlTableModel::setEditable(const QString & colName , bool on)
{
    colInfo[colName].editable = on;

}

void QpSqlTableModel::setSelectable(const QString & colName , bool on)
{
    colInfo[colName].selectable = on;

}


void QpSqlTableModel::set_Visible(const QString & colName , bool on)
{
    colInfo[colName].is_visible = on;

}

void QpSqlTableModel::setDblFormat(const QString & colName , char ch)
{
    colInfo[colName].cFormat = ch;

}


QpSqlRelation QpSqlTableModel::getRelationInfoForColumn(const QString &fldName)
{

    if( ! relations2.contains( fldName ))

        return QpSqlRelation();

    return relations2[fldName];
}

bool QpSqlTableModel::isRelationColumn( const QString &  fldName) const
{

    Q_ASSERT_X(fldName.isEmpty()==false,"6727984762565","56823056256");

    return relations2.contains( fldName );
}

bool QpSqlTableModel::isCalcColumn(const QString &colName) const
{

    /*if(col < baseRec.count())
        return false;

    int exCol = col - baseRec.count();

    if( exCol >= ex_columns.count() )
        return false;*/

    if( baseRec.specialFld.contains( colName ) && baseRec.specialFld.value( colName ) == QpSqlRecord::CALC_FLD)

        return true;


    return false;
}

bool QpSqlTableModel::isRelationalColumn(int col)
{
    QString fldName = baseRec.fieldName( col );

    QP_ASSERT(fldName.isEmpty()==false);

    if( relations2.contains(fldName))
        return true;

    return false;
}

int QpSqlTableModel::getRelIdColumn3(const QString & fldName) const
{

    if(! relations2.contains( fldName ))

        return qp::db::COL_UNDEFINED;

    QpSqlRelation ff = relations2.value( fldName );

    const QString relIdFldName = ff.get_ext_fld_name();

    if( relIdFldName.isEmpty() || ! baseRec.contains( relIdFldName ))

        return qp::db::COL_UNDEFINED;



    return baseRec.indexOf( relIdFldName ) ;
}

QString QpSqlTableModel::getRelIdColumn4(const QString & fldName)
{

    if(! relations2.contains( fldName ))

        return QString();

    QString relIdFldName = relations2[ fldName ].get_ext_fld_name();

    if( fldName.isEmpty() || ! baseRec.contains( relIdFldName ))

        return QString();

    return relIdFldName;
}

bool QpSqlTableModel::isSpecialColumn(int col) const
{
/*
     " 0:" QSqlField("id", int, required: no, generated: yes) "0"
     " 1:" QSqlField("name", QString, required: no, generated: yes) ""
     " 2:" QSqlField("date_", int, required: no, generated: yes) "0"
     " 3:" QSqlField("taxCode", int, required: no, generated: yes, auto-value: "QVariant(QString, "-1") " ) "0"
     " 4:" QSqlField("contractors", int, required: no, generated: yes, auto-value: "QVariant(QString, "0") " ) "0"
     " 5:" QSqlField("contractors_contractors_id", int, required: no, generated: yes) "0"
     " 6:" QSqlField("suppliers", int, required: no, generated: yes, auto-value: "QVariant(QString, "0") " ) "0"
     " 7:" QSqlField("suppliers_suppliers_id", int, required: no, generated: yes) "0"
     " 8:" QSqlField("cash_ecash_prepayment_credit_consideration", , generated: yes) ""  ?????? type ?????
     " 9:" QSqlField("cash", , generated: yes) ""
     "10:" QSqlField("ecash", , generated: yes) ""
     "11:" QSqlField("prepayment", , generated: yes) ""
     "12:" QSqlField("credit", , generated: yes) "
 */
//    if (  baseRec.field( col ).isValid() )
//    {
//        qDebug() << "QpSqlTableModel::isSpecialColumn " <<col << baseRec;
//        return false;
//    }

    if( baseRec.fieldName( col ).isEmpty() )

        return false;

    if( ! baseRec.specialFld.contains( baseRec.fieldName( col ) ) )

        return false;


    return true;

}


int QpSqlTableModel::getRelIdColumn(int col) const
{

    if (  ! baseRec.field( col ).isValid() )

        return qp::db::COL_UNDEFINED;


    QString fldName = baseRec.fieldName( col );

    if( fldName.isEmpty() )

        return qp::db::COL_UNDEFINED;


    if( ! relations2.contains( fldName ) )

        return qp::db::COL_UNDEFINED;

    QpSqlRelation pp = relations2[ fldName ];

    QString relIdFldName = pp.get_ext_fld_name();

    return baseRec.indexOf( relIdFldName );


}

int QpSqlTableModel::getAccountingOnColumn(int relCol) const
{

    QString fldName = baseRec.fieldName( relCol);

    if( fldName.isEmpty())

        return qp::db::COL_UNDEFINED;


    if(subAccnt.contains( fldName ))
    {
        qDebug() << subAccnt[ fldName ].get_sub_on_fld_name();
        //QP_ASSERT_X (subAccnt[ fldName ].get_sub_on_fld().isEmpty()==true, "456533654", "6786754352");

        int on_sub_col = baseRec.indexOf( subAccnt[ fldName ].get_sub_on_fld_name() );

        QP_ASSERT( on_sub_col>=0 );

        return on_sub_col;

    }
    else
        return qp::db::COL_UNDEFINED;
}

bool QpSqlTableModel::isRelationExtIdColumn(int col) const
{


    if( getRelIdColumn(  col )  != -1)

        return true;

    return false;
}



void QpSqlTableModel::setSort(int col, Qt::SortOrder order)
{

    orderSet.order = order;

    QP_ASSERT(baseRec.fieldName( col ).isEmpty()==false);

    QString fldName = baseRec.fieldName(col);

    qDebug() << "setSort "<< col << fldName;

    QP_ASSERT( fldName.isEmpty()==false );

    if( baseRec.specialFld.contains( fldName))
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


QpSqlRecord QpSqlTableModel::getPblSqlRecord( const QSqlRecord & rec)
{

    QpSqlRecord pblRec( * this , rec); // copy ctor


    //pblRec.priCol = priCol;

    pblRec.specialFld = baseRec.specialFld;

    qDebug()<<" getPblSqlRecordrec : "  << rec;

    return pblRec;
}

bool QpSqlTableModel::isSubAccounting(const QString &fldName)
{

    if(fldName.isEmpty())

        return false;


    if ( subAccnt.contains( fldName ))
    {
        return true;
    }

    return false;
}

bool QpSqlTableModel::isSubAccountingOn_forFld(int row, const QString &fldName)
{
    if(fldName.isEmpty())

        return false;

    if( isSubAccounting ( fldName ))
    {

        if( subAccnt.contains( fldName ))
        {
            QString sub_on_fldName = subAccnt[ fldName ].get_sub_on_fld_name();

            QP_ASSERT(sub_on_fldName.isEmpty()==false);

            int colSubOn = baseRec.indexOf(sub_on_fldName );

            QP_ASSERT( colSubOn >=0);

            QModelIndex idx = index( row, colSubOn );

            if (idx.isValid())
            {
                QVariant res = data( idx );

                if ( res.toBool() )

                    return true;
            }


        }
    }
    return false;
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

QString QpSqlTableModel::sqlite_qoutes_for_value(const QVariant & val)
{

    if(val.type() == QVariant::String)

        return val.toString().prepend("'").append("'");

    else

        return val.toString();
}

int QpSqlTableModel::indexOf(const QString &fieldName) const
{
    return QSqlTableModel::record().indexOf( fieldName );
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




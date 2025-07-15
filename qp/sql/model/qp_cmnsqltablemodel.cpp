#include "qp_cmnsqltablemodel.h"
#include "qp/sql/qp_sql.h"
#include <QMessageBox>
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
#include <QSqlTableModel>
#include "qdebug.h"
#include <QApplication>
#include <QSqlQuery>
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

const QLatin1String QpCmnSqlTableModel::prefix = QLatin1String("relTbl");

QpCmnSqlTableModel::QpCmnSqlTableModel(QSqlDatabase &Db,
                                       cb_setting_mdl pToSettingFunc,
                                       QObject *parent) :
    QSqlTableModel(parent , Db),
    QpAbstractTableModel(),
    db_(Db),
    callback_setting_mdl_func( pToSettingFunc ),
    origTblColumnCount(0),
    isDirtyRow( qp::db::ROW_UNDEFINED ),
    isInsertRow( qp::db::ROW_UNDEFINED ),
    lastDirtyCol( qp::db::COL_UNDEFINED ),
    lastDirtyRowId( qp::db::ROW_UNDEFINED ),
    isSelectedLine( qp::db::ROW_UNDEFINED ),
    isDefaultSearchingColumn( qp::db::COL_UNDEFINED )
{

    //qDebug() << "callback_setting_mdl_func" <<callback_setting_mdl_func << pToSettingFunc;
}

int QpCmnSqlTableModel::findRowById( int id )
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

const QpSqlRecord QpCmnSqlTableModel::baseRecord()
{

    return baseRec;
}

const QpSqlRecord QpCmnSqlTableModel::getBaseRec() const
{
    return baseRec;
}

const QpSqlRecord *QpCmnSqlTableModel::get_BaseRec() const
{
    return &baseRec;
}

QVariant QpCmnSqlTableModel::format_displayData( const QVariant &var, const QpColumnInfo &inf) const
{
    //    QVariant var = data(idx, Qt::DisplayRole);

    if( inf.precision >0 && var.type() == QVariant::Double )

        return QString::number( var.toDouble(),
                                inf.cFormat,
                                inf.precision );

    return var;

}

QVariant QpCmnSqlTableModel::data(const QModelIndex &idx, int role) const
{
    /*
      тут выравнивание
    */
    int row = idx.row();

    int col = idx.column();

    //qDebug() << "::data "<< idx.column() << idx.row() << " role : " << role;

    const QString &fldName = baseRec.fieldName(col);

    if( role == Qt::TextAlignmentRole )
    {

        if( specialFld.contains( fldName ))

            return Qt::AlignCenter;

    }
    else if( role == Qt::BackgroundColorRole ) // repaint
    {
        // here returns color
        // int r,g,b,a=0;

        if( specialFld.contains( fldName ))
        {
            if( specialFld[ fldName ] != CALC_FLD )

                return  QColor( QApplication::palette().color(QPalette::AlternateBase) );
        }

    }

    if( colInfo.contains( fldName ) )
    {

        QpColumnInfo inf = colInfo[ fldName ];

        if( role == Qt::TextAlignmentRole)
        {
            return colInfo[ fldName ].alignment;
        }
        else if( role == Qt::DisplayRole)
        {
            QVariant var = get_displayData( idx );

            if( inf.precision >0 && var.type() == QVariant::Double )

                return QString::number( var.toDouble(),
                                        inf.cFormat,
                                        inf.precision );
            return var;
        }

        if( calc_columns.contains( fldName ) && role == Qt::DisplayRole)
        {
            QVariant vv = QSqlTableModel::data(idx, role);

            if( vv.type() >= QVariant::Int && vv.type() <= QVariant::Double &&  vv.toDouble() == 0)

                return "";
        }

    }

    if( role == Qt::DisplayRole)
    {
        return get_displayData( idx);
    }

    return QSqlTableModel::data( idx , role );


    //    if( calc_columns.contains( fldName ) && role == Qt::DisplayRole)
    //    {
    //        QVariant vv = QSqlTableModel::data(idx, role);

    //        if( vv.type() >= QVariant::Int && vv.type() <= QVariant::Double &&  vv.toDouble() == 0)

    //            //if( vv.isNull()) // !!!!

    //            return "";
    //    }

    //    return QSqlTableModel::data(idx, role);

}

int QpCmnSqlTableModel::getAccountingOnColumn(int relCol) const
{

    QString fldName = baseRec.fieldName( relCol);

    if( fldName.isEmpty())

        return qp::db::COL_UNDEFINED;


    if(subAccnt.contains( fldName ))
    {
        qDebug() << subAccnt[ fldName ].get_sub_on_fld_name();
        //QP_ASSERT_X (subAccnt[ fldName ].get_sub_on_fld().isEmpty()==true, "456533654", "6786754352");

        int on_sub_col = baseRec.indexOf( subAccnt[ fldName ].get_sub_on_fld_name() );

        Q_ASSERT( on_sub_col>=0 );

        return on_sub_col;

    }
    else
        return qp::db::COL_UNDEFINED;
}



void QpCmnSqlTableModel::setColInf(const QString & colName , const QpColumnInfo & inf)
{
    colInfo[ colName ] = inf;
}

void QpCmnSqlTableModel::setAlignment(const QString & colName , Qt::Alignment align)
{
    colInfo[colName].alignment = align;
}

void QpCmnSqlTableModel::setPrecision(const QString & colName , int precision)
{
    colInfo[colName].precision = precision;

}

void QpCmnSqlTableModel::setEditable(const QString & colName , bool on)
{
    colInfo[colName].editable = on;

}

void QpCmnSqlTableModel::setSelectable(const QString & colName , bool on)
{
    colInfo[colName].selectable = on;

}


void QpCmnSqlTableModel::set_Visible(const QString & colName , bool on)
{
    colInfo[colName].is_visible = on;

}

void QpCmnSqlTableModel::setDblFormat(const QString & colName , char ch)
{
    colInfo[colName].cFormat = ch;

}

bool QpCmnSqlTableModel::setCalcField( QpCalcColumn Calc)
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


    specialFld.insert( Calc.select_as_name , CALC_FLD );


    return true;
}


bool QpCmnSqlTableModel::setRelation( QpSqlRelation &relation )
{

    if( ! baseRec.contains( relation.idField1Name)  )
    {
        qCritical() << tr("QpCmnSqlTableModel::setRelation. Error finding  : %1 ").arg(relation.idField1Name);

        return false;
    }


    //--------------------------------------------
    //          duplicate protect
    //--------------------------------------------

    if( relations2.contains( relation.idField1Name ))
    {

        QMessageBox::warning(0,
                             "error",
                             QString("QpCmnSqlTableModel::setRelation. This is a second trying to add setRelation for column : %1 , table %2")
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
    specialFld.insert( relation.get_ext_fld_name(), RELATION_ID_EXT_FLD ); // !!!!

    //    baseRec.relations.insert( relation.idField1Name , relCol);

    return true;
}

bool QpCmnSqlTableModel::setSubAccount(

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


    specialFld.insert( sub_on_fldName , SUBACCOUNT_ENABLE_FLD ); // !!!!

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

bool QpCmnSqlTableModel::isSubAccounting(const QString &fldName)
{

    if( fldName.isEmpty() )

        return false;


    if ( subAccnt.contains( fldName ))
    {
        return true;
    }

    return false;
}

bool QpCmnSqlTableModel::isSubAccountingOn_forFld(int row, const QString &fldName)
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


bool QpCmnSqlTableModel::isRelationColumn( const QString &  fldName) const
{

    Q_ASSERT_X(fldName.isEmpty()==false,"6727984762565","56823056256");

    return relations2.contains( fldName );
}

bool QpCmnSqlTableModel::isCalcColumn(const QString &colName) const
{

    /*if(col < baseRec.count())
        return false;

    int exCol = col - baseRec.count();

    if( exCol >= ex_columns.count() )
        return false;*/

    if( specialFld.contains( colName ) && specialFld.value( colName ) == CALC_FLD)

        return true;


    return false;
}

int QpCmnSqlTableModel::getRelIdColumn3(const QString & fldName) const
{

    if(! relations2.contains( fldName ))

        return qp::db::COL_UNDEFINED;

    QpSqlRelation ff = relations2.value( fldName );

    const QString relIdFldName = ff.get_ext_fld_name();

    if( relIdFldName.isEmpty() || ! baseRec.contains( relIdFldName ))

        return qp::db::COL_UNDEFINED;



    return baseRec.indexOf( relIdFldName ) ;
}

QString QpCmnSqlTableModel::getRelIdColumn4(const QString & fldName)
{

    if(! relations2.contains( fldName ))

        return QString();

    QString relIdFldName = relations2[ fldName ].get_ext_fld_name();

    if( fldName.isEmpty() || ! baseRec.contains( relIdFldName ))

        return QString();

    return relIdFldName;
}

bool QpCmnSqlTableModel::isSpecialColumn(int col) const
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
    //        qDebug() << "QpCmnSqlTableModel::isSpecialColumn " <<col << baseRec;
    //        return false;
    //    }

    if( baseRec.fieldName( col ).isEmpty() )

        return false;

    if( ! specialFld.contains( baseRec.fieldName( col ) ) )

        return false;


    return true;

}




bool QpCmnSqlTableModel::isRelationExtIdColumn(int col) const
{


    if( getRelIdColumn(  col )  != -1)

        return true;

    return false;
}

QString QpCmnSqlTableModel::sqlite_qoutes_for_value(const QVariant & val)
{

    if(val.type() == QVariant::String)

        return val.toString().prepend("'").append("'");

    else

        return val.toString();
}

int QpCmnSqlTableModel::getRowPriValue(int row) const
{
    if( baseRec.indexOf( priColName ) == qp::db::COL_UNDEFINED)
    {
        QMessageBox::warning(0 ,
                             qp::dbg::error_,
                             QObject::tr("pri column is not exists in the table!"));

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
                             QObject::tr("pri column value don't convert to int !"));
        return qp::db::INT_UNDEFINED;
    }


    return iPri;
}


void QpCmnSqlTableModel::setTable(const QString &tableName)
{
    QSqlTableModel::setTable( tableName );

    baseRec = record( );
    baseRec.setRefToModel( this );

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

bool QpCmnSqlTableModel::hasUniqueFields( )
{
    // --------------------------------------
    // test for unique columns
    // --------------------------------------

    QString str = QString("PRAGMA index_list('%1');")
            .arg( tableName());

    QSqlQuery qq( database() );

    if( qq.exec(str))
    {
        while( qq.next())
        {

            QSqlRecord  rec = qq.record();

            if(rec.value("unique") == "1")
            {
                return true;
            }

        }
    }
    return false;

}
bool QpCmnSqlTableModel::removePrimaryKeys_fromRec(QSqlRecord &rec, MODE mode)
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


int QpCmnSqlTableModel::indexOf(const QString &fieldName) const
{
    return baseRec.indexOf( fieldName );
}


QpSqlRecord QpCmnSqlTableModel::getPblSqlRecord( const QSqlRecord & rec)
{

    QpSqlRecord pblRec = baseRec  ; // copy ctor

    pblRec = rec ;

    //    pblRec.specialFld = baseRec.specialFld;

    //    qDebug()<<" getPblSqlRecordrec : "  << rec;

    return pblRec;
}

Qt::ItemFlags QpCmnSqlTableModel::flags(const QModelIndex &index) const
{

    int col = index.column();
    int row = index.row();


    Qt::ItemFlags flgs = QSqlTableModel::flags(index);

    const QString &fldName = baseRec.fieldName( col );

    if ( specialFld.contains( fldName ) )
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

bool QpCmnSqlTableModel::insertRowIntoTable(const QSqlRecord &values)
{
    QSqlRecord rec = values;

    qDebug() << "\n\n\nQpCmnSqlTableModel::insertRowIntoTable values " << values << "\n\n";

    // it occures when insetRow: insertRow and copyRow too!

    /*
        Внимание здесь спец поля присутствуют [goods_productName_id,goods_sub_on,sub_accounting_sub_id]
        (смотрите как запросе select)

         " 0:" QSqlField("id", int, generated: no, typeID: 1) "0"
         " 1:" QSqlField("productName", QString, generated: yes, typeID: 3) "apple"
         " 2:" QSqlField("goods_productName_id", int, generated: yes, typeID: 1) "2"
         " 3:" QSqlField("goods_sub_on", int, generated: yes, typeID: 1) "1"
         " 4:" QSqlField("sub", QString, generated: yes, typeID: 3) "L"
         " 5:" QSqlField("sub_accounting_sub_id", int, generated: yes, typeID: 1) "5"
         " 6:" QSqlField("price", double, generated: yes, typeID: 2) "234.56"
         " 7:" QSqlField("qty", double, generated: yes, typeID: 2) "1"
         " 8:" QSqlField("sum", double, generated: yes, typeID: 2) "234.56"
         " 9:" QSqlField("combobox", int, generated: yes, typeID: 1) "-1"
         "10:" QSqlField("chk", int, generated: yes, typeID: 5) "0"
         "11:" QSqlField("foo", int, generated: yes, typeID: 5) "0"
 */

    // --------------------------------------------------------------------------
    //          all special (extened) columns set generated no
    // --------------------------------------------------------------------------

    for( int col=0; col< rec.count(); col++)
    {

        QString fldName = rec.fieldName( col );

        QP_ASSERT( baseRec.contains( fldName ) ) ;

        if ( specialFld.contains( fldName ) )
        {
            SPECIAL_FLD_TYPES tt = specialFld[ fldName ] ;

            if(  tt == SUBACCOUNT_ENABLE_FLD
                 || tt == CALC_FLD
                 )
            {
                // --------------------------------------------------------------
                // тупо помечаем какие служебные поля нам не надо писать в базу
                // --------------------------------------------------------------
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



    qDebug() << "\n\n\nQpCmnSqlTableModel::insertRowIntoTable before " << rec << "\n\n";

    prepareInsertRow(0, rec);

    qDebug() << "\n\n\nQpCmnSqlTableModel::insertRowIntoTable translateFieldNames " << rec<< "\n\n";

    bool res = QSqlTableModel::insertRowIntoTable(rec); // insert all fields (with generated=no too)

    //qDebug() << "\n\n\nQpCmnSqlTableModel::insertRowIntoTable after " << rec<< "\n\n";

    if( res )
    {
        lastDirtyRowId = getLastInsertId();
    }

    return res;
}

bool QpCmnSqlTableModel::prepareInsertRow( int row,
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

int QpCmnSqlTableModel::getLastInsertId()
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

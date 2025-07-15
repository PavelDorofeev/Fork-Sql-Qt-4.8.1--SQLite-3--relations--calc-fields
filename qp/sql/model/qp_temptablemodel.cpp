#include "qp_temptablemodel.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include "qp/sql/model/qp_subaccnt.h"
#include "qp/sql/model/qp_columninfo.h"
#include "qp/sql/model/qp_calc_column.h"

#include "qp/sql/qp_sql.h"

#include "qp/core/dbg/dbg.h"

QpTempSqlTableModel::QpTempSqlTableModel(QSqlDatabase &Db,
                                         cb_setting_mdl pToSettingFunc,
                                         QObject *parent) :
    QpCmnSqlTableModel(Db ,
                       pToSettingFunc,
                       parent )
{

    setEditStrategy( QSqlTableModel::OnManualSubmit ); // !!

}

QpTempSqlTableModel::~QpTempSqlTableModel()
{

}

bool QpTempSqlTableModel::insertRows(int row, int count, const QModelIndex &parent)
{

    if ( row  >  cache.count()  )
        return false;

    int rowCnt = rowCount();
    qDebug() << "QpTempSqlTableModel::insertRows rowCount" << rowCnt;

    for( int ii = 0 ; ii < count; ii++ )
    {
        QpSqlRecord rec = getBaseRec();

        //emit beforeInsert( rec );

        cache.insert( row + 1 + ii, rec );

        qDebug() << "QpTempSqlTableModel::insertRows ii" << ii;

    }

    emit headerDataChanged( Qt::Vertical, row, rowCount()-1); // да этот перерисовывает полностью таблицу

    qDebug() << "QpTempSqlTableModel::insertRows rowCount" << rowCount();


    return true;
}

bool QpTempSqlTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if ( row + count >  cache.count()  )
        return false;
    int rowCnt = rowCount();
    qDebug() << "QpTempSqlTableModel::removeRows rowCount" << rowCnt;

    for( int ii = row + count -1 ; ii >=row; ii-- )
    {
        //        emit beforeDelete( ii );

        cache.removeAt( ii );
        qDebug() << "QpTempSqlTableModel::removeRows ii" << ii;

        emit headerDataChanged( Qt::Vertical, ii, rowCount()-1); // да этот перерисовывает полностью таблицу
    }

    qDebug() << "QpTempSqlTableModel::removeRows rowCount" << rowCount();

    /*
    void beforeInsert(QSqlRecord &record);
    void beforeUpdate(int row, QSqlRecord &record);
    void beforeDelete(int row);

    QAbstractItemModel
    Q_SIGNALS:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void headerDataChanged(Qt::Orientation orientation, int first, int last);
    void layoutChanged();
    void layoutAboutToBeChanged();

#if !defined(Q_MOC_RUN) && !defined(qdoc)
private: // can only be emitted by QAbstractItemModel
#endif
    void rowsAboutToBeInserted(const QModelIndex &parent, int first, int last);
    void rowsInserted(const QModelIndex &parent, int first, int last);

    void rowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void rowsRemoved(const QModelIndex &parent, int first, int last);

    void columnsAboutToBeInserted(const QModelIndex &parent, int first, int last);
    void columnsInserted(const QModelIndex &parent, int first, int last);

    void columnsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void columnsRemoved(const QModelIndex &parent, int first, int last);

    void modelAboutToBeReset();
    void modelReset();

    void rowsAboutToBeMoved( const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destinationParent, int destinationRow );
    void rowsMoved( const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row );

    void columnsAboutToBeMoved( const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destinationParent, int destinationColumn );
    void columnsMoved( const QModelIndex &parent, int start, int end, const QModelIndex &destination, int column );
    */

    //    emit rowsRemoved( parent , row , row + count - 1  );
    //    emit dataChanged( index(row , 0), index( rowCnt -1 , columnCount() -1 ));
    //    emit layoutChanged();
    //    emit layoutAboutToBeChanged();


    return true;
}

bool QpTempSqlTableModel::select( )
{
    // -------------------------------------------------------------
    // надо обязательно очищать предыдущие данные
    // каждый новый select это заново заполнение временной таблицы
    // --------------------------------------------------------------

    cache.clear();



    QString queryStr = selectStatement();

    qDebug() << "query" << queryStr;

    QSqlQuery sql( queryStr , db_);

    if( ! sql.exec(queryStr ) )
    {
        QMessageBox::warning( 0 , "Ошибка",
                              QString("%1").arg(sql.lastError().text())
                              );
        return false;
    }

    //    baseRec = sql.record();
    //    qDebug() << "12321 baseRec" << getBaseRec() ;

    while( sql.next())
    {

        QpSqlRecord rec( this , sql.record() );

        cache.append( rec );

    }


    return true;
}

QModelIndex QpTempSqlTableModel::index(int row, int column, const QModelIndex &parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column, 0) : QModelIndex();

}

bool QpTempSqlTableModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                       int row, int column, const QModelIndex &parent)
{
    return true;
}

bool QpTempSqlTableModel::prepare_mdl( const QString &tableName,
                                       const QList<QString> &fldList,
                                       const QHash<QString,QVariant> &SubCountingFilter)
{


    //    qDebug() <<"dsassa baseRec" << getBaseRec();

    QSqlRecord bsRec = db_.record( tableName );


    tblName = tableName;

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

    if ( tableName.isEmpty())
    {
        QMessageBox::critical( 0 ,
                               qp::dbg::error_,
                               QObject::tr("empty table name '%1'").
                               arg(tableName));

        return false;
    }


    if (! db_.tables().contains(tableName))
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

    setBaseRec( this, bsRec );

    if( callback_setting_mdl_func != 0)
    {
        /*
          Вот тут добавляются спец поля
          */
        //        qDebug() << "QpTempSqlTableModel::prepare_mdl table: " << tableName;

        callback_setting_mdl_func( (QpCmnSqlTableModel*)this  ); //!!!!
    }


    // -------------------------------------------------------------------

    subAccountingFilter = SubCountingFilter;

    qDebug() <<"324213423 baseRec" << getBaseRec();

    return true;

}

bool QpTempSqlTableModel::submit()
{
    return true; // ничего не делаем, т.к. select нам не нужен для данной модели
}

bool QpTempSqlTableModel::setRelation( QpSqlRelation &relation )
{

    if( ! getBaseRec().contains( relation.idField1Name)  )
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
                             .arg(tblName)
                             );

        return false;
    }

    // --------------------------------------------

    int relCol = getBaseRec().indexOf( relation.idField1Name ) ;

    Q_ASSERT ( relCol >= 0 );



    int newRelIdCol = getBaseRec().count() + relations2.count();

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

    bbb = getBaseRec().value( relCol + 1) .isValid();

    //baseRec.specialFld.insert( relation.idField1Name, PblSqlRecord::RELATION_TXT_FLD ); // !!!!
    specialFld.insert( relation.get_ext_fld_name(), RELATION_ID_EXT_FLD ); // !!!!



    return true;
}


QModelIndex QpTempSqlTableModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

//QVariant QpTempSqlTableModel::data(const QModelIndex &idx, int role ) const
//{
//    if( role == Qt::TextAlignmentRole || role == Qt::BackgroundColorRole )
//        return QpCmnSqlTableModel::data( idx , role );


////    int row = idx.row();

////    if( row < 0 || row>= cache.count() )
////        return QVariant();

////    int col = idx.column();

////    if( col <0 || col >= get_BaseRec()->count())
////        return QVariant();

//    if( role != Qt::DisplayRole)
//    {
//        return QpCmnSqlTableModel::data( idx , role );
//    }


//}

QVariant QpTempSqlTableModel::get_displayData( const QModelIndex &idx ) const
{
    int row = idx.row();
    int col = idx.column();

    if( row < 0 || row>= cache.count() )
        return QVariant();

    if( col <0 || col >= get_BaseRec()->count())
        return QVariant();

        QVariant value =  cache.value( row ).value( col );

        return value;

}

bool QpTempSqlTableModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{

    if( ! idx.isValid())
        return false;

    //    if( idx.column() == 4 )
    //    qDebug() << "QpTempSqlTableModel::setData(" << idx.row()<<","<< idx.column()<<") " << value << role << cache[ idx.row()];
    int row = idx.row();

    if( row <0 || row >= cache.count())
        return false;

    int col = idx.column();


    if( col <0 || col >= getBaseRec().count())
        return false;

    cache[ idx.row() ].setValue( idx.column() , value );

    //    qDebug() << "123132:::" << cache[ idx.row()];

    cache[ idx.row() ].setGenerated( idx.column() , true );

    emit dataChanged( idx , idx );

    return true;
}



bool QpTempSqlTableModel::hasChildren(const QModelIndex &parent) const
{
    if (parent.model() == this || !parent.isValid())
        return rowCount(parent) > 0 && columnCount(parent) > 0;

    return false;
}

void QpTempSqlTableModel::setBaseRec( QpCmnSqlTableModel* mdl, const QSqlRecord& rec)
{
    baseRec = rec;
    baseRec.setRefToModel( mdl );
}


bool QpTempSqlTableModel::setSubAccount(

        const QString & parentTblName ,    // parent table name
        const QString & col1Name ,      // parent field name
        const QString & col2Name ,      // child field id name
        const QString & filterColName,  // child filter name
        const QString & sub_on
        )
{


    Q_ASSERT ( getBaseRec().indexOf(col1Name) >=0 );


    int col1 = getBaseRec().indexOf(col1Name);

    if( ! relations2.contains( col1Name))

        return false;

    // ------------------------------------

    QpSubAccnt SubAccnt( parentTblName, col1Name , col2Name , sub_on);

    subAccnt.insert( col1Name , SubAccnt );

    // ----------------------------------------------------------

    rel_bindings.insert(col2Name , &subAccnt[col1Name]);

    //-----------------------------------------------------

    QString sub_on_fldName = subAccnt[col1Name].get_sub_on_fld_name();

    Q_ASSERT(sub_on_fldName.isEmpty()==false);

    QSqlField sqlFld;

    sqlFld.setName( sub_on_fldName );
    sqlFld.setType( QVariant::Int ); // else isValid = false

    baseRec.insert( col1 + 2 , sqlFld ); // !!!!!!!!

    Q_ASSERT ( baseRec.field( col1 + 2 ).isValid() == true) ;


    specialFld.insert( sub_on_fldName , SUBACCOUNT_ENABLE_FLD ); // !!!!

    int col2 = baseRec.indexOf(col2Name);

    Q_ASSERT ( baseRec.indexOf(col2Name) >=0 );

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

void QpTempSqlTableModel::setEditable(const QString & colName , bool on)
{
    colInfo[colName].editable = on;

}

QString QpTempSqlTableModel::selectStatement() const
{
    QString query;

    if (tblName.isEmpty())
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
                name.prepend(QLatin1String(".")).prepend(tblName);

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

                    append(tblName).append(QLatin1String(".")).
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

                append(tblName).append(QLatin1String(".")).
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

    sTablesList.prepend(tblName);
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
        query.append(QLatin1String(" \nGROUP BY ")).append( tblName ).append(QLatin1String(".id"));
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




int QpTempSqlTableModel::getRelIdColumn3(const QString & fldName) const
{

    if(! relations2.contains( fldName ))

        return qp::db::COL_UNDEFINED;

    QpSqlRelation ff = relations2.value( fldName );

    const QString relIdFldName = ff.get_ext_fld_name();

    if( relIdFldName.isEmpty() || ! baseRec.contains( relIdFldName ))

        return qp::db::COL_UNDEFINED;



    return baseRec.indexOf( relIdFldName ) ;
}

QString QpTempSqlTableModel::relationField(const QString &tableName,
                                           const QString &fieldName) const
{
    QString ret;

    ret.reserve(tableName.size() + fieldName.size() + 1);

    ret.append(tableName).append(QLatin1Char('.')).append(fieldName);

    return ret;
}

QString QpTempSqlTableModel::filter() const
{
    return "";
}

QString QpTempSqlTableModel::orderByClause() const
{

    //    if( orderSet.fldName.isEmpty() )

    //        return QSqlTableModel::orderByClause();

    return orderSet.getTxt();
}



QSqlTableModel::EditStrategy QpTempSqlTableModel::editStrategy() const
{
    return QSqlTableModel::OnManualSubmit;
}


int QpTempSqlTableModel::rowCount(const QModelIndex &parent ) const
{
    //    qDebug() << "QpTempSqlTableModel::rowCount"<<cache.count();
    return cache.count();
}

int QpTempSqlTableModel::columnCount(const QModelIndex &parent ) const
{
    return baseRec.count();
}

QVariant QpTempSqlTableModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( role == Qt::DisplayRole )
    {
        if( orientation == Qt::Horizontal)
        {
            //            qDebug() << "QpTempSqlTableModel::headerData" << section<<"orientation"<<orientation<< "role" << role;

            if( ! headerText.contains( section ) )
                return get_BaseRec()->fieldName( section );

            else
                return headerText.value( section );
        }
    }
    else if ( role == Qt::TextAlignmentRole )
    {
        return Qt::AlignCenter;
    }

    return QSqlTableModel::headerData( section, orientation, role );
}

bool QpTempSqlTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role )
{

    if( orientation ==Qt::Horizontal && role == Qt::EditRole )
    {
        if( ! headerText.contains( section ) )
            headerText.insert( section , value.toString());

        else if ( headerText.value( section ) != value.toString() )
            headerText.insert( section , value.toString());
    }

    return true;
}

void QpTempSqlTableModel::setEditStrategy( EditStrategy strategy )
{
    // тут всегда OnManualSubmit, точнее неважно что, все поведение реализуем сами

    QSqlTableModel::setEditStrategy( QSqlTableModel::OnManualSubmit );
}


bool QpTempSqlTableModel::submitAll()
{
    /*
        Сохраняем временную таблицу в базу данных

    */

    qDebug()<< "filter()"<< filter();

    QString where;
    if( ! filter().isEmpty() )
        where.append(" WHERE "+filter());

    // -------------------------------------------------------------------------
    //      Сначала удаляем все строки в базе данных (на текущем фильтре)
    // -------------------------------------------------------------------------

    QString qq = "DELETE FROM purchases" +where ;

    QSqlQuery sql(qq );

    if( ! sql.exec() )
    {
        qDebug()<< sql.lastQuery() << sql.lastError().text();
        return false;
    }

    // -------------------------------------------------------------------------
    //      Далее добавляем заново (на текущем фильтре)
    //      стандартным QSqlTableModel методом insertRowIntoTable
    //          стараемся максимально сохранить совместимость !
    // -------------------------------------------------------------------------
    QString str;
    str.reserve( 1000 );

    for( int row=0; row < rowCount(); row++)
    {
        if( ! insertRowIntoTable( cache.at( row )) )
        {
            return false;
        }

    }

    return true;

    //    return QSqlTableModel::submitAll();

}


QpSqlRecord QpTempSqlTableModel::qp_record(int row) const
{
    if( row < 0 || row >= cache.count())
        return QpSqlRecord();

    return cache.at( row );
}

bool QpTempSqlTableModel::qp_setRecord( int row, const QpSqlRecord &record)
{
    if( row < 0 || row >= cache.count())
        return false;

    cache.replace( row , record);

    return true;
}

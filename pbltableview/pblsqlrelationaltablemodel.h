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

#ifndef PBLSQLRELATIONALTABLEMODEL_H
#define PBLSQLRELATIONALTABLEMODEL_H

#include <QSqlTableModel>
#include <QSqlRecord>

//#include "pblrelcolumn.h"
#include "pbltableview/pblcalc_column.h"
#include "pblsqlrelation.h"
#include "pblsqlrecord.h"
#include "pblfield.h"
#include "pblsubaccnt.h"
#include "pblcolumninfo.h"

#include <QList>
#include <QSqlIndex>

#include <QHash>
#include <QDebug>

typedef bool (*cb_setting_mdl) (PblSqlRelationalTableModel *);

class Order_Settings
{
public:

    Order_Settings();

    QString fldName;
    Qt::SortOrder order;

    static const QString asc;// = " ASC";
    static const QString desc;// = " DESC";
    static const QString ord;// = " DESC";

    QString resTxt;

    QString getTxt();

};



class PblSqlRelationalTableModel: public QSqlTableModel
{
    Q_OBJECT
public:

    enum FILTER_TYPE
    {
        FILTER_TYPE_UNKNOWN=-1,
        FILTER_TYPE_SEARCH_TEXT_BY_COLUMN = 1,
        FILTER_TYPE_SEARCH_BY_FIELD_VALUE,
    };

    enum MODE{
        UPDATE=1,
        INSERT
    };
    
public:
    
    explicit PblSqlRelationalTableModel(QSqlDatabase &db_ ,
                                        cb_setting_mdl pMdl =0,
                                        QObject *parent = 0,
                                        const QList<QString> &FieldSet = QList<QString>()

            );
    
    virtual ~PblSqlRelationalTableModel();
    


    struct Filter{

        int col;
        FILTER_TYPE type;
        bool enabled;

        Filter():
            col(-1),
            type(FILTER_TYPE_UNKNOWN),
            enabled(false)
        {

        }
    };

public:

    static const QLatin1String prefix;

    QSqlDatabase &db_;

    cb_setting_mdl callback_setting_mdl_func;

    void set_editable( bool Editable);

    QString relationField(const QString &tableName, const QString &fieldName) const;

    virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

    bool canFetchMore(const QModelIndex &parent) const;

    bool change_fld_list(const QList<QString> &lst);

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) ;


    QString sqlite_qoutes_for_value(const QVariant & vv);

    PblSqlRecord baseRec; // first time the original table record is without extended fields (relations id, calc functions,..)

    // --------------------------------------------------------------------------------------
    //  here is all required containers for relations, calculations, subaccounting
    //
    //  Important ! contaners keys will be QString while look by field name (not col number)
    //  field name more universal calls (column positions may be changes )
    // --------------------------------------------------------------------------------------

    QHash< QString , PblCalcColumn> calc_columns;    // calculate columns  [ ]

    QHash< int , QVariant> defaultVls;              // defalt values for insert row

    QHash<QString , PblSqlRelation > relations2;     // here relational fields description


    QHash< QString , PblSubAccnt > subAccnt;        // here sub accounting connections

    QHash< QString , PblSubAccnt * > rel_bindings;  // here is an info only for sub fields

    QHash< QString , PblColumnInfo> colInfo;    // additional columns info for visual repainting,  aligning, precision

    QHash< QString , QVariant > subAccountingFilter; // if we open the sub accounting table we have to filter its rows

    QHash<QString,QString> having; // filter for aggregate functions

    // -------------------------------------------------------------------------------

    bool isSubAccounting( const QString &fldName );

    bool isSubAccountingOn_forFld(int row, const QString &fldName);


    QSqlIndex primaryIndex;

    QString priColName;

    int getPriColumn() const;

    int findRowById(int id);

    int isDirtyRow;

    int isInsertRow;

    uint lastDirtyRowId;

    uint isSelectedLine;

    uint lastDirtyCol;

    int getRowPriValue(int row) const;

    QVariant getRecordPriValue(const QSqlRecord &rec) const;

    bool translateFieldNames(int row, QSqlRecord &values, PblSqlRelationalTableModel::MODE isRowMode ) const;
    

    virtual QString selectStatement() const;
    
    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;

    virtual bool setData(const QModelIndex &item, const QVariant &value, int role = Qt::EditRole);

    bool setRecord_withoutPriCol(int row, QSqlRecord &record, MODE mode);

    bool removePrimaryKeys_fromRec(QSqlRecord &rec, MODE mode);

    virtual Qt::ItemFlags flags(const QModelIndex &idx) const;

    bool editable;

    virtual bool submit();

    bool setRelation(PblSqlRelation &relation);

    bool setSubAccount(
            const QString & ExtTblName ,
            const QString & col1 ,
            const QString & col2 ,
            const QString & filterColName,
            const QString & sub_on
            );


    bool setCalcField( PblCalcColumn calc);

    virtual bool select();

    virtual  void clear();

    bool isCopyRowMode(int extCol , const QSqlRecord &rec) const;

    mutable Order_Settings orderSet;


    virtual void setSort(int column, Qt::SortOrder order);


    virtual bool prepare_mdl( const QString &tableName,
                              const QList<QString> &fldList = QList<QString>(),
                              const QHash<QString,QVariant> &filter=QHash<QString,QVariant>());


    void setColInf(const QString & colName , const PblColumnInfo & inf);
    void setAlignment(const QString & colName , Qt::Alignment align);
    void setPrecision(const QString & colName , int precision);
    void setDblFormat(const QString & colName , char ch);
    void setEditable(const QString & colName , bool on);
    void setSelectable(const QString & colName , bool on);
    void set_Visible(const QString & colName , bool on);

    const QSqlRecord & baseRecord();

    PblSqlRelation  getRelationInfoForColumn(const QString &fldName);

    bool isCalcColumn(const QString &) const;

    bool isRelationColumn( const QString &  fldName ) const;

    bool isRelationExtIdColumn(int col) const;


    int getRelIdColumn(int col) const; // for calls from with QModelIndex parameters

    bool isSpecialColumn(int col) const;


    int getRelIdColumn3(const QString & fldName) const;

    QString getRelIdColumn4(const QString & fldName);

    int getAccountingOnColumn(int relCol) const;

    bool isRelationalColumn(int col);

    Filter filterDone;

    int getLastInsertId();

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    PblSqlRecord getPblSqlRecord(  const QSqlRecord & rec);

    int isDefaultSearchingColumn;


signals:

    void sig_editStrategyChanged(QSqlTableModel::EditStrategy);

    void sig_rowIsDirty(int row);

    void sig_afterSelect( bool);

    void sig_select_exec();

public Q_SLOTS:

    void setEditStrategy(EditStrategy strategy);

    void slot_primeInsert(int row, QSqlRecord &rec);

protected:

    bool updateRowInTable(int row, const QSqlRecord &values);

    bool insertRowIntoTable(const QSqlRecord &values);


    QString orderByClause() const;

private:

    int origTblColumnCount;

    void setTable(const QString &tableName); // now you have to use a prepare_mdl method ! Its incapsulates setTable.

    int fieldIndex(const QString &fieldName) const; // // don't use anymore


    void clearDirtyRow();
    void setDirtyRow(int dirtyRow, int dirtyCol);
};


#endif // PBLSQLRELATIONALTABLEMODEL_H

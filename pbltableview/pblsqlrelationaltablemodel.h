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

#include "pblrelcolumn.h"
#include "pblcalc_column.h"
#include "pblsqlrelation.h"
#include "pblsqlrecord.h"

#include <QList>
#include <QSqlIndex>

#include <QHash>

typedef struct COLUMN_INFO
{
    COLUMN_INFO():
        alignment(Qt::AlignCenter),
        precision(0),
        cFormat(' '),
        editable(true)
    {

    }

    Qt::Alignment alignment;
    int precision;
    char cFormat;
    bool editable;
    //PblRelColumn::COLUMN_TYPE type;
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

    enum SOME_FIELDS_VALUES
    {
        FLD_UNDEFINED = -1,
    };

    enum MODE{
        UPDATE=1,
        INSERT
    };
    
public:
    
    PblSqlRelationalTableModel(); //??

    explicit PblSqlRelationalTableModel(QSqlDatabase &db ,
                                        QObject *parent = 0

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

    QSqlDatabase db;

    QString relationField(const QString &tableName, const QString &fieldName) const;

    bool canFetchMore(const QModelIndex &parent) const;

    QHash<int , PblCalcColumn> calc_columns;    // calc columns  [ ]

    QHash<int , int > relations;     //

    QHash<int , int > addSubAcntOnFlds;     // sub accounting enable fields [1,2 ++]

    QHash<int , PblSqlRelation> rel_clmn;    // extended columns info [0,1,2..]

    QHash<int , const PblSqlRelation * > rel_bindings;           //

    QHash<int , const PblSqlRelation * > rel_subAccounting;           //

    bool isSubAccounting(int col);

    bool isSubAccountingOn_forFld(int row, int col);

    bool isParentBinding(int col);


    QHash<int, COLUMN_INFO> colInfo;    // extended columns info

    QSqlIndex primaryIndex;

    int priCol;

    int getPriColumn() const;

    int findRowById(int id);

    int isDirtyRow;

    int isInsertRow;

    uint lastDirtyRowId;

    uint isSelectedLine;

    uint lastDirtyCol;

    int getRowPriValue(int row) const;

    QVariant getRecordPriValue(const QSqlRecord &rec) const;

    bool addSubAcntOnField ( PblSqlRelation &rel, int col , int col2 , const QString &name);


    QHash<int , QVariant> defaultVls;

    QSqlRecord baseRec; // the original table record without extended fields (relations id, calc functions,..)

    bool translateFieldNames(int row, QSqlRecord &values, PblSqlRelationalTableModel::MODE isRowMode ) const;

    
    virtual QString selectStatement() const;
    
    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;

    virtual bool setData(const QModelIndex &item, const QVariant &value, int role = Qt::EditRole);

    /*bool setDataForRelationField(const QModelIndex &idx,
                                 const QVariant &value,
                                 int role);*/

    bool setRecord_withoutPriCol(int row, QSqlRecord &record, MODE mode);

    bool prepareRecord(QSqlRecord &rec, MODE mode);

    virtual Qt::ItemFlags flags(const QModelIndex &idx) const;

    virtual bool submit();

    bool setRelation(const PblSqlRelation &relation);

    bool setBinding(int col1 , int col2 , QString subAcntOnFld = "");

    bool setCalcField(CALC_COLUMN & calcLst);
    
    virtual bool select();

    virtual  void clear();

    PblSqlRelationalTableModel::MODE isRowMode(int row) const;
    PblSqlRelationalTableModel::MODE isRecordMode(const QSqlRecord &rec) const;
    bool isCopyRowMode(int extCol , const QSqlRecord &rec) const;


    int sortColumn;
    Qt::SortOrder sortOrder;

    virtual void setSort(int column, Qt::SortOrder order);
    
    
    virtual bool prepare(const QString &tableName,
                         const QHash<QString,QVariant> &filter=QHash<QString,QVariant>());


    void setAlignment(int col , Qt::Alignment align);
    void setPrecision(int col , int precision);
    void setDblFormat(int col , char ch);
    void setEditable(int col , bool on);
    
    const QSqlRecord & baseRecord();

    //PblColumn::COLUMN_TYPE exColType(int exCol);

    PblSqlRelation  getRelationInfoForColumn(int col);

    bool isCalcColumn(int col) const;

    bool isRelationColumn(int col) const;

    bool isRelationExtIdColumn(int col) const;

    int getOrigRelationColumn(int extCol) const;

    int getRelIdColumn(int relCol) const;

    int getRelIdAcntOnColumn(int relCol) const;

    bool isRelationalColumn(int col);


    QString getsubAccountingFilter();

    Filter filterDone;

    int getLastInsertId();

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    PblSqlRecord getPblSqlRecord(const QSqlRecord & rec);

    QHash<QString,QVariant> subAccountingFilter;

    int isDefaultSearchingColumn;

    bool setSubAccountingFields( QSqlRecord &rec);

signals:

    void sig_editStrategyChanged(QSqlTableModel::EditStrategy);

    void sig_rowIsDirty(int row);

    void sig_afterSelect( bool);

public Q_SLOTS:

    void setEditStrategy(EditStrategy strategy);


    void slot_primeInsert(int row, QSqlRecord &rec);
    
protected:
    
    bool updateRowInTable(int row, const QSqlRecord &values);
    
    bool insertRowIntoTable(const QSqlRecord &values);


    QString orderByClause() const;
    
private:

    void clearDirtyRow();
    void setDirtyRow(int dirtyRow, int dirtyCol);
};


#endif // PBLSQLRELATIONALTABLEMODEL_H

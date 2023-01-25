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

#include "pblsqlrelation.h"
#include "pblcolumn.h"

#include <QList>
#include <QSqlIndex>

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
    PblColumn::COLUMN_TYPE type;
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

    QSqlDatabase db;

    QString relationField(const QString &tableName, const QString &fieldName) const;


    //void fetchMore(const QModelIndex &parent);
    bool canFetchMore(const QModelIndex &parent) const;

    QHash<int , int> relations;     // connecting relation text and id fields

    QList<PblColumn> ex_columns;    // extended columns info

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

    QSqlRecord baseRec; // the original table record without extended fields (relations id, calc functions,..)

    void translateFieldNames(int row, QSqlRecord &values, PblSqlRelationalTableModel::MODE rowMode ) const;

    
    virtual QString selectStatement() const;
    
    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;

    virtual bool setData(const QModelIndex &item, const QVariant &value, int role = Qt::EditRole);

    bool setDataForRelationField(const QModelIndex &idx,
                                 const QVariant &value,
                                 int role);


    virtual Qt::ItemFlags flags(const QModelIndex &idx) const;

    virtual bool submit();

    bool setRelation(const PblSqlRelation &relation);

    bool setCalcField(CALC_COLUMN & calcLst);
    
    virtual bool select();

    virtual  void clear();

    PblSqlRelationalTableModel::MODE rowMode(int row) const;


    int sortColumn;
    Qt::SortOrder sortOrder;

    virtual void setSort(int column, Qt::SortOrder order);
    
    
    bool set_Table(const QString &tableName);


    void setAlignment(int col , Qt::Alignment align);
    void setPrecision(int col , int precision);
    void setDblFormat(int col , char ch);
    void setEditable(int col , bool on);
    
    const QSqlRecord & baseRecord();

    PblColumn::COLUMN_TYPE exColType(int exCol);

    PblColumn  getRelationInfoForColumn(int col);

    bool isCalcColumn(int col) const;
    bool isRelationColumn(int col) const;

    int getRelIdColumn(int relCol) const;
    bool isRelationalColumn(int col);


    PblColumn::COLUMN_TYPE columnType(int col);

    Filter filterDone;

    int getLastInsertId();


signals:

    void sig_editStrategyChanged(QSqlTableModel::EditStrategy);

    void sig_rowIsDirty(int row);

    void sig_showSubmit(bool);

public Q_SLOTS:

    virtual void setEditStrategy(EditStrategy strategy);


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

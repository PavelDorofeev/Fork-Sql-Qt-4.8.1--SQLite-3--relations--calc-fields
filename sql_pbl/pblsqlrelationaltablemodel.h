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

#include <QtSql/qsqltablemodel.h>
#include <QtSql/qsqlrecord.h>
#include "pblsqlrelation.h"
#include "pblcolumn.h"

#include <QList>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Sql)


class PblSqlRelationalTableModelPrivate;
class PblSqlRelationalTableModel;

typedef struct CALC_COLUMN
{
    CALC_COLUMN():
        table(QString()),
        idField(QString()),
        summaryField(QString()),
        calcFunc(QString()),
        calcFuncName_As(QString())
    {

    }

    QString     summaryField;
    QString     table;
    QString     idField;
    QString     calcFunc;
    QString     calcFuncName_As;
};

typedef struct COLUMN_INFO
{
    COLUMN_INFO():
        alignment(Qt::AlignCenter),
        precision(0),
        cFormat(' ')
    {

    }

    Qt::Alignment alignment;
    int precision;
    char cFormat;
};

class PblSqlRelationalTableModel: public QSqlTableModel
{
    Q_OBJECT

    enum FILTER_TYPE
    {
        FILTER_TYPE_UNKNOWN=-1,
        FILTER_TYPE_SEARCH_TEXT_BY_COLUMN = 1,
        FILTER_TYPE_SEARCH_BY_FIELD_VALUE,
    };
    
public:
    
    explicit PblSqlRelationalTableModel(QObject *parent = 0,
                                        QSqlDatabase db = QSqlDatabase()
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

    QHash<int , int> relations;     // connecting relation text and id fields

    QList<PblColumn> ex_columns;    // extended columns info

    QHash<int, COLUMN_INFO> colInfo;    // extended columns info

    QSqlRecord baseRec; // the original table record without extended fields (relations id, calc functions,..)

    void translateFieldNames(int row, QSqlRecord &values, QSqlTableModel::EditStrategy editStrategy) const;

    
    virtual QString selectStatement() const;
    
    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;

    virtual bool setData(const QModelIndex &item, const QVariant &value, int role = Qt::EditRole);

    virtual Qt::ItemFlags flags(const QModelIndex &idx) const;

    bool setRelation(int column, const PblSqlRelation &relation);

    bool setCalcField(CALC_COLUMN & calcLst);/*const QString &tableFrom,
                      const QString foreignKeyField,
                      const QString &fieldFrom,
                      const QString &funcName,
                      const QString fieldNameTo=QString());*/
    
    bool select();


    int sortColumn;
    Qt::SortOrder sortOrder;

    virtual void setSort(int column, Qt::SortOrder order);
    
    
    bool set_Table(const QString &tableName);


    bool setDoubleFormat(int col,
                         const char &format,
                         const int &precision);
    
    void setAlignment(int col , Qt::Alignment align);
    void setPrecision(int col , int precision);
    void setDblFormat(int col , char ch);
    
    const QSqlRecord & baseRecord();

    PblColumn::COLUMN_TYPE exColType(int exCol);

    PblColumn  getRelationInfoForColumn(int col);

    int getRelIdColumn(int relCol);

    bool setDataForRelationField(const QModelIndex &idx,
                                 const QVariant &value,
                                 int role);

    PblColumn::COLUMN_TYPE columnType(int col);

    Filter filterDone;

    int isInsertingRow;
    
public Q_SLOTS:
    virtual void setEditStrategy(EditStrategy strategy);
    
protected:
    
    bool updateRowInTable(int row, const QSqlRecord &values);
    
    bool insertRowIntoTable(const QSqlRecord &values);

    QString orderByClause() const;
    
private:


};

QT_END_NAMESPACE

QT_END_HEADER

#endif // PBLSQLRELATIONALTABLEMODEL_H

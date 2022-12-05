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

#ifndef PBLSQLRELATIONALTABLEMODEL_H
#define PBLSQLRELATIONALTABLEMODEL_H

#include <QtSql/qsqltablemodel.h>
#include <QtSql/qsqlrecord.h>
#include "pblsqlrelation.h"
#include "pblsqlrecord.h"

#include <QList>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Sql)


class PblSqlRelationalTableModelPrivate;

class PblSqlRelationalTableModel;
//class PblRelatedTableModel;
//class PblSqlRecord;


struct Q_SQL_EXPORT PblColumn
{
    
public:
    enum COLUMN_TYPE
    {
        COLUMN_TYPE_UNKNOUWN=-1,
        COLUMN_TYPE_RELATION_TEXT = 1,
        COLUMN_TYPE_RELATION_ID = 2,
        COLUMN_TYPE_CALCULATION = 3
    };
    
    PblColumn()
    {
        //qDebug() << "ctor ExColumns";
    }

    PblColumn(
            COLUMN_TYPE type,
            const QString &exTableName,
            const QString &indexFieldFrom,
            const QString &fieldFrom,
            const QString &funcName,
            int origCol,
            int exCol,
            const QString fieldNameTo=QString());
    
    //PblRelatedTableModel *model;
    int origCol;
    int exCol;
    COLUMN_TYPE type;
    QString exTableName;
    QString exIndexFieldName;
    QString exTextFieldName; //
    QString exFuncName;
    QString renamedField_As;
    
    char cFormat;
    int precision;

    bool isValid();
    
    void setFormat(const char &format, const int &precision_)
    {
        cFormat = format;
        precision = precision_;
    }
    
    void setAlignment(Qt::Alignment align = Qt::AlignLeft)
    {
        alignment = align;
    }
    Qt::Alignment alignment;
    
private:

    
};


typedef struct CALC_COLUMN
{
    CALC_COLUMN():
        table(QString()),
        idField2(QString()),
        idField1(QString()),
        calcFuncName(QString()),
        calcFuncName_As(QString())
    {

    }

    QString     idField1;
    QString     table;
    QString     idField2;
    QString     calcFuncName;
    QString     calcFuncName_As;
};


class Q_SQL_EXPORT PblSqlRelationalTableModel: public QSqlTableModel
{
    Q_OBJECT
    
    Q_DECLARE_PRIVATE(PblSqlRelationalTableModel)
    //Q_DECLARE_PRIVATE(QSqlTableModel)
    
public:
    
    explicit PblSqlRelationalTableModel(QObject *parent = 0,
                                        QSqlDatabase db = QSqlDatabase());
    
    virtual ~PblSqlRelationalTableModel();
    
    
    virtual QString selectStatement() const;
    
    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const; // !! add virtual

    virtual bool setData(const QModelIndex &item, const QVariant &value, int role = Qt::EditRole); // !! add virtual
    //bool setData(const QModelIndex &index, const QVariant &value, int role)

    virtual Qt::ItemFlags flags(const QModelIndex &idx) const;
    
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    
    bool setRelation(int column, const PblSqlRelation &relation);

    bool setCalcField(CALC_COLUMN & calcLst);/*const QString &tableFrom,
                      const QString foreignKeyField,
                      const QString &fieldFrom,
                      const QString &funcName,
                      const QString fieldNameTo=QString());*/
    
    bool select();
    
    PblSqlRecord record(int row) const;

    PblSqlRecord record();
    
    void setTable(const QString &tableName);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    
    bool setDoubleFormat(int col,
                         const char &format,
                         const int &precision);
    
    void setAlignment(int exCol , Qt::Alignment align);
    
    const QSqlRecord & baseRecord();

    PblColumn::COLUMN_TYPE exColType(int exCol);

    PblColumn  getRelationInfoForColumn(int col);

    QSqlRecord  getEditBuffer();

    int exColCount();

    QString exStr(int exCol);

    QString  exColName(int exCol);
    
    //int getRelIdColumn(int relCol);

    int getRelIdColumn(int relCol);

    bool setDataForRelation(const QModelIndex &idx,
                                             const QVariant &value,
                                             int role);

    void printQRec(const QSqlRecord &rec, const QString txt=QString());
    bool is_insertIndex(); // режим вставки новой строки

    PblColumn::COLUMN_TYPE columnType(int col);
    
public Q_SLOTS:
    //void revertRow(int row);
    
protected:
    
    //!! ------------- protected -----------------------
    PblSqlRelationalTableModel(PblSqlRelationalTableModelPrivate &dd,
                               QObject *parent = 0,
                               QSqlDatabase db = QSqlDatabase());
    //------------------------------------------------------------
    
    bool updateRowInTable(int row, const QSqlRecord &values);
    
    bool insertRowIntoTable(const QSqlRecord &values);

    QString orderByClause() const;
    
private:
    bool createRelColumnMap(PblSqlRecord& pblRec);
    bool setDataOnlyIntoEditBuffer(const QModelIndex &idx, const QVariant &value, int role);
    
    //Q_DECLARE_PRIVATE(PblSqlRelationalTableModel)
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // PBLSQLRELATIONALTABLEMODEL_H

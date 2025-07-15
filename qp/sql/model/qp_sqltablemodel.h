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

#ifndef QP_SQLTABLEMODEL_H
#define QP_SQLTABLEMODEL_H

#include <QSqlTableModel>
#include <QSqlRecord>

class QpSqlOrderString;

#include "qp_abstracttablemodel.h"
#include "qp_cmnsqltablemodel.h"

#include "qp/sql/dll_qp_sql_global.h"

class LIB_PREFIX_QP_SQL QpSqlTableModel : public QpCmnSqlTableModel
/*
          Почему наследование от двух классов
          Потому, что уже есть две ветки развития

*/
{
    Q_OBJECT
public:

    enum FILTER_TYPE
    {
        FILTER_TYPE_UNKNOWN=-1,
        FILTER_TYPE_SEARCH_TEXT_BY_COLUMN = 1,
        FILTER_TYPE_SEARCH_BY_FIELD_VALUE
    };


public:
    
    explicit QpSqlTableModel( QSqlDatabase &Db ,
                              cb_setting_mdl pMdl =0,
                              QObject *parent = 0,
                              const QList<QString> &FieldSet = QList<QString>()

            );
    
    virtual ~QpSqlTableModel();


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


    QString relationField(const QString &tableName, const QString &fieldName) const;

    virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

    bool canFetchMore(const QModelIndex &parent) const;

    bool change_fld_list(const QList<QString> &lst);

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) ;

    bool set_newInsertedRowParameters( QpSqlTableModel * mdl, QSqlRecord & rec);



    // ------------------------------------------------

    void setBaseRec( QpCmnSqlTableModel*mdl , const QSqlRecord& rec);

    // ------------------------------------------------
    // --------------------------------------------------------------------------------------
    //  here is all required containers for relations, calculations, subaccounting
    //
    //  Important ! contaners keys will be QString while look by field name (not col number)
    //  field name more universal calls (column positions may be changes )
    // --------------------------------------------------------------------------------------

    // ---------------------------------------------------------------------
    // методы дублированные для обоих веток развития
    // ---------------------------------------------------------------------


    // ---------------------------------------------------------------------
    // методы дублированные для обоих веток развития
    // ---------------------------------------------------------------------





    QVariant getRecordPriValue(const QSqlRecord &rec) const;

    bool translateFieldNames(int row, QSqlRecord &values, QpSqlTableModel::MODE mode ) const;
    

    virtual QString selectStatement() const;
    
//    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;

    virtual bool setData(const QModelIndex &item, const QVariant &value, int role = Qt::EditRole);

    bool setRecord_withoutPriCol(int row, QSqlRecord &record, MODE mode);


    virtual bool submit();


    virtual bool select();

    virtual  void clear();

    bool isCopyRowMode(int extCol , const QSqlRecord &rec) const;

    mutable QpSqlOrderString orderSet;


    virtual void setSort(int column, Qt::SortOrder order);


    virtual bool prepare_mdl( const QString &tableName,
                              const QList<QString> &fldList = QList<QString>(),
                              const QHash<QString,QVariant> &filter=QHash<QString,QVariant>());







    Filter filterDone;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    virtual QpSqlRecord qp_record(int row) const ;

    virtual bool qp_setRecord(int row, const QpSqlRecord &record);

signals:


public Q_SLOTS:

    void setEditStrategy( QSqlTableModel::EditStrategy strategy);

    void slot_primeInsert(int row, QSqlRecord &rec);

protected:

    bool updateRowInTable(int row, const QSqlRecord &values);

    QVariant get_displayData( const QModelIndex &idx ) const;

    QString orderByClause() const;

private:


    int fieldIndex(const QString &fieldName) const; // don't call anymore from inherited classes


    //bool insertRecord(int row, const QSqlRecord &record); // don't call anymore from inherited classes

    void clearDirtyRow();
    void setDirtyRow(int dirtyRow, int dirtyCol);
};


#endif // QP_SQLTABLEMODEL_H

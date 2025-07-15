#ifndef QP_TEMP_TABLEMODEL_H
#define QP_TEMP_TABLEMODEL_H

#include <QAbstractTableModel>
#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlTableModel>

#include "qp/sql/model/qp_sqlrecord.h"
#include "qp/sql/model/qp_sqlrelation.h"

class QpSubAccnt;
class QpColumnInfo;
class QpCalcColumn;
#include "qp/sql/model/qp_sql_orderstring.h"
#include "qp/sql/model/qp_cmnsqltablemodel.h"


#include "qp/sql/dll_qp_sql_global.h"


class LIB_PREFIX_QP_SQL QpTempSqlTableModel : public QpCmnSqlTableModel
{
    Q_OBJECT
public:


    explicit QpTempSqlTableModel( QSqlDatabase &Db,
                               cb_setting_mdl pToSettingFunc=0,
                               QObject *parent = 0);

    /*
      эта модель данных предназначена для создания временных таблиц
      впоследствие для добавления пакета строк в другую таблицу
    */


    virtual ~QpTempSqlTableModel();


    // ------------------------------------------------------------------------------------------

    virtual void setBaseRec( QpCmnSqlTableModel* mdl, const QSqlRecord& );

    // ------------------------------------------------------------------------------------------


    bool setSubAccount( const QString & parentTblName ,    // parent table name
                        const QString & col1Name ,      // parent field name
                        const QString & col2Name ,      // child field id name
                        const QString & filterColName,  // child filter name
                        const QString & sub_on
                        );

    bool setRelation( QpSqlRelation &relation );

    void setEditable(const QString & colName , bool on);

    QString selectStatement() const;

    int getRelIdColumn3(const QString & fldName) const;

    QString relationField(const QString &tableName, const QString &fieldName) const;

    QString filter() const; // эмуляция от родителя

    // ------------------------------------------------------------------------------------------

    QSqlTableModel::EditStrategy editStrategy() const;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    bool insertRows(int row, int count, const QModelIndex &parent= QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent= QModelIndex());

    bool select( );

    bool prepare_mdl( const QString &tableName,
                      const QList<QString> &fldList,
                      const QHash<QString,QVariant> &SubCountingFilter);

    // ---------------------------------------------------------------------------------
    // переопределяем виртуальные методы
    // ---------------------------------------------------------------------------------

    QModelIndex parent(const QModelIndex &child) const;

    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);

    virtual bool hasChildren(const QModelIndex &parent = QModelIndex()) const;

//    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const ;

    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
                               int role = Qt::EditRole);

    virtual void setEditStrategy(EditStrategy strategy);

    virtual bool setData(const QModelIndex &idx, const QVariant &value, int role = Qt::EditRole);

    //-------------------------------------------------------------------------------

    QHash<int,QString> headerText;
    // ------------------------------------------------------------------------------

    virtual QpSqlRecord qp_record(int row) const;

    virtual bool qp_setRecord(int row, const QpSqlRecord &record);

    mutable QpSqlOrderString orderSet;

protected:
    QString orderByClause() const;
    QVariant get_displayData( const QModelIndex &idx ) const;

signals:
    
    void sig_column_values_changed( int );

public Q_SLOTS:

    bool submit();

    bool submitAll();


private:

    QList<QpSqlRecord> cache;



};

#endif // QP_TEMP_TABLEMODEL_H


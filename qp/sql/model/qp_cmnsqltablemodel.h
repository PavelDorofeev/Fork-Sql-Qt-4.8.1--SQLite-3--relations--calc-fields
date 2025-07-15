#ifndef QP_CMNSQLTABLEMODEL_H
#define QP_CMNSQLTABLEMODEL_H

#include <QSqlTableModel>
#include <QList>
#include <QSqlIndex>
#include <QHash>
#include <QDebug>

#include "qp/sql/model/qp_calc_column.h"
#include "qp_sqlrelation.h"
#include "qp_sqlrecord.h"
#include "qp_field.h"
#include "qp_subaccnt.h"
#include "qp_columninfo.h"
#include "qp_sql_orderstring.h"


#include "qp/sql/model/qp_abstracttablemodel.h"

class QpCmnSqlTableModel;

typedef bool (*cb_setting_mdl) (QpCmnSqlTableModel *);

#include "qp/sql/dll_qp_sql_global.h"

class LIB_PREFIX_QP_SQL QpCmnSqlTableModel : public QSqlTableModel, public QpAbstractTableModel
{
    Q_OBJECT
public:


    enum MODE{
        UPDATE=1,
        INSERT
    };


    explicit QpCmnSqlTableModel( QSqlDatabase &Db,
                                 cb_setting_mdl pToSettingFunc,
                                 QObject *parent = 0);

    const QpSqlRecord baseRecord();

    virtual void setBaseRec( QpCmnSqlTableModel* mdl, const QSqlRecord& ) =0;
    virtual const QpSqlRecord getBaseRec() const;
    virtual const QpSqlRecord *get_BaseRec() const;

    int findRowById(int id);
    int getAccountingOnColumn(int relCol) const;

    cb_setting_mdl callback_setting_mdl_func;

    int isDirtyRow;

    int isInsertRow;

    uint lastDirtyRowId;

    uint isSelectedLine;

    uint lastDirtyCol;

    QSqlDatabase &db_;


    void setColInf( const QString & colName , const QpColumnInfo & inf);
    void setAlignment( const QString & colName , Qt::Alignment align);
    void setPrecision( const QString & colName , int precision);
    void setDblFormat( const QString & colName , char ch);
    void setEditable( const QString & colName , bool on);
    void setSelectable( const QString & colName , bool on);
    void set_Visible( const QString & colName , bool on);
    bool setCalcField( QpCalcColumn calc);

    bool setRelation(QpSqlRelation &relation);

    bool setSubAccount(
            const QString & parentTblName ,
            const QString & col1 ,
            const QString & col2 ,
            const QString & filterColName,
            const QString & sub_on
            );

    int indexOf(const QString &fieldName) const;

    QpSqlRecord getPblSqlRecord(  const QSqlRecord & rec);


    bool isSubAccounting( const QString &fldName );

    bool isSubAccountingOn_forFld(int row, const QString &fldName);

    static const QLatin1String prefix;

    bool isCalcColumn(const QString &) const;

    bool isRelationColumn( const QString &  fldName ) const;

    bool isRelationExtIdColumn(int col) const;

    bool isSpecialColumn(int col) const;


    int getRelIdColumn3(const QString & fldName) const;

    QString getRelIdColumn4(const QString & fldName);

    QString sqlite_qoutes_for_value(const QVariant & vv);

    int getRowPriValue(int row) const;

    QSqlIndex primaryIndex;

        int isDefaultSearchingColumn;

    bool hasUniqueFields( ); // for test copying possibilities

    bool removePrimaryKeys_fromRec(QSqlRecord &rec, MODE mode);

    virtual QpSqlRecord qp_record(int row) const = 0;

    virtual bool qp_setRecord(int row, const QpSqlRecord &record) = 0;
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;

    virtual QVariant format_displayData( const QVariant &var , const QpColumnInfo &inf) const;
    virtual QVariant get_displayData( const QModelIndex &idx ) const =0;

protected:

    void setTable(const QString &tableName); // now you have to use a prepare_mdl method ! Its incapsulates setTable.
    Qt::ItemFlags flags(const QModelIndex &idx) const;

    // ----------------------------------------------------------------
    // что касается добавления строк
    // ----------------------------------------------------------------
    bool insertRowIntoTable(const QSqlRecord &values);
    bool prepareInsertRow( int row, QSqlRecord &rec);

    int getLastInsertId();
    // ----------------------------------------------------------------
    int origTblColumnCount;



signals:

    void sig_editStrategyChanged(QSqlTableModel::EditStrategy);

    void sig_rowIsDirty(int row);

    void sig_afterSelect( bool);

    void sig_select_exec();


public slots:

private:



};

#endif // QP_CMNSQLTABLEMODEL_H

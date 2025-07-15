#ifndef QP_ABSTRACTTABLEMODEL_H
#define QP_ABSTRACTTABLEMODEL_H

#include "qp/sql/model/qp_sqlrecord.h"

#include <QSqlQuery>
#include <QModelIndex>

#include "qp/sql/model/qp_sqlrecord.h"
#include "qp/sql/model/qp_sqlrelation.h"

class QpSubAccnt;
class QpColumnInfo;
class QpCalcColumn;
#include "qp/sql/model/qp_sql_orderstring.h"
#include "qp/sql/model/qp_abstracttablemodel.h"

#include "qp/sql/dll_qp_sql_global.h"

class LIB_PREFIX_QP_SQL QpAbstractTableModel
{
    //    Q_OBJECT
public:

    typedef enum SPECIAL_FLD_TYPES{
        //RELATION_TXT_FLD=1,
        RELATION_ID_EXT_FLD=1,
        SUBACCOUNT_ENABLE_FLD,
        CALC_FLD
    }SPECIAL_FLD_TYPES;

    explicit QpAbstractTableModel();//QObject *parent = 0);

    virtual ~QpAbstractTableModel();



    QString tblName;


    // ------------------------------------------------------------------------------------------

    QHash<QString , QpSqlRelation > relations2;         // here relational fields description

    QHash< QString , QVariant > subAccountingFilter;    // if we open the sub accounting table we have to filter its rows

    QHash< QString , QpSubAccnt > subAccnt;             // here sub accounting connections

    QHash< QString , QpSubAccnt * > rel_bindings;       // here is an info only for sub fields

    QHash< QString , QpColumnInfo> colInfo;             // additional columns info for visual repainting,  aligning, precision, detect unique field (anavailabe to copy )

    QHash< QString , QpCalcColumn> calc_columns;        // calculate columns  [ ]

    QHash<QString,QString> having;                      // filter for aggregate functions

    QHash< int , QVariant> defaultVls;                  // defalt values for insert row

    QHash< QString, SPECIAL_FLD_TYPES > specialFld;

    // ------------------------------------------------------------------------------------------

    // собираем все , что относится к нашему развитию
    // т.е. все по сервисным полям
    int getPriColumn() const;
    QString priColName;

    bool editable;

    bool isRelationalColumn(int col);
    QpSqlRelation  getRelationInfoForColumn(const QString &fldName);

    int getRelIdColumn(int col) const; // for calls from with QModelIndex parameters

    void set_editable( bool Editable);

    // ----------------------------------
    QpSqlRecord baseRec; // first time the original table record is without extended fields (relations id, calc functions,..)

protected:
    void clearContainers();

signals:
    
public slots:
    
private:
};

#endif // QP_ABSTRACTTABLEMODEL_H

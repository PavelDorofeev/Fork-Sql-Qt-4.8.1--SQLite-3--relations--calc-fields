#ifndef QP_SQLTABLEMODEL2_H
#define QP_SQLTABLEMODEL2_H

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QList>
#include <QHash>

#include "qp/sql/model/qp_sqltablemodel.h"


class QpSqlTableModel2 : public QpSqlTableModel
{
    Q_OBJECT

public:

    typedef struct dependCol
    {
        int dst;
        int op;
        int col2;

        dependCol()
        {
        }
    };

    enum {
        MULTI=1,
        DEVIDE,
        SUM
    };

    explicit QpSqlTableModel2( QSqlDatabase &db ,
                               QObject *parent = 0);
    
    bool setDependColumn(int src, int dest, int op, int col2);

    bool setSummaryColumns(int col);

    virtual bool setData(const QModelIndex &item, const QVariant &value, int role = Qt::EditRole);

    bool prepare_mdl(const QString &tableName ,
                     const QHash<QString,QVariant> &SubAccountingFilter = QHash<QString,QVariant>());

    QHash<int,int> summaryColumns;

    bool select();

signals:

    void sig_column_values_changed(int col);
    
public slots:

protected:


private:

    QHash<int , dependCol > dep;
    
};

#endif // QP_SQLTABLEMODEL2_H

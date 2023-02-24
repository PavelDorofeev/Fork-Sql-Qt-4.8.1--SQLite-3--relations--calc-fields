#ifndef PBLSQLRELATIONALTABLEMODEL2_H
#define PBLSQLRELATIONALTABLEMODEL2_H

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QList>
#include <QHash>

#include "pbltableview/pblsqlrelationaltablemodel.h"


class PblSqlRelationalTableModel2 : public PblSqlRelationalTableModel
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

    explicit PblSqlRelationalTableModel2(QSqlDatabase &db ,
                                         QObject *parent = 0);
    
    bool setDependColumn(int src, int dest, int op, int col2);

    bool setSummaryColumns(int col);

    virtual bool setData(const QModelIndex &item, const QVariant &value, int role = Qt::EditRole);

    bool prepare(const QString &tableName);

    QHash<int,int> summaryColumns;

signals:

    void sig_column_values_changed(int col);
    
public slots:

private:

    QHash<int , dependCol > dep;


    
};

#endif // PBLSQLRELATIONALTABLEMODEL2_H

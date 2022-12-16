#ifndef PBLSQLRELATIONALTABLEMODEL_PURCHASES_H
#define PBLSQLRELATIONALTABLEMODEL_PURCHASES_H

#include "pblsqlrelationaltablemodel.h"

class PblSqlRelationalTableModel_Purchases : public PblSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit PblSqlRelationalTableModel_Purchases(QObject *parent = 0,
                                                  QSqlDatabase db = QSqlDatabase());
    
    virtual bool setData(const QModelIndex &item, const QVariant &value, int role = Qt::EditRole);

signals:
    
public slots:
    
};

#endif // PBLSQLRELATIONALTABLEMODEL_PURCHASES_H

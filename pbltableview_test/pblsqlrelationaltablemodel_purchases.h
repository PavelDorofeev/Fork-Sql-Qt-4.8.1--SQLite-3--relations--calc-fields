#ifndef PBLSQLRELATIONALTABLEMODEL_PURCHASES_H
#define PBLSQLRELATIONALTABLEMODEL_PURCHASES_H

#include "pbltableview/pblsqlrelationaltablemodel.h"

class PblSqlRelationalTableModel_Purchases : public PblSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit PblSqlRelationalTableModel_Purchases(QSqlDatabase &db ,
                                                  QObject *parent = 0
                                                  );
    
    virtual bool setData(const QModelIndex &item, const QVariant &value, int role = Qt::EditRole);

protected:

    bool updateRowInTable(int row, const QSqlRecord &values);

signals:
    
public slots:
    
};

#endif // PBLSQLRELATIONALTABLEMODEL_PURCHASES_H

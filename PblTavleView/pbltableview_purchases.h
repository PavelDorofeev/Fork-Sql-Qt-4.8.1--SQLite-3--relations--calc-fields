#ifndef PBLTABLEVIEW_PURCHASES_H
#define PBLTABLEVIEW_PURCHASES_H

#include "pbltableview.h"

class PblTableView_Purchases : public PblTableView
{
    Q_OBJECT
public:
    explicit PblTableView_Purchases(PblSqlRelationalTableModel * mdl_,
                                    QVBoxLayout * lo,
                                    QWidget *parent =0,
                                    bool editable = false);

    void commitData(QWidget *editor);
signals:
    
public slots:
    void slot_dataChanged(QModelIndex,QModelIndex);
    
};

#endif // PBLTABLEVIEW_PURCHASES_H

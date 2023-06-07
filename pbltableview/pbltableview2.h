#ifndef PBLTABLEVIEW2_H
#define PBLTABLEVIEW2_H

#include "pbltableview/pbltableview.h"

class PblTableView2 : public PblTableView
{
    Q_OBJECT
public:
    explicit PblTableView2(QWidget          *parent = 0,
                           cb_setting_mdl   pMdl = 0,
                           cb_setting_view  pView = 0,
                           bool selectable = false);

    virtual bool vrt_insertRow(int row);

    virtual bool vrt_afterSetFldValue(int idRow,
                                         int col,
                                         const QModelIndex & idx,
                                         const PblSqlRecord &rec);

signals:
    
public slots:
    
};

#endif // PBLTABLEVIEW2_H

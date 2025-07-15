#ifndef QP_TABLEVIEWWRAPPER2_H
#define QP_TABLEVIEWWRAPPER2_H

#include "qp/sql/view/qp_tableview_wrapper.h"

#include "qp/sql/dll_qp_sql_global.h"
class LIB_PREFIX_QP_SQL QpTableViewWrapper2 : public QpTableViewWrapper
{
    Q_OBJECT
public:
    explicit QpTableViewWrapper2( QWidget          *parent = 0,
                                  cb_setting_view  pView = 0,
                                  bool selectable = false);

    virtual bool vrt_insertRow(int row);

    virtual bool vrt_afterSetFldValue(int idRow,
                                      const QString & fldName,
                                      const QModelIndex & idx,
                                      const QpSqlRecord &rec,
                                      bool &needsSubmitAfter);

signals:
    
public slots:
    
};

#endif // QP_TABLEVIEWWRAPPER2_H

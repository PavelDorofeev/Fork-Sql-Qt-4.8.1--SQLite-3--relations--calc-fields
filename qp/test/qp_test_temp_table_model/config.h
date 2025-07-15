#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QSqlRecord>
#include <QSqlRecord>
#include "qp/sql/model/qp_columninfo.h"
#include "qp/sql/tableview/qp_tableview.h"

class QpSqlTableModel;
class QpTableViewWrapper;
class QpTempSqlTableModel;
class QpCmnSqlTableModel;

class config
{
public:
    config();

    static QpColumnInfo inf;

    static char * prog_version;

    static bool setting_mdl( QpCmnSqlTableModel * mdl);

    static bool setting_view( QpTableViewWrapper *view);

    static bool set_newInsertedRowParameters( QpSqlTableModel * mdl, QSqlRecord & rec);

    static bool set_newInsertedRowParameters_withSetData( QpSqlTableModel * mdl, int row);

    static int get_defaultColumn( QpSqlTableModel * mdl);

    static bool visibleRelIdColumns_byDefault;


    static qp::db::SECTIONS_TMPL prepare_matrix_goods( QAbstractTableModel * amdl);

    static qp::db::SECTIONS_TMPL prepare_matrix_purch( QAbstractTableModel * amdl );

    static bool test_model_is_correct( QSqlTableModel * amdl);



};

#endif // CONFIG_H

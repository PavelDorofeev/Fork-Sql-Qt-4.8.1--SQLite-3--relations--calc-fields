#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QSqlRecord>

class PblSqlRelationalTableModel;
class PblTableView;

class config
{
public:
    config();

    static char * prog_version;

    static bool setting_mdl( PblSqlRelationalTableModel * mdl);

    static bool setting_view( PblTableView *view);

    static bool set_newInsertedRowParameters( PblSqlRelationalTableModel * mdl, QSqlRecord & rec);

    static bool set_newInsertedRowParameters_withSetData( PblSqlRelationalTableModel * mdl, int row);

    static int get_defaultColumn( PblSqlRelationalTableModel * mdl);

    static bool visibleRelIdColumns_byDefault;

};

#endif // CONFIG_H

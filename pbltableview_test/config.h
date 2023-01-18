#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

class PblSqlRelationalTableModel;
class PblTableView;

class config
{
public:
    config();

    static bool setting_mdl( PblSqlRelationalTableModel * mdl);

    static bool setting_view( PblTableView *view);

    static bool visibleRelIdColumns_byDefault;

};

#endif // CONFIG_H

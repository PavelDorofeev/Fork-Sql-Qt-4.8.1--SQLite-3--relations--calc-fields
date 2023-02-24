#ifndef CONFIG2_H
#define CONFIG2_H

#include "config.h"

class PblSqlRelationalTableModel2;

class config2 : public config
{
public:
    config2();

    static bool setting_mdl2(PblSqlRelationalTableModel2 * mdl);

};

#endif // CONFIG2_H

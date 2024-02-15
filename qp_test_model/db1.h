#ifndef DB1_H
#define DB1_H

#include <QString>
#include <QSqlDatabase>

class db1
{

public:

    static const QString TBL_GOODS;
    static const QString TBL_PURCHASES;
    static const QString TBL_SUB_ACCOUNTING;
    static const QString TBL_CHECKS;
    static const QString TBL_TEST;


    static struct GOODS
    {
        static const QString ID;
        static const QString PRODUCT_NAME_STR;
        static const QString PRICE;
        static const QString SUB_ON;
    };


    static struct PURCHASES
    {
        static const QString ID;
        static const QString PRODUCT_NAME_ID;
        static const QString SUB;
        static const QString PRICE;
        static const QString QTY;
        static const QString SUM;
        static const QString CHK;
        static const QString COMBOBOX;
        static const QString FOO;

    };


    static struct CHECK
    {
        static const QString ID;
        static const QString PRODUCT_NAME;
        static const QString SUB;
        static const QString QTY;
        static const QString SUM;
        static const QString DATE_TIME;
    };


    static struct SUB_ACCOUNTING
    {
        static const QString ID;
        static const QString PRODUCT_NAME_ID;
        static const QString VAL;
    };

    static struct TEST
    {
        static const QString ID;
        static const QString INT1;
        static const QString INT2;
        static const QString INT3;
        static const QString INT4;
    };




    explicit db1(QSqlDatabase &Db);



};

#endif // DB_H

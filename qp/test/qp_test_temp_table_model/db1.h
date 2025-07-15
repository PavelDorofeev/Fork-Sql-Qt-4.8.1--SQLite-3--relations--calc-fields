#ifndef DB1_H
#define DB1_H

#include <QString>
#include <QSqlDatabase>



namespace db1
{

    // --------------------------------------------------------
    //                      TABLES
    // --------------------------------------------------------

    static const QString TBL_GOODS            = "goods";
    static const QString TBL_PURCHASES        = "purchases";
    static const QString TBL_SUB_ACCOUNTING   = "sub_accounting";
    static const QString TBL_CHECKS           = "checks";
    static const QString TBL_TEST             = "test";

    namespace GOODS
    {
        // --------------------------------------------------------
        //                  GOODS
        // --------------------------------------------------------
        static const QString SUB_ON                 = "sub_on";
        static const QString ID                     = "id";
        static const QString PRODUCT_NAME_STR       = "productName";
        static const QString PRICE                  = "price";

    }


    namespace PURCHASES
    {
    // --------------------------------------------------------
    //                  PURCHASES
    // --------------------------------------------------------
        static const QString ID                     = "id";
        static const QString PRODUCT_NAME_ID        = "productName";
        static const QString PRICE                  = "price";
        static const QString QTY                    = "qty";
        static const QString SUM                    = "sum";
        static const QString SUB                   = "sub";
        static const QString CHK                   = "chk";
        static const QString COMBOBOX              = "combobox";
        static const QString FOO                    = "foo";


    }

    namespace CHECK
    {
        // --------------------------------------------------------
        //                  CHECK
        // --------------------------------------------------------
        static const QString ID                    = "id";
        static const QString PRODUCT_NAME          = "productName";
        static const QString SUB                   = "sub";
        static const QString QTY                   = "qty";
        static const QString SUM                   = "sum";
        static const QString DATE_TIME             = "date_";

    }


    namespace TEST
    {
        // --------------------------------------------------------
        //                  TEST
        // --------------------------------------------------------
        static const QString ID         = "id";
        static const QString INT1       = "int1";
        static const QString INT2       = "int2";
        static const QString INT3       = "int3";
        static const QString INT4       = "int4";

    }




    namespace SUB_ACCOUNTING
    {
        // --------------------------------------------------------
        //                  SUB_ACCOUNTING
        // --------------------------------------------------------
        static const QString ID                     = "id";
        static const QString PRODUCT_NAME_ID        = "goods_productName_id";
        static const QString VAL                    = "val";
    }

}



#endif // DB_H

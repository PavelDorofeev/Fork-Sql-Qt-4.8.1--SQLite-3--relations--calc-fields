#include "db1.h"
#include <QDebug>

// --------------------------------------------------------
//                      TABLES
// --------------------------------------------------------

const QString db1::TBL_GOODS            = "goods";
const QString db1::TBL_PURCHASES        = "purchases";
const QString db1::TBL_SUB_ACCOUNTING   = "sub_accounting";
const QString db1::TBL_CHECKS           = "checks";
const QString db1::TBL_TEST             = "test";


// --------------------------------------------------------
//                  GOODS
// --------------------------------------------------------
const QString db1::GOODS::ID                     = "id";
const QString db1::GOODS::PRODUCT_NAME_STR       = "productName";
const QString db1::GOODS::PRICE                  = "price";
const QString db1::GOODS::SUB_ON                 = "sub_on";



// --------------------------------------------------------
//                  PURCHASES
// --------------------------------------------------------
const QString db1::PURCHASES::ID                     = "id";
const QString db1::PURCHASES::PRODUCT_NAME_ID           = "productName";
const QString db1::PURCHASES::PRICE                  = "price";
const QString db1::PURCHASES::QTY                    = "qty";
const QString db1::PURCHASES::SUM                    = "sum";
const QString db1::PURCHASES::SUB                   = "sub";
const QString db1::PURCHASES::CHK                   = "chk";
const QString db1::PURCHASES::COMBOBOX                   = "combobox";
const QString db1::PURCHASES::FOO                        = "foo";



// --------------------------------------------------------
//                  RECEIPT
// --------------------------------------------------------
const QString db1::CHECK::ID                    = "id";
const QString db1::CHECK::PRODUCT_NAME          = "productName";
const QString db1::CHECK::SUB                   = "sub";
const QString db1::CHECK::QTY                   = "qty";
const QString db1::CHECK::SUM                   = "sum";
const QString db1::CHECK::DATE_TIME             = "date_";

// --------------------------------------------------------
//                  SUB_ACCOUNTING
// --------------------------------------------------------
const QString db1::SUB_ACCOUNTING::ID                     = "id";
const QString db1::SUB_ACCOUNTING::PRODUCT_NAME_ID        = "goods_productName_id";
const QString db1::SUB_ACCOUNTING::VAL                    = "val";



// --------------------------------------------------------
//                  TEST
// --------------------------------------------------------
const QString db1::TEST::ID                     = "id";
const QString db1::TEST::INT1               = "int1";
const QString db1::TEST::INT2              = "int2";
const QString db1::TEST::INT3              = "int3";
const QString db1::TEST::INT4         = "int4";






db1::db1(QSqlDatabase &Db)

{

}



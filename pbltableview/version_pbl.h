#ifndef VERSION_H
#define VERSION_H


// 9.0.1.0 add new PblSqlRelationalTableModel2 class & config2.h/cpp for this

// 9.0.1.1 add PblSqlRelationalTableModel::insertRows fuction that this sets defaut values (i.e. comboBox with -1)

// 9.0.1.2 add possibility od two fields with to one ext table binding (change selectStatement)

// add getPblSqlRecord
// PblColumn is devides in two class PblRelColumn And PblCalcCol . We replace the pointers PblSqlRelation* and  CALC_COLUMN* to PblSqlRelation and CALC_COLUMN
// 10.0.0.1 

// filter was breaken / repare
// 10.0.1.0

// setRelation , setBinding make convenient
// 10.0.2.0

// 11.0.0.0  remove some functions

// our fields order is not equal db fields order , some fields may be in other position
// setRelation method has changed , anymore no field number only field name will be used
// add new parametr to constructor PblSqlRelationalTableModel : const QList<QString> &FieldsSet
// setSubAccount has changed
// Many changes
// selectStatement
/*
    SELECT purchases.id,
    relTbl_1.productName AS productName_id, !!!!!!! productName_id orig
    purchases.price,
    .....
    relTbl_26.name AS suppliers,
     relTbl_1.id AS goods_id_1,
     relTbl_26.id AS suppliers_id_26
    FROM purchases
    LEFT JOIN goods relTbl_1 ON purchases.productName_id=relTbl_1.id
    LEFT JOIN suppliers relTbl_26 ON purchases.suppliers=relTbl_26.id
*/
// все оригинальные имена (поля) имею оригинальные имена !!! в select выборке, чтобы можно было к ним обращаться по наименованиям !!!!!
// orderByClause
// calls fieldIndex will never used anymore . uses onle baseRec.indexOf !fieldIndex
// 12.0.0.0

// подправили F8 select
// подправили selectStatement для subAccountingFilter
//12.1.0.0

// for MDL : setTable,fieldIndex to private that this not use anymore from external calls ( now use only prepare_mdl )
// for View : setModel to private too ( now use only prepare_view )
//12.2.0.0

// when dialog with table was closed then this data is not saves yet with OnRowChange (for example)
// add PblTableView::currentChanged for OnRowChange
// Calc field and sub accounting on field set non editable
//12.3.0.0

// не сохранялось последнее измененное значение в таблице при закрытии окна
//12.4.0.0

#define PROG_VERSION    "12.4.0.0"
#define VER1    12
#define VER2    4
#define VER3    0
#define VER4    0

#endif // VERSION_H

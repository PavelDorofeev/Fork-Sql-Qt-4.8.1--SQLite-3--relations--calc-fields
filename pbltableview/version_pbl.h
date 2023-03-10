#ifndef VERSION_H
#define VERSION_H


// 9.0.1.0 add new PblSqlRelationalTableModel2 class & config2.h/cpp for this

// 9.0.1.1 add PblSqlRelationalTableModel::insertRows fuction that this sets defaut values (i.e. comboBox with -1)

// 9.0.1.2 add possibility od two fields with to one ext table binding (change selectStatement)

// add getPblSqlRecord
// PblColumn is devides in two class PblRelColumn And PblCalcCol . We replace the pointers PblSqlRelation* and  CALC_COLUMN* to PblSqlRelation and CALC_COLUMN
// 10.0.0.1 

// filter was breaken / repare
// 10.0.1.1

#define PROG_VERSION    "10.0.0.1"
#define VER1    10
#define VER2    0
#define VER3    0
#define VER4    1

#endif // VERSION_H

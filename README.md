This is Beta version 3.0. Fork-Sql-Qt-4.8.1--SQLite-3--relations--calc-fields 2022г.

We are created PblSqlRelationalTableModel class inherited by QSqlTableModeland.

sql_pbl directory is building as part of Qt Soources 4.8.1 (with sql.pro).
This is add new funtionality of Data Model - convinient extrenal relations, calculated field by other table and ...

PblSqlRelationalTableModel overrides QSqlTableModel class functions:
setTable;
select;
setData;
updateRowInTable;
insertRowIntoTable;
selectStatment;
orderByClause;

We add functions like in the QSqlRelationalTableModel class for compatibility:
setRelation;

Next we added PblSqlRelation and PblSqlRecord classes for support new functionality of PblSqlRelationalTableModel class.

Base idea: class PblSqlRelationalTableModel adds to resulting table new extended fields that are not existing in the database. 
This is id field of relations, calculated fields by data of other table.

Next we created PblTableView class inherited by QTableView


